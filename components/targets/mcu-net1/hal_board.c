//-------------------------------------------------------------------
// Filename: hal_board.c
// Description: HAL board peripherals library
//-------------------------------------------------------------------
//-------------------------------------------------------------------
// INCLUDES
//-------------------------------------------------------------------
#include "hal_defs.h"
#include "hal_cc8051.h"
#include "hal_mcu.h"
#include "hal_digio.h"
#include "hal_int.h"
#include "hal_board.h"
#include "hal_uart.h"
#include "hal_buzzer.h"
#include "hal_rtc.h"
#include "hal_relay.h"

//-------------------------------------------------------------------
// GLOBAL VARIABLES
//-------------------------------------------------------------------
uint8 pLedData;

//-------------------------------------------------------------------
// GLOBAL FUNCTIONS
//-------------------------------------------------------------------
//-------------------------------------------------------------------
// @fn      halBoardInit
// @brief   Set up board. Initialize MCU, configure I/O pins and user interfaces
//-------------------------------------------------------------------
void halBoardInit(void)
{
    // MCU
    halMcuInit();

    // RELAY
    HAL_RELAY1_OUTPUT();
    HAL_RELAY2_OUTPUT();

    // RS485 EN
    MCU_IO_OUTPUT(HAL_BOARD_RS485_EN_PORT, HAL_BOARD_RS485_EN_PIN, 0);

    // Buzzer
    MCU_IO_OUTPUT(HAL_BOARD_IO_BUZZER_PORT, HAL_BOARD_IO_BUZZER_PIN, 1);
    halBuzzerInit(2730);

    // RTC
    RTC_Init();
    
    HAL_RS485_SET_OUTPUT();
    
    // Initilization the UART or RS485  
    halUartInit();

    halIntOn();
}

//-------------------------------------------------------------------
// @fn          halAssertHandler
// @brief       Assert Prints error message
// @param       szErrMsg - String with error message.
// @return      none
//-------------------------------------------------------------------
void halAssertHandler(char *szErrMsg)
{
    while (1)
    {
        halMcuWaitMs(200);
        halMcuWaitMs(200);
    }
}
