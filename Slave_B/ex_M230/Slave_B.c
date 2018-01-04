//ZigBee_PRO
#include "hal_defs.h"
#include "hal_mcu.h"
#include "hal_board.h"
#include "hal_led.h"
#include "hal_lcd.h"
#include "hal_int.h"
#include "hal_button.h"
#include "hal_buzzer.h"
#include "hal_rf.h"
#include "Program.h"
#include "basic_rf.h"
#include "hal_keypad.h"

//C_Compiler
#include <string.h>

// Application parameters
#define RF_CHANNEL                18      // 2.4 GHz RF channel

// BasicRF address definitions
#define PAN_ID                	0x1111
#define B_ZONE           		0x2233		//Slave-B位址
#define APP_PAYLOAD_LENGTH        127

// Application states
#define IDLE                      0
#define SEND_CMD                  1

#ifdef SECURITY_CCM
    // Security key
    static uint8 key[] = 
    {
        0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 
    };
#endif

static uint8 pRxData[APP_PAYLOAD_LENGTH];
static basicRfCfg_t basicRfConfig;			//宣告RFConfig組態

//-------------------------------------------------
uint8 key;
uint16 ProgramDelay;
uint8 ModeRam[9];
//-------------------------------------------------
void Program(uint8 b);
void Mode(uint8 a);
void ShowLCD(void);
uint8 BreakMode(uint8 i,uint8 j);
/********************************
主程式
********************************/
void main(void)
{   
	basicRfConfig.panId = PAN_ID;
	basicRfConfig.channel = RF_CHANNEL;
	basicRfConfig.ackRequest = TRUE;
	#ifdef SECURITY_CCM
		basicRfConfig.securityKey = key;
	#endif 
	halBoardInit();	
	halLedSet(8);
	basicRfConfig.myAddr = B_ZONE;
    if (basicRfInit(&basicRfConfig) == FAILED){}	
	
    basicRfReceiveOn();			
	ProgramDelay = 300;
	ModeRam[0] = 0;
    halLcdWriteString(HAL_LCD_LINE_1,0,"I.O.L_System");
	halLcdWriteString(HAL_LCD_LINE_2,0,"Slave_B Ready..");
    while (1)
	{		
        while (!basicRfPacketIsReady())
		{
            halLedToggle(7);
            halMcuWaitMs(10);
        }				
		while(basicRfReceive(pRxData, APP_PAYLOAD_LENGTH, NULL) > 0)
		{						
			Mode(pRxData[1]);	
		}   
    }
}

void Mode(uint8 a)
{
    switch(a)
    {
		case 1:
			ModeRam[0] = 1;
			ShowLCD();
			halLcdWriteString(HAL_LCD_LINE_1,12,"1");
			for(uint8 i = 0;i < 100;i++)
			{
				READProgram(i);
				halLcdDisplayUint8(HAL_LCD_LINE_2,8,HAL_LCD_RADIX_DEC,i);
				for(uint8 j = 0;j < 8;j++)
				{
					LedProgram(j);
					halMcuWaitMs(250);
				}
				halLedSetPort(0x00);
				halMcuWaitMs(ProgramDelay);
				i = BreakMode(i,0x0001);
			}			
			break;		
		case 2:
			ModeRam[0] = 2;
			ShowLCD();
			halLcdWriteString(HAL_LCD_LINE_1,12,"2");
			for(int i = 0;i < 8;i++)
			{
				READProgram(pRxData[i+2]);
				ModeRam[i+1] = pRxData[i+2];
				halLcdDisplayUint8(HAL_LCD_LINE_2,8,HAL_LCD_RADIX_DEC,pRxData[i+2]);
				for(int j = 0;j < 8;j++)
				{
					LedProgram(j);
					halMcuWaitMs(250);
				}
				i = BreakMode(i,0x0002);
				halMcuWaitMs(ProgramDelay);
			}		
			break;		
		case 3:
			ShowLCD();
			halLcdWriteString(HAL_LCD_LINE_1,12,"3");
			ProgramDelay = pRxData[2] * 1000 + pRxData[3] * 100 + pRxData[4] * 10 + pRxData[5];
			halLcdDisplayUint16(HAL_LCD_LINE_2,12,HAL_LCD_RADIX_DEC,ProgramDelay);
			if(ModeRam[0] == 1 || ModeRam[0] == 0) pRxData[1] = 1;
			if(ModeRam[0] == 2)
			{
				pRxData[1] = 2;
				for(uint8 i = 0;i < 8;i++)
				{
					pRxData[i+2] = ModeRam[i+1];
				}
			}
			break;		
    }
}

void ShowLCD(void)
{
	halLcdClear();
	halLcdWriteString(HAL_LCD_LINE_1,0,"Slave_B:Mode");
	halLcdWriteString(HAL_LCD_LINE_2,0,"Program:");
	halLcdDisplayUint16(HAL_LCD_LINE_2,12,HAL_LCD_RADIX_DEC,ProgramDelay);
}

uint8 BreakMode(uint8 i,uint8 j)
{
	if(basicRfReceive(pRxData, APP_PAYLOAD_LENGTH, NULL) > 0)
	{
		if(pRxData[0] != j)
		{
			halLcdWriteString(HAL_LCD_LINE_1,0,"Slave_B:NewMode");
			halMcuWaitMs(100);
			if(j == 0x0001) return 100;
			else if(j == 0x0002) return 8;
			
		}
		return i;
	}
}