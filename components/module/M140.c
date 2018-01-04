//-------------------------------------------------------------------
// Filename: M140.c
// Description: hal M140 library
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
#include "M140.h"

//-------------------------------------------------------------------
// LOCAL VARIABLES
//-------------------------------------------------------------------
uint16 M140_Value;

//-------------------------------------------------------------------
// LOCAL FUNCTIONS
//-------------------------------------------------------------------
uint8 M140_SpiRW(uint8 ch)
{
    uint8 i, cmd, ret;

    cmd = ch;
    for (i = 0; i < 8; i++)
    {
        HAL_SPI_CLK_CLR();
        if (cmd &0x80)
        {
            HAL_SPI_MOSI_SET();
        }
        else
        {
            HAL_SPI_MOSI_CLR();
        }
        
        cmd <<= 1;
        ret <<= 1;
        HAL_SPI_CLK_SET();
        if (HAL_SPI_MISO_VAL())
        {
            ret |= 0x01;
        }
    }
    HAL_SPI_MOSI_SET();
    return ret;
}

//-------------------------------------------------------------------
void ADT7301_Start(void)
{
    HAL_SPI_CS_EN();
    M140_SpiRW(0x00);
    M140_SpiRW(0x00);
    HAL_SPI_CS_DIS();
}

//-------------------------------------------------------------------
void ADT7301_Read(void)
{
    HAL_SPI_CS_EN();
    M140_Value = M140_SpiRW(0x20);
    M140_Value = (M140_Value << 8) + M140_SpiRW(0x00);
    HAL_SPI_CS_DIS();
}

//-------------------------------------------------------------------
// GLOBAL FUNCTIONS
//-------------------------------------------------------------------
void M140_Init(void)
{
    MCU_IO_INPUT(HAL_BOARD_IO_SPI_MISO_PORT, HAL_BOARD_IO_SPI_MISO_PIN, MCU_IO_PULLUP);
    MCU_IO_OUTPUT(HAL_BOARD_IO_SPI_MOSI_PORT, HAL_BOARD_IO_SPI_MOSI_PIN,1);
    MCU_IO_OUTPUT(HAL_BOARD_IO_SPI_CLK_PORT, HAL_BOARD_IO_SPI_CLK_PIN,1);
    MCU_IO_OUTPUT(HAL_BOARD_IO_SPI_CS_PORT, HAL_BOARD_IO_SPI_CS_PIN,1);
    
    ADT7301_Start();
    halMcuWaitMs(2);
    ADT7301_Read();
}

//-------------------------------------------------------------------
uint16 M140_GetValue(void)
{
    ADT7301_Start();
    halMcuWaitMs(2);
    ADT7301_Read();
    return M140_Value;
}

