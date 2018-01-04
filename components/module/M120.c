//-------------------------------------------------------------------
// Filename: M120.c
// Description: EEPROM SPI library ¶Í¶C∞Oæ–≈È(SPI)Ωd®“
//-------------------------------------------------------------------
//-------------------------------------------------------------------
// INCLUDES
//-------------------------------------------------------------------
#include "hal_defs.h"
#include "hal_cc8051.h"
#include "hal_mcu.h"
#include "hal_board.h"
#include "M120.h"

//-------------------------------------------------------------------
uint8 M120_SpiRW(uint8 ch)
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
void M120_Init(void)
{
    HAL_SPI_INIT();
    
    HAL_SPI_CS_DIS();
    HAL_SPI_MOSI_SET();
    HAL_SPI_CLK_SET();
}

//-------------------------------------------------------------------
void M120_WriteEEPROM(uint8 addr, uint8 c)
{
    HAL_SPI_CS_EN();
    M120_SpiRW(0x06);
    HAL_SPI_CS_DIS();


    HAL_SPI_CS_EN();
    M120_SpiRW(0x02);
    M120_SpiRW((uint8)(addr >> 8));
    M120_SpiRW((uint8)addr);
    M120_SpiRW(c);
    HAL_SPI_CS_DIS();

    HAL_SPI_CS_EN();
    M120_SpiRW(0x04);
    HAL_SPI_CS_DIS();

    halMcuWaitMs(5);
}

//-------------------------------------------------------------------
uint8 M120_ReadEEPROM(uint8 addr)
{
    uint8 ch;

    HAL_SPI_CS_EN();
    M120_SpiRW(0x03);
    M120_SpiRW((uint8)(addr >> 8));
    M120_SpiRW((uint8)addr);
    ch = M120_SpiRW(0x00);
    HAL_SPI_CS_DIS();

    return ch;
}
