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

uint8 ProgramROM[8];
uint8 ProgramText;
uint8 ProgramOrder[4];
uint8 key;
uint8 KeyCount;
void LcdWrite(void);
void Program(uint8 a);
void Mode(uint8 b);
//-------------------------------------------------------------------
void main(void)
{   
	halBoardInit();
    halBuzzer(300);
    halLcdWriteString(HAL_LCD_LINE_1,0,"Press 1or2 Mode");
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
					halMcuWaitMs(300);
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
					halMcuWaitMs(300);
				}
			}			
    }
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