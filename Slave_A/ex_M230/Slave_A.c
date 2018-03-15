/*------------------------------------------------------------------
File name: Slave_A.c
Description:This is I.O.L system master control application functions.
Updated:2018/03/12
-------------------------------------------------------------------*/
//-----------------------CC2530 Include--------------------------
#include "ioCC2530.h"
#include "hal_defs.h"
#include "hal_mcu.h"
#include "hal_board.h"
#include "hal_led.h"
#include "hal_int.h"
#include "hal_rf.h"
#include "basic_rf.h"
#include "Program.h"
#include <string.h>
#include "hal_cc8051.h"
//---------------------------Define-----------------------------------
#define RF_CHANNEL                18      // 2.4 GHz RF channel
// BasicRF address definitions
#define PAN_ID                	0x1111
#define A_ZONE           		0x2222
#define APP_PAYLOAD_LENGTH        255
#define Master            	0x3333
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
//-------------------------------------------------------------------
static uint8 pRxData[APP_PAYLOAD_LENGTH];
static uint8 pTxData[APP_PAYLOAD_LENGTH];
static basicRfCfg_t basicRfConfig;
//-------------------------variable----------------------------------
uint16 ProgramDelay;
//-------------------------Function---------------------------------
void SlaveInit(void);
void Program(uint8 b);
void Mode(uint8 a);
uint8 BreakMode(uint8 i,uint8 j);
void SendData(uint8 Program,uint8 RxData);
//-------------------------main function----------------------------------
void main(void)
{   
	SlaveInit();
    while (1)
	{				
		while(basicRfReceive(pRxData, APP_PAYLOAD_LENGTH, NULL) > 0)
		{									
			if(pRxData[0] == 0 && pRxData[1] == 0) SendData(0,0);
			if(pRxData[0] != 5) Mode(pRxData[0]);
			if(pRxData[0] == 5) halMcuReset();
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
	basicRfConfig.myAddr = A_ZONE;
    if (basicRfInit(&basicRfConfig) == FAILED){}	
    basicRfReceiveOn();			
	ProgramDelay = 300;
    P0SEL &= ~0xFF;
    P0DIR |= 0xFF;
    MCU_PORT_OUTPUT(0, 0x00);
}
void Mode(uint8 a)
{
	ProgramDelay = pRxData[1] * 100;
    switch(a)
    {
		case 1:
			for(int i = 1;i < 100;i++)
			{
				READProgram(i);
				SendData(i,pRxData[10]);
				for(uint8 j = 0;j < 8;j++)
				{
					LedProgram(j);
					halMcuWaitMs(ProgramDelay);
				}				
				halLedSetPort(0x00);
                MCU_PORT_OUTPUT(0, 0x00);
				halMcuWaitMs(ProgramDelay);
				i = BreakMode(i,1);
			}			
			break;		
		case 2:
			for(int i = 0;i < 2;i++)
			{
				READProgram(pRxData[i+2]);
				SendData(pRxData[i+2],pRxData[10]);
				for(int j = 0;j < 8;j++)
				{
					LedProgram(j);
					halMcuWaitMs(ProgramDelay);
				}
				i = BreakMode(i,2);
                MCU_PORT_OUTPUT(0, 0x00);
                halLedSetPort(0x00);
                halMcuWaitMs(ProgramDelay);
			}
			break;
    }
}

uint8 BreakMode(uint8 i,uint8 j)
{
	if(basicRfReceive(pRxData, APP_PAYLOAD_LENGTH, NULL) > 0)
	{
		if((pRxData[0] != j) || (pRxData[1] * 100 != ProgramDelay))
		{
			halMcuWaitMs(100);
			if(j == 1) return 100;
			else if(j == 2) return 10;			
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