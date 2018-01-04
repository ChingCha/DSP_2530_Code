//-------------------------------------------------------------------
// Filename: M320.c
// Description: hal M320 module library ¬õ¥~½u·Å«×°»´ú(I2C)
//-------------------------------------------------------------------
//-------------------------------------------------------------------
// INCLUDES
//-------------------------------------------------------------------
#include "hal_defs.h"
#include "hal_cc8051.h"
#include "hal_mcu.h"
#include "hal_board.h"
#include "M320.h"

#define SA  0x00
uint8 ChipType ;
//-------------------------------------------------------------------
// LOCAL FUNCTIONS
//-------------------------------------------------------------------
void M320_I2cStart(void)
{
    HAL_I2C_SCL_SET();
    HAL_I2C_SDA_SET();
    halMcuWaitUs(5);
    HAL_I2C_SDA_CLR();
    halMcuWaitUs(5);
    HAL_I2C_SCL_CLR();
    halMcuWaitUs(5);
}

//-------------------------------------------------------------------
void M320_I2cStop(void)
{
    HAL_I2C_SDA_CLR();
    halMcuWaitUs(5);
    HAL_I2C_SCL_SET();
    halMcuWaitUs(5);
    HAL_I2C_SDA_SET();
    halMcuWaitUs(5);
}

//-------------------------------------------------------------------
void M320_I2cAck(void)
{
    HAL_I2C_SDA_CLR();
    HAL_I2C_SCL_SET();
    halMcuWaitUs(5);
    HAL_I2C_SCL_CLR();
    halMcuWaitUs(5);
}

//-------------------------------------------------------------------
void M320_I2cNack(void)
{
    HAL_I2C_SDA_SET();
    HAL_I2C_SCL_SET();
    halMcuWaitUs(5);
    HAL_I2C_SCL_CLR();
    halMcuWaitUs(5);
}

//-------------------------------------------------------------------
void M320_I2cWrite(uint8 d)
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
        halMcuWaitUs(5);
        HAL_I2C_SCL_CLR();
        halMcuWaitUs(5);
    }
}

//-------------------------------------------------------------------
uint8 M320_I2cRead(void)
{
    uint8 res = 0;
    uint8 cnt;

    HAL_I2C_SDA_SET();
    HAL_I2C_SDA_DIR_IN();
    halMcuWaitUs(5);
    for (cnt = 0; cnt < 8; cnt++)
    {
        HAL_I2C_SCL_SET();
        res <<= 1;
        if (HAL_I2C_SDA_VAL())
        {
            res |= 0x01;
        }
        halMcuWaitUs(5);
        HAL_I2C_SCL_CLR();
        halMcuWaitUs(5);
    }
    HAL_I2C_SDA_DIR_OUT();
    return res;
}

//-------------------------------------------------------------------
// GLOBAL FUNCTIONS
//-------------------------------------------------------------------
void M320_Init(void)
{
    uint16 val;
    HAL_I2C_SDA_DIR_OUT();
    MCU_IO_OUTPUT(HAL_BOARD_IO_I2C_SCL_PORT, HAL_BOARD_IO_I2C_SCL_PIN, 1);
    
    halMcuWaitMs(100);
    ChipType=0x20;
    val=M320_GetDieTemperature();
    halMcuWaitMs(200);
    val=M320_GetDieTemperature();
    val=((val *2) - 27315) / 10;
    if(val>100 && val<500)
        ChipType=0x20;
    else
        ChipType=0x00;
}

//-------------------------------------------------------------------
uint16 M320_GetObjTemperature(void)
{
    uint8 val_4lsb;
    uint8 val_4msb;
    uint8 val_crc;
    uint16 val;
    while (1)
    {
        M320_I2cStart();
        M320_I2cWrite((SA << 1));
        M320_I2cAck();
        M320_I2cWrite(0x07|ChipType);//0x27 or 0x07
        M320_I2cAck();

        M320_I2cStart();
        M320_I2cWrite((SA << 1) | 0x01);
        M320_I2cAck();
        val_4lsb = M320_I2cRead();
        M320_I2cAck();
        val_4msb = M320_I2cRead();
        M320_I2cAck();
        val_crc = M320_I2cRead();
        M320_I2cNack();
        M320_I2cStop();
        if (val_crc != 0xFF)
        {
            break;
        }
        halMcuWaitMs(10);
    }
    val = ((uint16)val_4msb) << 8 | val_4lsb;
    return val;
}

//-------------------------------------------------------------------
uint16 M320_GetDieTemperature(void)
{
    uint8 val_4lsb;
    uint8 val_4msb;
    uint8 val_crc;
    uint16 val;
    while (1)
    {
        M320_I2cStart();
        M320_I2cWrite((SA << 1));
        M320_I2cAck();
        M320_I2cWrite(0x06|ChipType);//0x26 or 0x06
        M320_I2cAck();

        M320_I2cStart();
        M320_I2cWrite((SA << 1) | 0x01);
        M320_I2cAck();
        val_4lsb = M320_I2cRead();
        M320_I2cAck();
        val_4msb = M320_I2cRead();
        M320_I2cAck();
        val_crc = M320_I2cRead();
        M320_I2cNack();
        M320_I2cStop();
        if (val_crc != 0xFF)
        {
            break;
        }
        halMcuWaitMs(10);
    }
    val = ((uint16)val_4msb) << 8 | val_4lsb;
    return val;
}
