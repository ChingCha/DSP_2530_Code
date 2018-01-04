//-------------------------------------------------------------------
// Filename: hal_rs485.c
// Description: This file contains the interface to the H/W RS485 driver.
//-------------------------------------------------------------------
//-------------------------------------------------------------------
// INCLUDES
//-------------------------------------------------------------------
#include "hal_defs.h"
#include "hal_cc8051.h"
#include "hal_board.h"
#include "hal_mcu.h"
#include "hal_uart.h"
#include "hal_rs485.h"

//-------------------------------------------------------------------
// MACROS
//-------------------------------------------------------------------
#define HAL_RS485_ISR_RX_AVAIL() \
(rs485Cfg.rxTail >= rs485Cfg.rxHead) ? (rs485Cfg.rxTail - rs485Cfg.rxHead) : (HAL_RS485_ISR_RX_MAX - rs485Cfg.rxHead + rs485Cfg.rxTail)

#define HAL_RS485_ISR_TX_AVAIL() \
(rs485Cfg.txHead > rs485Cfg.txTail) ? (rs485Cfg.txHead - rs485Cfg.txTail - 1) : (HAL_RS485_ISR_TX_MAX - rs485Cfg.txTail + rs485Cfg.txHead - 1)

//-------------------------------------------------------------------
// TYPEDEFS
//-------------------------------------------------------------------
#define HAL_RS485_ISR_RX_MAX       128
#define HAL_RS485_ISR_TX_MAX       128

typedef struct
{
    uint8 rxBuf[HAL_RS485_ISR_RX_MAX];
    uint8 rxHead;
    volatile uint8 rxTail;
    uint8 rxShdw;

    uint8 txBuf[HAL_RS485_ISR_TX_MAX];
    volatile uint8 txHead;
    uint8 txTail;
    uint8 txMT;
} RS485Cfg_t;

//-------------------------------------------------------------------
// LOCAL VARIABLES
//-------------------------------------------------------------------
RS485Cfg_t rs485Cfg;

//-------------------------------------------------------------------
// @fn      halUartInit
// @brief   Initialize the UART65
//-------------------------------------------------------------------
void halRS485Init(void)
{ 
    // UART Configuration
    PERCFG &= ~HAL_UART_PERCFG_BIT; // Set UART0 I/O location to P0.

    P0SEL |= U0RX_TX; // Enable Tx and Rx peripheral functions on pins.
    ADCCFG &= ~U0RX_TX; // Make sure ADC doesnt use this.
    U0CSR = CSR_MODE; // Mode is UART Mode.
    U0UCR = UCR_FLUSH; // Flush it.

    // Only supporting subset of baudrate for code size - other is possible.
    // 115200
    U0BAUD = 216;
    U0GCR = 11;

    // 8 bits/char; no parity; 1 stop bit; stop bit hi.
    U0UCR = UCR_STOP;
    U0CSR |= CSR_RE;
    URX0IE = 1;
    U0DBUF = 0; // Prime the ISR pump.

    rs485Cfg.rxHead = 0;
    rs485Cfg.rxTail = 0;
    rs485Cfg.txHead = 0;
    rs485Cfg.txTail = 0;
    rs485Cfg.rxShdw = 0;
    rs485Cfg.txMT = 0;

}

//-------------------------------------------------------------------
// @fn      halUartRead
// @brief   Read a buffer from the UART
// @param   buf  - valid data buffer at least 'len' bytes in size
//          len  - max length number of bytes to copy to 'buf'
// @return  length of buffer that was read
//-------------------------------------------------------------------
uint16 halRS485Read(uint8 *buf, uint16 len)
{
    uint16 cnt = 0;
    
    // Set the RS485 state to RX
    HAL_RS485_SET_RX();
    halMcuWaitUs(500);
    
    while ((rs485Cfg.rxHead != rs485Cfg.rxTail) && (cnt < len))
    {
        *buf++ = rs485Cfg.rxBuf[rs485Cfg.rxHead++];
        if (rs485Cfg.rxHead >= HAL_RS485_ISR_RX_MAX)
        {
            rs485Cfg.rxHead = 0;
        }
        cnt++;
    }
    return cnt;
}

//-------------------------------------------------------------------
// @fn      halUartWrite
// @brief   Write a buffer to the UART.
// @param   buf - pointer to the buffer that will be written, not freed
//          len - length of
// @return  length of the buffer that was sent
//-------------------------------------------------------------------
uint16 halRS485Write(uint8 *buf, uint16 len)
{
    uint16 cnt;
    
    // Set the RS485 state to TX
    HAL_RS485_SET_TX();
    halMcuWaitUs(500);
    
    // Accept "all-or-none" on write request.
    if (HAL_RS485_ISR_TX_AVAIL() < len)
    {
        return 0;
    }

    for (cnt = 0; cnt < len; cnt++)
    {
        rs485Cfg.txBuf[rs485Cfg.txTail] =  *buf++;
        rs485Cfg.txMT = 0;

        if (rs485Cfg.txTail >= HAL_RS485_ISR_TX_MAX - 1)
        {
            rs485Cfg.txTail = 0;
        }
        else
        {
            rs485Cfg.txTail++;
        }
        IEN2 |= UTX0IE; // Keep re-enabling ISR as it might be keeping up with this loop due to other ints.
    }
    
    // Set the RS485 state to RX
    halMcuWaitUs(500);
    HAL_RS485_SET_RX(); 
    
    return cnt;
}

//-------------------------------------------------------------------
// @fn      halUartRxLen()
// @brief   Calculate Rx Buffer length - the number of bytes in the buffer.
// @param   none
// @return  length of current Rx Buffer
//-------------------------------------------------------------------
uint16 halRS485RxLen(void)
{
    return HAL_RS485_ISR_RX_AVAIL();
}

//-------------------------------------------------------------------
// @fn      halUartSuspend
// @brief   Suspend UART hardware before entering PM mode 1, 2 or 3.
// @param   None
// @return  None
//-------------------------------------------------------------------
void halRS485Suspend(void)
{
    U0CSR &= ~CSR_RE;
}

//-------------------------------------------------------------------
// @fn      halUartResume
// @brief   Resume UART hardware after exiting PM mode 1, 2 or 3.
// @param   None
// @return  None
//-------------------------------------------------------------------
void halRS485Resume(void)
{
    U0UCR |= UCR_FLUSH;
    U0CSR |= CSR_RE;
}

//-------------------------------------------------------------------
// @fn      halUartRxIsr
// @brief   UART Receive Interrupt
//-------------------------------------------------------------------
HAL_ISR_FUNCTION(halRS485RxIsr, URX0_VECTOR)
{
    uint8 tmp = U0DBUF;
    rs485Cfg.rxBuf[rs485Cfg.rxTail] = tmp;

    // Re-sync the shadow on any 1st byte received.
    if (rs485Cfg.rxHead == rs485Cfg.rxTail)
    {
        rs485Cfg.rxShdw = ST0;
    }

    if (++rs485Cfg.rxTail >= HAL_RS485_ISR_RX_MAX)
    {
        rs485Cfg.rxTail = 0;
    }
}

//-------------------------------------------------------------------
// @fn      halUartTxIsr
// @brief   UART Transmit Interrupt
//-------------------------------------------------------------------
HAL_ISR_FUNCTION(halRS485TxIsr, UTX0_VECTOR)
{
    if (rs485Cfg.txHead == rs485Cfg.txTail)
    {
        IEN2 &= ~UTX0IE;
        rs485Cfg.txMT = 1;
    }
    else
    {
        UTX0IF = 0;
        U0DBUF = rs485Cfg.txBuf[rs485Cfg.txHead++];

        if (rs485Cfg.txHead >= HAL_RS485_ISR_TX_MAX)
        {
            rs485Cfg.txHead = 0;
        }
    }
}
