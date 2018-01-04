//-------------------------------------------------------------------
// Filename: hal_spi.c
// Description: hal_spi transmit interface library
//-------------------------------------------------------------------
//-------------------------------------------------------------------
// INCLUDES
//-------------------------------------------------------------------
#include "hal_defs.h"
#include "hal_cc8051.h"
#include "hal_mcu.h"
#include "hal_board.h"
#include "hal_digio.h"
#include "hal_adc.h"
#include "hal_spi.h"

//-------------------------------------------------------------------
// LOCAL FUNCTIONS
//-------------------------------------------------------------------


//-------------------------------------------------------------------
// LOCAL VARIABLES
//-------------------------------------------------------------------
spiCfg_t spiCfg;

//-------------------------------------------------------------------
// GLOBAL FUNCTIONS
//-------------------------------------------------------------------
//-------------------------------------------------------------------
// SPI_Init function
//-------------------------------------------------------------------
void SPI_Init(void)
{
    // Setting the SPI transmit interface IO pin
    MCU_IO_INPUT(HAL_BOARD_IO_SPI_MISO_PORT, HAL_BOARD_IO_SPI_MISO_PIN, MCU_IO_PULLUP); // MISO
    MCU_IO_OUTPUT(HAL_BOARD_IO_SPI_MOSI_PORT, HAL_BOARD_IO_SPI_MOSI_PIN,1);  // MOSI
    MCU_IO_OUTPUT(HAL_BOARD_IO_SPI_CLK_PORT, HAL_BOARD_IO_SPI_CLK_PIN,1);    // CLK   
    MCU_IO_OUTPUT(HAL_BOARD_IO_SPI_CS_PORT, HAL_BOARD_IO_SPI_CS_PIN,1);      // CS
    
    // Set the Master Mode, Configure phase, polarity, and bit order
    U1CSR &= ~0xA0; // Set the SPI mode and Master mode
    U1GCR &= ~0xC0;      // Set the CPOL = CPHA = 0 
    U1GCR |= 0x20;       // Set the ORDER = 1 
    
    // Set UART0 I/O to alternate 2 location on P1 pins
    PERCFG |= 0x01;
    
    // The SPI configure
    
}

//-------------------------------------------------------------------
// halSpiWrite function
//-------------------------------------------------------------------
uint16 halSpiWrite(uint8 *pBuffer, uint16 length)
{
//    uint8 i, cmd, ret;
//
//    cmd = ch;
//    for (i = 0; i < 8; i++)
//    {
//        HAL_SPI_CLK_CLR();
//        if (cmd &0x80)
//        {
//            HAL_SPI_MOSI_SET();
//        }
//        else
//        {
//            HAL_SPI_MOSI_CLR();
//        }
//        
//        cmd <<= 1;
//        ret <<= 1;
//        HAL_SPI_CLK_SET();
//        if (HAL_SPI_MISO_VAL())
//        {
//            ret |= 0x01;
//        }
//    }
//    HAL_SPI_MOSI_SET();
//    return ret;
}

//-------------------------------------------------------------------
// halSpiRead function
//-------------------------------------------------------------------
uint16 halSpiRead(uint8 *pBuffer, uint16 length)
{
  
}

//-------------------------------------------------------------------
// halSpiRxLen function
//-------------------------------------------------------------------
uint16 halSpiRxLen(void)
{
  
}