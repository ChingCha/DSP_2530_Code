//ZigBee_PRO
#include "hal_defs.h"
#include "hal_mcu.h"
#include "hal_board.h"
#include "hal_led.h"
#include "hal_int.h"
#include "hal_button.h"
#include "hal_buzzer.h"
#include "hal_rf.h"
#include "basic_rf.h"
#include "hal_keypad.h"
#include "Program.h"
#include "hal_lcd.h"

//C_Compiler
#include <string.h>

// Application parameters
#define RF_CHANNEL                18      // 2.4 GHz RF channel

// BasicRF address definitions
#define PAN_ID                	0x1111
#define A_ZONE           		0x2222
#define APP_PAYLOAD_LENGTH        255
#define Master            	0x3333


//---------------------------------------------------------------
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
//-------------------------------------------------
static uint8 pRxData[APP_PAYLOAD_LENGTH];
static uint8 pTxData[APP_PAYLOAD_LENGTH];
static basicRfCfg_t basicRfConfig;
//-------------------------------------------------
uint8 key;
uint16 ProgramDelay;
//-------------------------------------------------
void SlaveInit(void);
void Program(uint8 b);
void Mode(uint8 a);
void ShowLCD(void);
uint8 BreakMode(uint8 i,uint8 j);
void SendData(uint8 Program,uint8 RxData);
/********************************
主程式
********************************/
void main(void)
{   
	SlaveInit();
    while (1)
	{		
        while (!basicRfPacketIsReady())
		{
            halLedToggle(7);
            halMcuWaitMs(10);
			halLedToggle(7);
            halMcuWaitMs(10);
        }				
		while(basicRfReceive(pRxData, APP_PAYLOAD_LENGTH, NULL) > 0)
		{						
			Mode(pRxData[0]);
		}   
    }
}
void SlaveInit(void)
{
	basicRfConfig.panId = PAN_ID;
	basicRfConfig.channel = RF_CHANNEL;
	basicRfConfig.ackRequest = TRUE;
	#ifdef SECURITY_CCM
		basicRfConfig.securityKey = key;
	#endif 
	halBoardInit();	
	halLedSet(8);
	basicRfConfig.myAddr = A_ZONE;
    if (basicRfInit(&basicRfConfig) == FAILED){}	
    basicRfReceiveOn();			
	ProgramDelay = 300;
    halLcdWriteString(HAL_LCD_LINE_1,0,"I.O.L_System");
	halLcdWriteString(HAL_LCD_LINE_2,0,"Slave_A Ready..");
}
void Mode(uint8 a)
{
	ProgramDelay = pRxData[1] * 100;
    switch(a)
    {
		case 1:
			ShowLCD();
			halLcdWriteString(HAL_LCD_LINE_1,12,"1");
			for(uint8 i = 0;i < 100;i++)
			{
				READProgram(i);
				SendData(i,pRxData[10]);
				halLcdDisplayUint8(HAL_LCD_LINE_2,8,HAL_LCD_RADIX_DEC,i);
				for(uint8 j = 0;j < 8;j++)
				{
					LedProgram(j);
					halMcuWaitMs(250);
				}				
				halLedSetPort(0x00);
				halMcuWaitMs(ProgramDelay);
				i = BreakMode(i,1);
			}			
			break;		
		case 2:
			ShowLCD();
			halLcdWriteString(HAL_LCD_LINE_1,12,"2");
			for(int i = 0;i < 8;i++)
			{
				READProgram(pRxData[i+2]);
				SendData(pRxData[i+2],pRxData[10]);
				halLcdDisplayUint8(HAL_LCD_LINE_2,8,HAL_LCD_RADIX_DEC,pRxData[i+2]);
				for(int j = 0;j < 8;j++)
				{
					LedProgram(j);
					halMcuWaitMs(250);
				}
				i = BreakMode(i,2);
				halMcuWaitMs(ProgramDelay);
			}		
			break;
    }
}

void ShowLCD(void)
{
	halLcdClear();
	halLcdWriteString(HAL_LCD_LINE_1,0,"Slave_A:Mode");
	halLcdWriteString(HAL_LCD_LINE_2,0,"Program:");
	halLcdDisplayUint16(HAL_LCD_LINE_2,12,HAL_LCD_RADIX_DEC,ProgramDelay);
}

uint8 BreakMode(uint8 i,uint8 j)
{
	if(basicRfReceive(pRxData, APP_PAYLOAD_LENGTH, NULL) > 0)
	{
		if((pRxData[0] != j) || (pRxData[1] * 100 != ProgramDelay))
		{
			halLcdWriteString(HAL_LCD_LINE_1,0,"Slave_A:NewMode");
			halMcuWaitMs(100);
			if(j == 1) return 100;
			else if(j == 2) return 8;			
		}
		return i;
	}
}
void SendData(uint8 Program,uint8 RxData)
{
		pTxData[0] = 0x01;
		pTxData[1] = Program;
		basicRfSendPacket(Master,pTxData,APP_PAYLOAD_LENGTH);
}