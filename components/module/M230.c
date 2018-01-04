//-------------------------------------------------------------------
// Filename: M230.c
// Description: hal M230 module library ¶Í¶C∞Oæ–≈È(I2C)
//-------------------------------------------------------------------
//-------------------------------------------------------------------
// INCLUDES
//-------------------------------------------------------------------
#include "hal_defs.h"
#include "hal_cc8051.h"
#include "hal_mcu.h"
#include "hal_board.h"
#include "M230.h"

//-------------------------------------------------------------------
// LOCAL FUNCTIONS
//-------------------------------------------------------------------
void M230_I2cStart(void)
{
    HAL_I2C_SCL_SET();
    HAL_I2C_SDA_SET();
    halMcuWaitUs(2);
    HAL_I2C_SDA_CLR();
    halMcuWaitUs(2);
    HAL_I2C_SCL_CLR();
    halMcuWaitUs(2);
}

//-------------------------------------------------------------------
void M230_I2cStop(void)
{
    HAL_I2C_SDA_CLR();
    halMcuWaitUs(2);
    HAL_I2C_SCL_SET();
    halMcuWaitUs(2);
    HAL_I2C_SDA_SET();
    halMcuWaitUs(2);
}

//-------------------------------------------------------------------
void M230_I2cAck(void)
{
    HAL_I2C_SDA_CLR();
    HAL_I2C_SCL_SET();
    halMcuWaitUs(2);
    HAL_I2C_SCL_CLR();
    halMcuWaitUs(2);
}

//-------------------------------------------------------------------
void M230_I2cNack(void)
{
    HAL_I2C_SDA_SET();
    HAL_I2C_SCL_SET();
    halMcuWaitUs(2);
    HAL_I2C_SCL_CLR();
    halMcuWaitUs(2);
}

//-------------------------------------------------------------------
void M230_I2cWrite(uint8 d)
{
    uint8 i;

    for (i = 0; i < 8; i++)
    {
        if (d &0x80)
        {
            HAL_I2C_SDA_SET();
        }
        else
        {
            HAL_I2C_SDA_CLR();
        }
        HAL_I2C_SCL_SET();
        d = d << 1;
        halMcuWaitUs(2);
        HAL_I2C_SCL_CLR();
        halMcuWaitUs(2);
    }
}

//-------------------------------------------------------------------
uint8 M230_I2cRead(void)
{
    uint8 res = 0;
    uint8 cnt;

    HAL_I2C_SDA_SET();
    HAL_I2C_SDA_DIR_IN();
    halMcuWaitUs(2);
    for (cnt = 0; cnt < 8; cnt++)
    {
        HAL_I2C_SCL_SET();
        res <<= 1;
        if (HAL_I2C_SDA_VAL())
        {
            res |= 0x01;
        }
        halMcuWaitUs(2);
        HAL_I2C_SCL_CLR();
        halMcuWaitUs(2);
    }
    HAL_I2C_SDA_DIR_OUT();
    return res;
}

//-------------------------------------------------------------------
// GLOBAL FUNCTIONS
//-------------------------------------------------------------------
void M230_Init(void)
{
    HAL_I2C_SDA_DIR_OUT();
    MCU_IO_OUTPUT(HAL_BOARD_IO_I2C_SCL_PORT, HAL_BOARD_IO_I2C_SCL_PIN,1);

	M230_ReadEEPROM(0);
}


//-------------------------------------------------------------------
void M230_WriteEEPROM(uint8 addr, uint8 ch)
{
    M230_I2cStart();
    M230_I2cWrite((((uint8)(addr >> 7)) &0x0E) | 0xA0);
    M230_I2cAck();
    M230_I2cWrite((uint8)addr);
    M230_I2cAck();
    M230_I2cWrite(ch); //data
    M230_I2cAck();
    M230_I2cStop();
	halMcuWaitMs(5);
}

//-------------------------------------------------------------------
uint8 M230_ReadEEPROM(uint8 addr)
{
    uint8 res;

    res = (((uint8)(addr >> 7)) &0x0E) | 0xA0;
    M230_I2cStart();
    M230_I2cWrite(res);
    M230_I2cAck();
    M230_I2cWrite((uint8)addr);
    M230_I2cAck();

    M230_I2cStart();
    M230_I2cWrite(res+1);
    M230_I2cAck();
    res = M230_I2cRead();
    M230_I2cNack();
    M230_I2cStop();

    return res;
}
