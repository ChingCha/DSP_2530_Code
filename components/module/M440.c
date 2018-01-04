//-------------------------------------------------------------------
// Filename: M440.c
// Description: hal M440 module library πq§l√πΩL(I2C)Ωd®“
//-------------------------------------------------------------------
//-------------------------------------------------------------------
// INCLUDES
//-------------------------------------------------------------------
#include "hal_defs.h"
#include "hal_cc8051.h"
#include "hal_mcu.h"
#include "hal_board.h"
#include "M440.h"

/* X,Y,Z axis value */
uint16 M440_X_AXIS_Value;
uint16 M440_Y_AXIS_Value;
uint16 M440_Z_AXIS_Value;

/* OFFSET X,Y,Z value */
uint16 M440_OFFSET_X_Value;
uint16 M440_OFFSET_Y_Value;
uint16 M440_OFFSET_Z_Value;

/* M440 Module version, serial and Info */
uint16 M440_Ver, M440_Ser;
uint8 M440_Dev;
uint8 M440_Sta;

#define SA  0x0E

//-------------------------------------------------------------------
// GLOBAL FUNCTIONS
//-------------------------------------------------------------------
//-------------------------------------------------------------------
// Function Name : M440_Start
// Description : Start the M440 Module
//-------------------------------------------------------------------
void M440_I2cStart(void)
{
    // Start the M440 I2C Module
    HAL_I2C_SCL_CLR(); 
    HAL_I2C_SDA_SET(); 
    halMcuWaitUs(5);
    HAL_I2C_SCL_SET(); 
    halMcuWaitUs(5);
    HAL_I2C_SDA_CLR(); 
    halMcuWaitUs(5);
    HAL_I2C_SCL_CLR(); 
}

//-------------------------------------------------------------------
// Function Name : M440_Stop
// Description : Stop the M440 Module
//-------------------------------------------------------------------
void M440_I2cStop(void)
{
     // Stop the M440 I2C Module 
    HAL_I2C_SCL_CLR(); 
    halMcuWaitUs(5);
    HAL_I2C_SDA_CLR(); 
    halMcuWaitUs(5);
    HAL_I2C_SCL_SET(); 
    halMcuWaitUs(5);
    HAL_I2C_SDA_SET(); 
}

//-------------------------------------------------------------------
// FileName : M440_I2cAck
// Description : M440 Module I2C Ack
//-------------------------------------------------------------------
void M440_I2cAck(void)
{
    HAL_I2C_SDA_CLR();
    halMcuWaitUs(5);
    HAL_I2C_SCL_SET();
    halMcuWaitUs(5);
    HAL_I2C_SCL_CLR();
    halMcuWaitUs(5);
}

//-------------------------------------------------------------------
// FileName : M440_I2cNack
// Description : M440 Module I2C NoAck
//-------------------------------------------------------------------
void M440_I2cNack(void)
{
    HAL_I2C_SDA_SET();
    halMcuWaitUs(5);
    HAL_I2C_SCL_SET();
    halMcuWaitUs(5);
    HAL_I2C_SCL_CLR();
    halMcuWaitUs(5);
}

//-------------------------------------------------------------------
// FileName : M440_I2cWrite
// Description : M440 Module I2C Write Command
//-------------------------------------------------------------------
void M440_I2cWrite(uint8 d)
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
// FileName : M440_I2cRead
// Description : M440 Module I2C Read Command
//-------------------------------------------------------------------
uint8 M440_I2cRead(void)
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
// Function Name : M440_Init
// Description : Initilization the E-compass module
//-------------------------------------------------------------------
void M440_Init(void)
{
    HAL_I2C_SCL_DIR_OUT(); // SCL set output
    HAL_I2C_SDA_DIR_OUT(); // SDA set output
    
    M440_I2cStart();
    halMcuWaitMs(20);
    
    M440_WriteReg(AMI304_CNTL1,0x82); 
    halMcuWaitMs(10);
    M440_WriteReg(AMI304_CNTL2,0x08); 
    halMcuWaitMs(10);
    M440_WriteReg(AMI304_CNTL3,0x10); 
    halMcuWaitMs(10);  
}

//-------------------------------------------------------------------
// Function Name : M440_WriteReg
// Description : Write the M440 Module Register
//-------------------------------------------------------------------
void M440_WriteReg(uint8 addr,uint8 ch)
{
        M440_I2cStart();
        M440_I2cWrite((SA << 1)); 
        M440_I2cAck();
        M440_I2cWrite(addr); 
        M440_I2cAck();
        M440_I2cWrite(ch);  
        M440_I2cNack();
        M440_I2cStop();
}

//-------------------------------------------------------------------
// Function Name : M440_ReadReg
// Description : Read the M440 Module Register
//-------------------------------------------------------------------
uint8 M440_ReadReg(uint8 addr)
{
    uint8 ret;
        // Slave address + write
        M440_I2cStart();
        M440_I2cWrite((SA << 1)); 
        M440_I2cAck();        
        M440_I2cWrite(addr); 
        M440_I2cAck();

        // Slave address + read
        M440_I2cStart();
        M440_I2cWrite((SA << 1) | 0x01); 
        M440_I2cAck();
        ret = M440_I2cRead(); 
        M440_I2cNack();
        M440_I2cStop();
        return ret;
}

//-------------------------------------------------------------------
// FileName : M440_Pooling
// Description : Get X,Y,Z axis Magnetism value
//-------------------------------------------------------------------
void M440_Pooling(void)
{ 
    M440_WriteReg(AMI304_CNTL3, 0x40);
    halMcuWaitMs(300);
    
    // X-axis value
    M440_X_AXIS_Value = M440_ReadReg(AMI304_DATAX_1); 
    M440_X_AXIS_Value = (M440_X_AXIS_Value << 8) + M440_ReadReg(AMI304_DATAX_0);
    // Y-axis value
    M440_Y_AXIS_Value = M440_ReadReg(AMI304_DATAY_1); 
    M440_Y_AXIS_Value = (M440_Y_AXIS_Value << 8) + M440_ReadReg(AMI304_DATAY_0);
    // Z-axis value
    M440_Z_AXIS_Value = M440_ReadReg(AMI304_DATAZ_1); 
    M440_Z_AXIS_Value = (M440_Z_AXIS_Value << 8) + M440_ReadReg(AMI304_DATAZ_0);
}

//-------------------------------------------------------------------
// FileName : M440_Offset
// Description : Get X,Y,Z axis offset adjusting
//-------------------------------------------------------------------
void M440_Offset(void)
{
  M440_OFFSET_X_Value = M440_ReadReg(AMI304_OFFX_1); // Get X axis offset adjusting
  M440_OFFSET_Y_Value = M440_ReadReg(AMI304_OFFY_1); // Get Y axis offset adjusting
  M440_OFFSET_Z_Value = M440_ReadReg(AMI304_OFFZ_1); // Get Z axis offset adjusting
}

//-------------------------------------------------------------------
// FileName : M440_Version
// Description : Get M440 Module information, SN and version
//-------------------------------------------------------------------
void M440_Version(void)
{  
   // Device Infomation(Who I am)
   M440_Dev = M440_ReadReg(AMI304_DEVICE);
   
   // Version
   M440_Ver = M440_ReadReg(AMI304_VER_0);
  
   // SN
   M440_Ser = M440_ReadReg(AMI304_SN_1);
   M440_Ser = (M440_Ser << 8) + M440_ReadReg(AMI304_SN_0);
}