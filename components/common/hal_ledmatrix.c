//引入標頭檔
#include "ioCC2530.h"
#include "hal_ledmatrix.h"

//CC2530 Port & MAX7219初始化函數，並設置MAX7219內部的控制暫存器
void MAX7219_Init(){
	
	P0SEL &= ~0x70;	//把P0a_4、5、6設置為通用I/O Port功能
	P0DIR |= 0x70;	//把P0_4、5、6 Prot傳輸方向設置為輸出
	
	MAX7219_Write(REG_DECODE, 0x00);          	// set to "no decode" for all digits
	MAX7219_Write(REG_SCAN_LIMIT,0x07);      	// set up to scan all eight digits
	MAX7219_Write(REG_SHUTDOWN, 1);
	MAX7219_Write(REG_DISPLAY_TEST, 0);	
	MAX7219_Clear(); 
	MAX7219_SetBrightness(0x06); 
}

/*
*********************************************************************************************************
* MAX7219_SendByte()
*
* Description: Send one byte to the MAX7219
* Arguments  : DINout = DIN to send
* Returns    : none
*********************************************************************************************************
*/
void MAX7219_SendByte (unsigned char DINout)
{
  char i;
  for (i=8; i>0; i--) {
    unsigned char mask = 1 << (i - 1);                // calculate bitmask
	MAX7219CLK=0;                                     
    if (DINout & mask)                               // output one DIN bit
	  MAX7219DIN=1;                                   
    else                                              
	  MAX7219DIN=0;										  // bring CLK high
    MAX7219CLK=1;                                          
	}
}

/*
*********************************************************************************************************
* MAX7219_Write()
*
* Description: Write to MAX7219
* Arguments  : reg_number = register to write to
*              DINout = DIN to write to MAX7219
* Returns    : none
*********************************************************************************************************
*/
void MAX7219_Write (unsigned char reg_number, unsigned char DINout)
{
  MAX7219LOAD=1;                                           // take LOAD high to begin
  MAX7219_SendByte(reg_number);                       // write register number to MAX7219
  MAX7219_SendByte(DINout);                          // write DIN to MAX7219
  MAX7219LOAD=0;                                           // take LOAD low to latch in DIN
  MAX7219LOAD=1;                                           // take LOAD high to end
}


/*
*********************************************************************************************************
* MAX7219_Clear()
*
* Description: Clear the display (all digits blank)
* Arguments  : none
* Returns    : none
*********************************************************************************************************
*/
void MAX7219_Clear (void)
{
  char i;
  for (i=0; i < 9; i++)
    MAX7219_Write(i, 0x00);                           // turn all segments off
}

/*
*********************************************************************************************************
* MAX7219_SetBrightness()
*
* Description: Set the LED display brightness
* Arguments  : brightness (0-15)
* Returns    : none
*********************************************************************************************************
*/
void MAX7219_SetBrightness (char brightness)
{
  brightness &= 0x0f;                                 // mask off extra bits
  MAX7219_Write(REG_INTENSITY, brightness);           // set brightness
}

//延遲函數
void Delay(unsigned int t)
{
  while(t--);
}

//A1警示
void A1_Warning(){
	MAX7219_Write(DIGIT0,0x001);
	Delay(60000);
	MAX7219_Write(DIGIT0,0x00);
	Delay(60000);
}

//A2警示
void A2_Warning(){
	MAX7219_Write(DIGIT0,0x002);
	Delay(60000);
	MAX7219_Write(DIGIT0,0x00);
	Delay(60000);
}


//B1警示
void B1_Warning(){
	MAX7219_Write(DIGIT1,0x01);
	Delay(60000);
	MAX7219_Write(DIGIT1,0x00);
	Delay(60000);
}


//B2警示
void B2_Warning(){
	MAX7219_Write(DIGIT1,0x02);
	Delay(60000);
	MAX7219_Write(DIGIT1,0x00);
	Delay(60000);
}


