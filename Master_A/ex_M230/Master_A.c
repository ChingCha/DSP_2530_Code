//LED_Matrix
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

//C_Compiler
#include <string.h>

//M230.h
#include "hal_cc8051.h"
#include "hal_uart.h"
#include "util.h"
#include "M230.h"

#define RF_CHANNEL                18      // 2.4 GHz RF channel

// BasicRF address definitions
#define PAN_ID		0x1111
#define A_ZONE	0x2222
#define B_ZONE	0x2233
#define C_ZONE	0x2244
#define Master	0x3333

#define APP_PAYLOAD_LENGTH        255	//�w�q�ʥ]�ǻ��j�p


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
static uint8 pTxData[APP_PAYLOAD_LENGTH];	//Tx��ƪ��W��
static uint8 pRxData[APP_PAYLOAD_LENGTH];	//Rx��ƪ��W��
typedef struct RxSlave
{
	uint16 Slave_Num;
	uint8 Slave_Data1;
	uint8 Slave_Data2;
};
static basicRfCfg_t basicRfConfig;			//�ŧiRFConfig�պA
/******************************************************
pTxData[0] = Mode1 or 2
pTxData[1] = Delay
pTxData[2] to pTxData[9] �ۭq8�Ӹ`�ض��Ƕǰe
******************************************************/
//system.c Variables
uint8 key;
uint8 KeyCount;
uint16 ProgramA[8];
uint8 ShowMode[3];
uint8 RxData[3];
uint8 SlaveNum;
//system.c Function
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
void RxRegister(void);
//�D���

void main(void) 
{
    MasterInit();
	while(1)
	{

		RxRegister();
		key = halKeypadPushed();
		if(key == 'A' || key == 'B' || key == 'C') CommandZone(key);
		halMcuWaitMs(300); 		
	}
}
void MasterInit(void)
{
	// �t�mRF�Ѽ�
    basicRfConfig.panId = PAN_ID;
    basicRfConfig.channel = RF_CHANNEL;
    basicRfConfig.ackRequest = TRUE;
    #ifdef SECURITY_CCM
        basicRfConfig.securityKey = key;
    #endif
	
	// ��l���X�R�O�BLCD�B�I�x�}�BM230
    halBoardInit();
    halLcdInit();
	M230_Init();
	
	// �˸m�w�g�q�q������
    halLedSet(8);
    halBuzzer(300);
	
    basicRfConfig.myAddr = Master;
    if (basicRfInit(&basicRfConfig) == FAILED){}
    basicRfReceiveOn();

	halLcdWriteString(HAL_LCD_LINE_1,0,"I.O.L_System:M_A");
	halLcdWriteString(HAL_LCD_LINE_2,0,"Target:ABC___");
	SlaveNum = 0;
	ShowMode[0] = 0;
	ShowMode[1] = 0;
	ShowMode[2] = 0;
	struct RxSlave Slave[3];
}
/***************************
Client_Program_Order()
1.��J00~99�������ƭȡA��J�����U#(Enter�i���x�s)
2.�̦h�ۭq8�Ӹ`�ض���
3.������ǭȡA��^
****************************/
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
				halBuzzer(100);
				KeyCount ++;
			}
			halMcuWaitMs(300);
		}
		ProgramA[ProgramZ] = ProgramXY[0] * 10 + ProgramXY[1];
		pTxData[ProgramZ+1] = ProgramA[ProgramZ];
		halLcdWriteString(HAL_LCD_LINE_2,3,"Press * or #");
		key = halKeypadPushed();
		if(key == '#')
		{
			halBuzzer(100);
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
/*********************************************************
halLcdWriteIntToChar(LCD�ĴX��,���ĴX�Ӧr,��ܪ��ƭ�)
�i�N�ƭȦ۰��ഫ���r����ܦbLCD�W(���w�@�Ӧr?������)
*********************************************************/
void halLcdWriteIntToChar(uint8 lcd_line,uint8 lcd_col,uint8 lcd_text)
{
	char *pValue = convInt32ToText(lcd_text);
	if(lcd_line == HAL_LCD_LINE_1) halLcdWriteString(HAL_LCD_LINE_1,lcd_col,pValue);
	if(lcd_line == HAL_LCD_LINE_2) halLcdWriteString(HAL_LCD_LINE_2,lcd_col,pValue);
}
/***************************
Client_Program_Time()
***************************/
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
/********************
ReadKeyInt()
�μƭȫ��A�^����L��
********************/
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
/*************************
CommandZone(uint8 zone)
1.�P�_�n�e�����@��A~F
2.�M��LCD�ALCD��ܭn�ǰe���I
3.�i�JCommandAction�Ƶ{��Ū���n�i�檺�Ҧ�
4.�N��Ƥ@�ְe�X
5.�w�������A
*************************/
void CommandZone(uint8 zone)
{
	halBuzzer(100);
	halLcdClear();
	halLcdWriteString(HAL_LCD_LINE_2,0,"Target : 1 2 3 4");
	switch(zone)
	{
		case 'A':
			halLcdWriteString(HAL_LCD_LINE_1,0,"Send_Zone : S_A ");
			CommandAction(0);
			SendData(0);
			break;
		case 'B':
			halLcdWriteString(HAL_LCD_LINE_1,0,"Send_Zone : S_B ");
			CommandAction(1);
			SendData(1);
			break;
		case 'C':
			halLcdWriteString(HAL_LCD_LINE_1,0,"Send_Zone : S_C ");
			CommandAction(2);
			SendData(2);
			break;
/*		case 'D':
			break;
		case 'E':
			break;
		case 'F':
			break;
*/
		default:
			break;
	}
	halMcuWaitMs(1000);
	halLcdClear();
	halLcdWriteString(HAL_LCD_LINE_1,0,"I.O.L_System:M_A");
	halLcdWriteString(HAL_LCD_LINE_2,0,"Target:ABC___");
}
/*****************************
CommandAction(uint8 zone)
1.�P�_��J���Ҧ�1~3
2.�]�w�ϰ�a�}?
3.LCD���
4.�^�ǼҦ����ƭ�
*****************************/
void CommandAction(uint8 zone)
{
	uint8 Mode;
	while(1)
	{
		Mode = ReadKeyInt();
		if(Mode > 0 && Mode < 5) break;
	}
	halBuzzer(100);
	switch(Mode)
	{			
		case 1:
			halLcdWriteString(HAL_LCD_LINE_2,0,"Send_Mode : 1 ");
			WriteEEPROM(zone,1);
			break;			
		case 2:
			Client_Program_Order();
			halLcdWriteString(HAL_LCD_LINE_2,0,"Send_Mode : 2 ");
			WriteEEPROM(zone,2);
			break;
		case 3:
			Client_Program_Time();
			halLcdWriteString(HAL_LCD_LINE_2,0,"Send_Mode : 3 ");
			WriteEEPROM(zone,3);
			break;
		case 4:
			ShowZoneMode(zone);
			break;
	}
}
/*********************
ShowZoneMode()
��ܷ�e�C�ӼҦ��Ҷi�檺�`��(��K�ʴ�)
*********************/
void ShowZoneMode(uint8 zone)
{
    halLcdClear();
	halLcdWriteString(HAL_LCD_LINE_1,0,"Slave  Woking");
	halLcdWriteString(HAL_LCD_LINE_2,0,"Program:");
	while (!basicRfPacketIsReady())
	{
				halLedToggle(7);
				halMcuWaitMs(100);
	}
	while(basicRfReceive(pRxData, APP_PAYLOAD_LENGTH, NULL) > 0)
	{
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
		switch(zone)
		{
			case 0:
				halLcdWriteString(HAL_LCD_LINE_1,5,"A");
				halLcdWriteIntToChar(HAL_LCD_LINE_2,9,RxData[zone]);				  				
				break;
			case 1:
				halLcdWriteString(HAL_LCD_LINE_1,5,"B");
				halLcdWriteIntToChar(HAL_LCD_LINE_2,9,RxData[zone]);				  
				break;
			case 2:
				halLcdWriteString(HAL_LCD_LINE_1,5,"C");
				halLcdWriteIntToChar(HAL_LCD_LINE_2,9,RxData[zone]);	
				break;
		}
		key = halKeypadPushed();
		if(key == '*') break;
	}	
	halLcdClear();
	halLcdWriteString(HAL_LCD_LINE_1,0,"I.O.L_System:M_A");
	halLcdWriteString(HAL_LCD_LINE_2,0,"Target:ABC");
}
/**************************************************
M230	
��m	�\��
0			S_A_Mode 1 or 2
10		S_B_Mode 1 or 2
20		S_C_Mode 1 or 2
2~9	S_A_Mode2 Program1~8
12~19	S_B_Mode2 Program1~8
22~29	S_C_Mode2 Program1~8
1		S_A Delay
11		S_B Delay
21		S_C Delay
**************************************************/
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
	uint8 JJY;
	for(uint8 j = 0; j < 10; j++)
	{
			JJY = zone * 10 + j;
			pTxData[j] = M230_ReadEEPROM(JJY);
	}
		if(zone == 0) basicRfSendPacket(A_ZONE,pTxData,APP_PAYLOAD_LENGTH);
		if(zone == 1) basicRfSendPacket(B_ZONE,pTxData,APP_PAYLOAD_LENGTH);
		if(zone == 2) basicRfSendPacket(C_ZONE,pTxData,APP_PAYLOAD_LENGTH);
}

void RxRegister(void)
{	
	uint8 seqNumber;
	seqNumber = rxi.seqNumber;
}