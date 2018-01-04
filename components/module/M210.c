//-------------------------------------------------------------------
// Filename: M210.c
// Description: ¹qÀ£¿é¥XD/A(SPI)
//-------------------------------------------------------------------
//-------------------------------------------------------------------
// INCLUDES
//-------------------------------------------------------------------
#include "hal_defs.h"
#include "hal_cc8051.h"
#include "hal_mcu.h"
#include "hal_board.h"
#include "M210.h"

//-------------------------------------------------------------------
void M210_SpiRW(uint16 ch)
{
    uint8 i;
    uint16 cmd;

    cmd = ch;
    for (i = 0; i < 16; i++)
    {
        HAL_SPI_CLK_CLR();
        if (cmd &0x8000)
        {
            HAL_SPI_MOSI_SET();
        }
        else
        {
            HAL_SPI_MOSI_CLR();
        }
        cmd <<= 1;
        HAL_SPI_CLK_SET();
    }
    HAL_SPI_MOSI_SET();
}

//-------------------------------------------------------------------
void M210_Init(void)
{
    HAL_SPI_INIT();
    HAL_SPI_CS_DIS();
    HAL_SPI_MOSI_SET();
    HAL_SPI_CLK_SET();
}

//-------------------------------------------------------------------
void M210_SetValue(uint8 ch)
{
    uint16 temp;

    temp = ((uint16)ch) << 4;
    HAL_SPI_CS_EN();
    M210_SpiRW(temp); // Read rate ADCC instruction
    HAL_SPI_CS_DIS();
}
