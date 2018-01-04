//-------------------------------------------------------------------
// Filename: system.c
// Description: 
//-------------------------------------------------------------------
//-------------------------------------------------------------------
// INCLUDES
//-------------------------------------------------------------------
#include "hal_defs.h"
#include "hal_mcu.h"
#include "hal_board.h"
#include "hal_led.h"
#include "hal_lcd.h"
#include "hal_keypad.h"
#include "hal_buzzer.h"
#include "hal_uart.h"
#include "util.h"
#include "util_lcd.h"
#include "hal_timer_32k.h"
#include <string.h>
#define LINE1                           0x00
#define LINE2                           0x40
#define SET_DISPLAY_LINE(line)          lcdControl(0x80 | (line))
uint8 ProgramROM[8];
uint8 ProgramText;
uint8 ProgramOrder[4];
uint8 key;
uint8 KeyCount;
uint16 ProgramDelay;
void LcdWrite(void);
void Program(uint8 a);
void Mode(uint8 b);
uint8 ReadKeyInt(void);
//-------------------------------------------------------------------
void main(void)
{   
	halBoardInit();
    halBuzzer(300);
	ProgramDelay = 300;
    halLcdWriteString(HAL_LCD_LINE_1,0,"Press 1or2 Mode");
    halLcdWriteString(HAL_LCD_LINE_2,0,"Press3 set delay");
    //------------------------------------------------------------------------------
    while (TRUE)
    {
        key = halKeypadPushed();		
        if (key > 0)
        {
            if (key == '1')
            {
               halBuzzer(250);
               LcdWrite();
               Mode(1);
            }
            if (key == '2')
            {
               halBuzzer(250);
               LcdWrite();
               Mode(2);
            }
            if (key == '3')
            {
               halBuzzer(250);
               Mode(3);
            }   			
        }
        halMcuWaitMs(300);      
    }
}
void LcdWrite(void)
{
     halLcdClear();
     halLcdWriteString(HAL_LCD_LINE_1,0,"Mode");
     halLcdWriteChar(HAL_LCD_LINE_1, 4, key);
     halLcdWriteString(HAL_LCD_LINE_1,5,",Program");
}
void Mode(uint8 a) //Mode1´`Àô,Mode2¿é¤J¸`¥Ø«á¨Ì·Ó¿é¤J¶¶§Ç´`Àô
{
    switch(a)
    {
		case 1:
			while(1)
			{
				for(int i = 0;i < 4;i++)
				{
					Program(i+1);
					for(int j = 0;j < 8;j++)
					{
						halLedSetPort(ProgramROM[j]);
						halMcuWaitMs(250);
					}
					halBuzzer(200);
					halLedSetPort(0x00);
					halMcuWaitMs(ProgramDelay);
				}
			}
		case 2:
		    KeyCount = 0;
			halLcdWriteString(HAL_LCD_LINE_2,0,"Input:");
			halMcuWaitMs(300);
			while(KeyCount < 4)
			{
				key = halKeypadPushed();
				if (key > 0)
				{
					if (key == '1')
					{
						ProgramOrder[KeyCount] = 1;
					}
					if (key == '2')
					{
						ProgramOrder[KeyCount] = 2;
					}
					if (key == '3')
					{
						ProgramOrder[KeyCount] = 3;
					}
					if (key == '4')
					{					
						ProgramOrder[KeyCount] = 4;
					}
					halLcdWriteChar(HAL_LCD_LINE_2,6+KeyCount,key);
					KeyCount++;
				}
				halMcuWaitMs(300);
			}
			while(1)
			{
				for(int i = 0;i < 4;i++)
				{
					Program(ProgramOrder[i]);
					for(int j = 0;j < 8;j++)
					{
						halLedSetPort(ProgramROM[j]);
						halMcuWaitMs(250);
					}
					halBuzzer(200);
					halLedSetPort(0x00);
					halMcuWaitMs(ProgramDelay);
				}
			}
		case 3:
		    KeyCount = 0;
			uint8 ProgramDelayI[4];
			halLcdWriteString(HAL_LCD_LINE_1,0,"Input Delay:   ");
			halLcdWriteString(HAL_LCD_LINE_2,0,"0000 ms         ");
			while(KeyCount<4)
			{
			    halMcuWaitMs(300);
				if(ReadKeyInt() >= 0 && ReadKeyInt() < 10)
				{
					ProgramDelayI[KeyCount] = ReadKeyInt();
					char *pValue = convInt32ToText(ProgramDelayI[KeyCount]);
					halLcdWriteString(HAL_LCD_LINE_2,KeyCount,pValue);
					//halLcdDisplayUint8(HAL_LCD_LINE_2,KeyCount,HAL_LCD_RADIX_DEC,ProgramDelayI[KeyCount]);
					KeyCount++;
				}				
			}
			ProgramDelay = ProgramDelayI[0] * 1000 + ProgramDelayI[1] * 100 + ProgramDelayI[2] *10 + ProgramDelayI[3];
			halLcdWriteString(HAL_LCD_LINE_1,0,"Press 1or2 Mode");
            break;
    }
}
uint8 ReadKeyInt(void)
{
	key = halKeypadPushed();
	if(key == '1') return 1;
	else if(key == '2') return 2;
	else if(key == '3') return 3;
	else if(key == '4') return 4;
	else if(key == '5') return 5;
	else if(key == '6') return 6;
	else if(key == '7') return 7;
	else if(key == '8') return 8;
	else if(key == '9') return 9;
	else if(key == '0') return 0;
	else return 11;
}
void Program(uint8 b)
{
    switch(b)
    {
		case 1:
			ProgramText = '1';
			halLcdWriteChar(HAL_LCD_LINE_1, 13, ProgramText);
			ProgramROM[0] = 0x81;
			ProgramROM[1] = 0x42;
			ProgramROM[2] = 0x24;
			ProgramROM[3] = 0x18;
			ProgramROM[4] = 0x3C;
			ProgramROM[5] = 0x7E;
			ProgramROM[6] = 0xFF;
			ProgramROM[7] = 0x00;
			break;
		case 2:
			ProgramText = '2';
			halLcdWriteChar(HAL_LCD_LINE_1, 13, ProgramText);
			ProgramROM[0] = 0x01;
			ProgramROM[1] = 0x02;
			ProgramROM[2] = 0x04;
			ProgramROM[3] = 0x08;
			ProgramROM[4] = 0x10;
			ProgramROM[5] = 0x20;
			ProgramROM[6] = 0x40;
			ProgramROM[7] = 0x80;
			break;
		case 3:
			ProgramText = '3';
			halLcdWriteChar(HAL_LCD_LINE_1, 13, ProgramText);
			ProgramROM[0] = 0x01;
			ProgramROM[1] = 0x03;
			ProgramROM[2] = 0x07;
			ProgramROM[3] = 0x0F;
			ProgramROM[4] = 0x1F;
			ProgramROM[5] = 0x3F;
			ProgramROM[6] = 0x7F;
			ProgramROM[7] = 0xFF;
			break;
		case 4:
			ProgramText = '4';
			halLcdWriteChar(HAL_LCD_LINE_1, 13, ProgramText);
			ProgramROM[0] = 0x11;
			ProgramROM[1] = 0x00;
			ProgramROM[2] = 0x33;
			ProgramROM[3] = 0x00;
			ProgramROM[4] = 0x77;
			ProgramROM[5] = 0x00;
			ProgramROM[6] = 0xFF;
			ProgramROM[7] = 0x00;
			break;
    }	
}
