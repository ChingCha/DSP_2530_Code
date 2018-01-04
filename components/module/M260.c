//-------------------------------------------------------------------
// Filename: M260.c
// Description: MLX90609 Digital/Analog Gyro library
//-------------------------------------------------------------------
//-------------------------------------------------------------------
// INCLUDES
//-------------------------------------------------------------------
#include "hal_defs.h"
#include "hal_cc8051.h"
#include "hal_mcu.h"
#include "hal_board.h"
#include "M260.h"

uint16 M260_Rate;
uint16 M260_Temp;
//-------------------------------------------------------------------
uint8 M260_SpiRW(uint8 ch)
{
	uint8 i,cmd,ret;

    cmd=ch;
	for(i=0;i<8;i++)
	{
		HAL_SPI_CLK_CLR();
        halMcuWaitUs(2);
		if(cmd & 0x80)
		{
			HAL_SPI_MOSI_SET();
		}
		else
		{
			HAL_SPI_MOSI_CLR();
		}
		cmd <<= 1;
		ret <<= 1;
        halMcuWaitUs(2);
		HAL_SPI_CLK_SET();
        halMcuWaitUs(2);
        if(HAL_SPI_MISO_VAL())
       		ret |= 0x01;
	}
    HAL_SPI_MOSI_SET();
	return ret;
}

//-------------------------------------------------------------------
// @fn      M260_Init
// @brief   Set up MLX90609
// @return  none
//-------------------------------------------------------------------
void M260_Init(void)
{
    HAL_SPI_INIT();
    
	HAL_SPI_CS_DIS();
	HAL_SPI_MOSI_SET();
	HAL_SPI_CLK_SET();
}

//-------------------------------------------------------------------
// @fn      M260_Pooling
// @brief   Get Digital/Analog
// @param   none
// @return  none
//-------------------------------------------------------------------
void M260_Pooling(void)
{
	uint8 data1,data2;
	uint16 temp;

    HAL_SPI_INIT();
    
	HAL_SPI_CS_DIS();
	HAL_SPI_MOSI_SET();
	HAL_SPI_CLK_SET();

	HAL_SPI_CS_EN();
    M260_SpiRW(0x94); // Read rate ADCC instruction
	HAL_SPI_CS_DIS();

    halMcuWaitUs(250);

	HAL_SPI_CS_EN();
    M260_SpiRW(0x80); // Send SPI ADCR Instruction        
    data1 = M260_SpiRW(0x00);
    data2 = M260_SpiRW(0x00);
	HAL_SPI_CS_DIS();

	if(((data1&0x80)==0x00) && (data1&0x20)==0x20)
	{
		temp = data1;
        temp = (temp<<7)+(data2>>1);
        temp &= 0x07FF;
		M260_Rate=temp;
	}

	HAL_SPI_CS_EN();
    M260_SpiRW(0x9C); // Read temperature ADCC instruction
	HAL_SPI_CS_DIS();

    halMcuWaitUs(250);

	HAL_SPI_CS_EN();
    M260_SpiRW(0x80); // Send SPI ADCR Instruction        
    data1 = M260_SpiRW(0x00);
    data2 = M260_SpiRW(0x00);
	HAL_SPI_CS_DIS();

	if(((data1&0x80)==0x00) && (data1&0x20)==0x20)
	{
		temp = data1;
        temp = (temp<<7)+(data2>>1);
        temp &= 0x07FF;
		M260_Temp=temp;
	}
}

