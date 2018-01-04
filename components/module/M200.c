//-------------------------------------------------------------------
// Filename: M200.c
// Description: hal M200 module library ����װ���(I2C)�d��
//-------------------------------------------------------------------
//-------------------------------------------------------------------
// INCLUDES
//-------------------------------------------------------------------
#include "hal_defs.h"
#include "hal_cc8051.h"
#include "hal_mcu.h"
#include "hal_board.h"
#include "M200.h"


uint16 M200_Humi;
uint16 M200_Temp;

//-------------------------------------------------------------------
void SHT_Start(void)
{
    HAL_I2C_SCL_CLR();
    HAL_I2C_SDA_SET();
    halMcuWaitUs(5);
    HAL_I2C_SCL_SET();
    halMcuWaitUs(5);
    HAL_I2C_SDA_CLR();
    halMcuWaitUs(5);
    HAL_I2C_SCL_CLR();
    halMcuWaitUs(20);
    HAL_I2C_SCL_SET();
    halMcuWaitUs(5);
    HAL_I2C_SDA_SET();
    halMcuWaitUs(5);
    HAL_I2C_SCL_CLR();
    halMcuWaitUs(5);
}

//-------------------------------------------------------------------
uint8 SHT_WriteByte(uint8 dat)
{
    uint8 i, err = 0;

    for (i = 0; i <8; i++)
    {
        if (dat &0x80)
        {
            HAL_I2C_SDA_SET();
        }
        else
        {
            HAL_I2C_SDA_CLR();
        }
        dat = dat << 1;
        HAL_I2C_SCL_SET();
        halMcuWaitUs(20);
        HAL_I2C_SCL_CLR();
        halMcuWaitUs(20);
    }
    HAL_I2C_SDA_SET();
    HAL_I2C_SDA_DIR_IN();
    MCU_IO_OUTPUT(HAL_BOARD_IO_SPI_CS_PORT, HAL_BOARD_IO_SPI_CS_PIN, 0);
    HAL_I2C_SCL_SET();
    halMcuWaitUs(5);
    if (HAL_I2C_SDA_VAL())
    {
        err = 1;
    }
    HAL_SPI_CS_DIS();
    HAL_I2C_SCL_CLR();
    HAL_I2C_SDA_DIR_OUT();
    HAL_I2C_SDA_SET();
    return err;
}

//-------------------------------------------------------------------
uint8 SHT_ReadByte(uint8 ack)
{
    uint8 res = 0;
    uint8 cnt;

    HAL_I2C_SDA_SET();
    HAL_I2C_SDA_DIR_IN();
    HAL_I2C_SCL_CLR();
    for (cnt = 0; cnt < 8; cnt++)
    {
        HAL_I2C_SCL_SET();
        halMcuWaitUs(5);
        res <<= 1;
        if (HAL_I2C_SDA_VAL())
        {
            res |= 0x01;
        }
        HAL_I2C_SCL_CLR();
        halMcuWaitUs(5);
    }
    HAL_I2C_SDA_DIR_OUT();
    halMcuWaitUs(5);
    if (ack == 1)
    {
        HAL_I2C_SDA_CLR();
    }
    HAL_I2C_SCL_SET();
    halMcuWaitUs(20);
    HAL_I2C_SCL_CLR();
    HAL_I2C_SDA_SET();
    return res;
}

//-------------------------------------------------------------------
void SHT_ConnectReset(void)
{
    uint8 i;

    HAL_I2C_SDA_SET();
    HAL_I2C_SCL_CLR();
    halMcuWaitUs(20);
    for (i = 0; i < 9; i++)
    {
        HAL_I2C_SCL_SET();
        halMcuWaitUs(5);
        HAL_I2C_SCL_CLR();
        halMcuWaitUs(5);
    }
	halMcuWaitMs(100);
}

//-------------------------------------------------------------------
// GLOBAL FUNCTIONS
//-------------------------------------------------------------------
// @fn      M200_Init
// @return  none
//-------------------------------------------------------------------
void M200_Init(void)
{
    HAL_I2C_SCL_DIR_OUT();
    HAL_I2C_SDA_DIR_OUT();
    SHT_ConnectReset();
    SHT_Start();
    SHT_WriteByte(0x1E);
	halMcuWaitMs(100);
}

//-------------------------------------------------------------------
void M200_GetValue(void)
{
    uint8 count, err = 0;

    while (TRUE)
    {
        SHT_Start();
        err += SHT_WriteByte(0x05); //  Converter H
        if (err > 0)
        {
            break;
        }
        //55ms
        HAL_I2C_SDA_DIR_IN();
        for (count = 0; count < 75; count++)
        {
            halMcuWaitMs(1);
            if (HAL_I2C_SDA_VAL() == 0)
            {
                HAL_I2C_SDA_DIR_OUT();
                M200_Humi = SHT_ReadByte(1);
                if (M200_Humi > 0x3F)
                {
                    M200_Humi = 0x3F;
                }
                M200_Humi = (M200_Humi << 8) + (uint16)SHT_ReadByte(1);
                SHT_ReadByte(0);
                break;
            }
        }
        HAL_I2C_SDA_SET();
        HAL_I2C_SDA_DIR_OUT();
        
        halMcuWaitMs(10);
        SHT_Start();
        err += SHT_WriteByte(0x03); // Converter T
        if (err > 0)
        {
            break;
        }
        //210ms
        HAL_I2C_SDA_DIR_IN();
        for (count = 0; count < 250; count++)
        {
            halMcuWaitMs(1);
            if (HAL_I2C_SDA_VAL() == 0)
            {
                HAL_I2C_SDA_DIR_OUT();
                M200_Temp = SHT_ReadByte(1);
                if (M200_Temp > 0x3F)
                {
                    M200_Temp = 0x3F;
                }
                M200_Temp = (M200_Temp << 8) + (uint16)SHT_ReadByte(1);
                SHT_ReadByte(0);
                break;
            }
        }
        HAL_I2C_SDA_SET();
        HAL_I2C_SDA_DIR_OUT();       
        break;
    }
    
    if (err > 0)
    {
        SHT_ConnectReset();
    }
}
