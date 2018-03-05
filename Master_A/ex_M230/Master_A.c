/*------------------------------------------------------------------
File name: Master.c
Description:This is I.O.L system master control application functions.
Updated:2018/03/03
-------------------------------------------------------------------*/
//-----------------------CC2530 Include--------------------------
#include "hal_defs.h"
#include "hal_mcu.h"
#include "hal_board.h"
#include "hal_led.h"
#include "hal_lcd.h"
#include "hal_int.h"
#include "hal_button.h"
#include "hal_buzzer.h"
#include "hal_rf.h"
#include "basic_rf.h"
#include "hal_keypad.h"
#include <string.h>
#include "hal_cc8051.h"
#include "hal_uart.h"
#include "util.h"
#include "M230.h"
#include "Program.h"
//---------------------------Define-----------------------------------
#define RF_CHANNEL                18      // 2.4 GHz RF channel
// BasicRF address definitions
#define PAN_ID		0x1111
#define A_ZONE	0x2222
#define B_ZONE	0x2233
#define C_ZONE	0x2244
#define Master	0x3333
#define APP_PAYLOAD_LENGTH        255	//Packet size
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
static uint8 pTxData[APP_PAYLOAD_LENGTH];	//Transmitter data size
static uint8 pRxData[APP_PAYLOAD_LENGTH];	//Receiver data size
static basicRfCfg_t basicRfConfig;			//RFConfig
/*-------------------------------------------------------------------
pTxData[0] = Mode1 or 2
pTxData[1] = Delay
pTxData[2] to pTxData[9] is custom program array
pTxData[10] if  1 = command, if 2 = observed
-------------------------------------------------------------------*/
//-------------------------variable----------------------------------
uint8 key;
uint8 KeyCount;
uint16 ProgramA[8];
uint8 RxData[3];
uint8 uart_buf[20];
//-------------------------Function---------------------------------
void MasterInit(void);
void Program(uint8 a);
void Client_Program_Order(void);
void Client_Program_Time(void);
uint8 ReadKeyInt(void);
void CommandZone(uint8 zone);
void CommandAction(uint8 zone);
void WriteEEPROM(uint8 zone,uint8 mode);
void AutoReadEEPRom(void);
void halLcdWriteIntToChar(uint8 lcd_line,uint8 lcd_col,uint8 lcd_text);
void ShowZoneMode(uint8 zone);
void SendData(uint8 zone);
void ResetSlave(uint8 zone);
//-------------------------main function----------------------------------
void main(void) 
{
    MasterInit();
	while(1)
	{
		key = halKeypadPushed();
		if(key == 'A' || key == 'B' || key == 'C') CommandZone(key);
		halMcuWaitMs(300); 		
	}
}
//-------------------------initialization function----------------------------------
void MasterInit(void)
{
	// RFConfig
    basicRfConfig.panId = PAN_ID;
    basicRfConfig.channel = RF_CHANNEL;
    basicRfConfig.ackRequest = TRUE;
    #ifdef SECURITY_CCM
        basicRfConfig.securityKey = key;
    #endif
	
	//initialization¡BLCD¡BM230
    halBoardInit();
    halLcdInit();
	M230_Init();
	
    basicRfConfig.myAddr = Master;
    if (basicRfInit(&basicRfConfig) == FAILED){}
    basicRfReceiveOn();

	halLcdWriteString(HAL_LCD_LINE_1,0,"I.O.L_System:M_A");
	halLcdWriteString(HAL_LCD_LINE_2,0,"Target:A B C");

}
/*------------------------------------------------------------------------------------------------------
Client_Program_Order()
the function can custom program
1.input 00~99 then target *(clear) or #(enter)
2.Repeat 8 times
------------------------------------------------------------------------------------------------------*/
void Client_Program_Order()
{	
	KeyCount = 0;
	uint8 ProgramXY[2];
	uint8 ProgramZ = 1;
	halLcdClear();
	halMcuWaitMs(300);
	halLcdWriteString(HAL_LCD_LINE_1,0,"Input Program_1");
	halLcdWriteString(HAL_LCD_LINE_2,0,"__");
	while(ProgramZ < 9)
	{
		halLcdWriteIntToChar(HAL_LCD_LINE_1,14,ProgramZ);
		while(KeyCount < 2)
		{			
			ProgramXY[KeyCount] = ReadKeyInt();
			if(ProgramXY[KeyCount] != 11)
			{		
				key = halKeypadPushed();
				halLcdWriteChar(HAL_LCD_LINE_2,KeyCount,key);
				KeyCount ++;
			}
			halMcuWaitMs(300);
		}
		ProgramA[ProgramZ] = ProgramXY[0] * 10 + ProgramXY[1];
		READProgram(ProgramA[ProgramZ]);
		for(int i = 0; i < 8; i++)
		{
			LedProgram(i);
			halMcuWaitMs(250);
		}
		pTxData[ProgramZ+1] = ProgramA[ProgramZ];
		halLcdWriteString(HAL_LCD_LINE_2,3,"Press * or #");
		key = halKeypadPushed();
		if(key == '#')
		{
			ProgramZ ++;
			KeyCount = 0;
			halLcdWriteString(HAL_LCD_LINE_2,0,"__ Press * or #");
		}
		if(key == '*') 
		{
			halBuzzer(100);
			KeyCount = 0;
			halLcdWriteString(HAL_LCD_LINE_2,0,"__ Press * or #");
		}
		halMcuWaitMs(300);
	}
}
void halLcdWriteIntToChar(uint8 lcd_line,uint8 lcd_col,uint8 lcd_text)
{
	char *pValue = convInt32ToText(lcd_text);
	if(lcd_line == HAL_LCD_LINE_1) halLcdWriteString(HAL_LCD_LINE_1,lcd_col,pValue);
	if(lcd_line == HAL_LCD_LINE_2) halLcdWriteString(HAL_LCD_LINE_2,lcd_col,pValue);
}
/*------------------------------------------------------------------------------------------------------
Client_Program_Time()
------------------------------------------------------------------------------------------------------*/
void Client_Program_Time()
{		
	uint8 ProgramDelay[2];
	uint8 SendTime;
	halLcdWriteString(HAL_LCD_LINE_2,0,"__00ms Delay    ");
	KeyCount = 0;
	while(1)
	{
		while(KeyCount<2)
		{		
			halMcuWaitMs(300);
			if(ReadKeyInt() >= 0 && ReadKeyInt() < 10)
			{
				ProgramDelay[KeyCount] = ReadKeyInt();
				halLcdWriteIntToChar(HAL_LCD_LINE_2,KeyCount,ProgramDelay[KeyCount]);
				KeyCount++;
			}				
		}
		key = halKeypadPushed();
		if(key == '#')
		{
			break;
		}
		if(key == '*') 
		{
			KeyCount = 0;
			halLcdWriteString(HAL_LCD_LINE_2,0,"__00ms Delay    ");
		}
		halMcuWaitMs(300);
	}
	SendTime = ProgramDelay[0] * 10 + ProgramDelay[1];
	pTxData[1] = SendTime;
}
/*------------------------------------------------------------------------------------------------------
ReadKeyInt()
------------------------------------------------------------------------------------------------------*/
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
/*------------------------------------------------------------------------------------------------------
CommandZone(uint8 zone)
------------------------------------------------------------------------------------------------------*/
void CommandZone(uint8 zone)
{
	halLcdClear();
	halLcdWriteString(HAL_LCD_LINE_2,0,"Target : 1 2 3 4");
	switch(zone)
	{
		case 'A':
			halLcdWriteString(HAL_LCD_LINE_1,0,"Send_Zone : S_A ");
			CommandAction(0);			
			break;
		case 'B':
			halLcdWriteString(HAL_LCD_LINE_1,0,"Send_Zone : S_B ");
			CommandAction(1);
			break;
		case 'C':
			halLcdWriteString(HAL_LCD_LINE_1,0,"Send_Zone : S_C ");
			CommandAction(2);
			break;
		default:
			break;
	}
	halMcuWaitMs(1000);
	halLcdClear();
	halLcdWriteString(HAL_LCD_LINE_1,0,"I.O.L_System:M_A");
	halLcdWriteString(HAL_LCD_LINE_2,0,"Target:A B C");
}
/*------------------------------------------------------------------------------------------------------
CommandAction(zone)
------------------------------------------------------------------------------------------------------*/
void CommandAction(uint8 zone)
{
	uint8 Mode;
	while(1)
	{
		Mode = ReadKeyInt();
		if(Mode > 0 && Mode < 6) break;
	}
	switch(Mode)
	{	
		case 1:
			halLcdWriteString(HAL_LCD_LINE_2,0,"Send_Mode : 1     ");
			WriteEEPROM(zone,1);
			SendData(zone);
			halMcuWaitMs(1000);
			ShowZoneMode(zone);
			break;			
		case 2:
			Client_Program_Order();
			halLcdWriteString(HAL_LCD_LINE_2,0,"Send_Mode : 2     ");
			WriteEEPROM(zone,2);
			SendData(zone);
			halMcuWaitMs(1000);
			ShowZoneMode(zone);
			break;
		case 3:
			Client_Program_Time();
			halLcdWriteString(HAL_LCD_LINE_2,0,"Send_Mode : 3     ");
			WriteEEPROM(zone,3);
			SendData(zone);
			halMcuWaitMs(1000);
			ShowZoneMode(zone);
			break;
		case 4:
			ShowZoneMode(zone);
			break;
		case 5:
			ResetSlave(zone);
			break;
	}
}
/*------------------------------------------------------------------------------------------------------
ShowZoneMode(zone)
------------------------------------------------------------------------------------------------------*/
void ShowZoneMode(uint8 zone)
{
    halLcdClear();
	uint8 check;
	halLcdWriteString(HAL_LCD_LINE_1,0,"Slave Working");
	halLcdWriteString(HAL_LCD_LINE_2,0,"Program:       0");
	while(1)
	{
		basicRfReceive(pRxData, APP_PAYLOAD_LENGTH, NULL);
		switch(pRxData[0])
		{
			case 0x01:
				RxData[0] = pRxData[1];
				break;
			case 0x02:
				RxData[1] = pRxData[1];
				break;
			case 0x03:
				RxData[2] = pRxData[1];
				break;
		}
		halLcdWriteString(HAL_LCD_LINE_2,14,"00");
		switch(zone)
		{
			case 0:
				if(RxData[zone] < 10)
				{
					halLcdWriteString(HAL_LCD_LINE_2,8,"0");
					halLcdWriteIntToChar(HAL_LCD_LINE_2,9,RxData[zone]);
				}
				else
				{
					halLcdWriteIntToChar(HAL_LCD_LINE_2,8,RxData[zone]);
				}
				halLcdWriteIntToChar(HAL_LCD_LINE_2,12,M230_ReadEEPROM(1) / 10);
				halLcdWriteIntToChar(HAL_LCD_LINE_2,13,M230_ReadEEPROM(1) % 10);
				uart_buf[0] = 0x000A;	//Slave_ID
				uart_buf[1] = RxData[zone];		//Program_ID				
				uart_buf[2] = M230_ReadEEPROM(1);		//Delay_time
				halUartWrite(uart_buf,3);
				halMcuWaitMs(1000);
				break;
			case 1:
				if(RxData[zone] < 10)
				{
					halLcdWriteString(HAL_LCD_LINE_2,8,"0");
					halLcdWriteIntToChar(HAL_LCD_LINE_2,9,RxData[zone]);
				}
				else
				{
					halLcdWriteIntToChar(HAL_LCD_LINE_2,8,RxData[zone]);
				}
				halLcdWriteIntToChar(HAL_LCD_LINE_2,12,M230_ReadEEPROM(11) / 10);
				halLcdWriteIntToChar(HAL_LCD_LINE_2,13,M230_ReadEEPROM(11) % 10);		
				uart_buf[0] = 0x000B;	//Slave_ID
				uart_buf[1] = RxData[zone];		//Program_ID				
				uart_buf[2] = M230_ReadEEPROM(11);		//Delay_time
				halUartWrite(uart_buf,3);
				halMcuWaitMs(1000);
				break;
			case 2:
				if(RxData[zone] < 10)
				{
					halLcdWriteString(HAL_LCD_LINE_2,8,"0");
					halLcdWriteIntToChar(HAL_LCD_LINE_2,9,RxData[zone]);
				}
				else
				{
					halLcdWriteIntToChar(HAL_LCD_LINE_2,8,RxData[zone]);
				}
				halLcdWriteIntToChar(HAL_LCD_LINE_2,12,M230_ReadEEPROM(21) / 10);
				halLcdWriteIntToChar(HAL_LCD_LINE_2,13,M230_ReadEEPROM(21) % 10);
				uart_buf[0] = 0x000C;	//Slave_ID
				uart_buf[1] = RxData[zone];		//Program_ID				
				uart_buf[2] = M230_ReadEEPROM(21);		//Delay_time
				halUartWrite(uart_buf,3);
				halMcuWaitMs(1000);
				break;
		}
		if(RxData[zone] == 0 && check < 6)
		{
			check++;
			halLcdWriteString(HAL_LCD_LINE_1,0,"Slave Return 0");
		}
		if(RxData[zone] == 0 && check > 5)
		{
			halLcdWriteString(HAL_LCD_LINE_1,0,"Slave No Work");
		}
		if(RxData[zone] != 0)
		{
			halLcdWriteString(HAL_LCD_LINE_1,0,"Slave Working   ");
		}
		key = halKeypadPushed();
		if(key == '*') break;
	}
	check = 0;
	halLcdClear();
	halLcdWriteString(HAL_LCD_LINE_1,0,"I.O.L_System:M_A");
	halLcdWriteString(HAL_LCD_LINE_2,0,"Wait.....");
}
/*------------------------------------------------------------------------------------------------------
M230
0			S_A_Mode 1 or 2
10		S_B_Mode 1 or 2
20		S_C_Mode 1 or 2
2~9		S_A_Mode2 Program1~8
12~19	S_B_Mode2 Program1~8
22~29	S_C_Mode2 Program1~8
1			S_A Delay
11		S_B Delay
21		S_C Delay
------------------------------------------------------------------------------------------------------*/
void WriteEEPROM(uint8 zone,uint8 mode)
{
	uint8 JJY;
	if(mode == 1)
	{
		JJY = zone * 10;
		M230_WriteEEPROM(JJY,1);
	}
	if(mode == 2)
	{
		JJY = zone * 10;
		M230_WriteEEPROM(JJY,2);
		for(uint8 i = 2;i < 10;i++)
		{
			JJY = zone * 10 + i;
			M230_WriteEEPROM(JJY,pTxData[i]);
		}
	}
	if(mode == 3)
	{
		JJY = zone * 10 + 1;
		M230_WriteEEPROM(JJY,pTxData[1]);
	}
}
void AutoReadEEPRom(void)
{
	uint8 JJY;
	for(uint8 i = 0; i < 3; i++)
	{
		for(uint8 j = 0; j < 10; j++)
		{
			JJY = i * 10 + j;
			pTxData[j] = M230_ReadEEPROM(JJY);
		}
		if(i == 0) basicRfSendPacket(A_ZONE,pTxData,APP_PAYLOAD_LENGTH);
		if(i == 1) basicRfSendPacket(B_ZONE,pTxData,APP_PAYLOAD_LENGTH);
		if(i == 2) basicRfSendPacket(C_ZONE,pTxData,APP_PAYLOAD_LENGTH);
	}
}
void SendData(uint8 zone)
{
	uint8 JJY, EAT;
	EAT = 30 + zone;
	for(uint8 j = 0; j < 10; j++)
	{
			JJY = zone * 10 + j;
			pTxData[j] = M230_ReadEEPROM(JJY);
	}
	pTxData[10] = M230_ReadEEPROM(EAT);
		if(zone == 0) basicRfSendPacket(A_ZONE,pTxData,APP_PAYLOAD_LENGTH);
		if(zone == 1) basicRfSendPacket(B_ZONE,pTxData,APP_PAYLOAD_LENGTH);
		if(zone == 2) basicRfSendPacket(C_ZONE,pTxData,APP_PAYLOAD_LENGTH);
}
void ResetSlave(uint8 zone)
{
	pTxData[0] = 5;
	if(zone == 0) basicRfSendPacket(A_ZONE,pTxData,APP_PAYLOAD_LENGTH);
	if(zone == 1) basicRfSendPacket(B_ZONE,pTxData,APP_PAYLOAD_LENGTH);
	if(zone == 2) basicRfSendPacket(C_ZONE,pTxData,APP_PAYLOAD_LENGTH);
	halLcdClear();
	halLcdWriteString(HAL_LCD_LINE_1,0,"Reset Slave");
	halMcuWaitMs(1000);
}