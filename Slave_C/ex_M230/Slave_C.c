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
#include "basic_rf.h"
#include "hal_keypad.h"

//C_Compiler
#include <string.h>

//Local_Define
#define LINE1                           0x00
#define LINE2                           0x40
#define SET_DISPLAY_LINE(line)          lcdControl(0x80 | (line))

// Application parameters
#define RF_CHANNEL                18      // 2.4 GHz RF channel

// BasicRF address definitions
#define PAN_ID                	0x1111
#define C_ZONE           		0x2244		//Slave-A位址
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

uint8 ProgramROM[8];
uint8 ProgramDelayI[4];
uint8 ProgramOrder[4];
uint8 ProgramText;
uint8 key;
uint8 KeyCount;
uint16 ProgramDelay;

void LcdWrite(void);
void Program(uint8 b);
void Mode(uint8 a);
void Client(void);
uint8 ReadKeyInt(void);

void main(void){   

	basicRfConfig.panId = PAN_ID;			//指定RF ID
    basicRfConfig.channel = RF_CHANNEL;		//指定RF Channel
    basicRfConfig.ackRequest = TRUE;		//封包傳遞會有ACK回應
    #ifdef SECURITY_CCM
        basicRfConfig.securityKey = key;	//封包傳遞安全機制
    #endif 

	//初始化板子
	halBoardInit();
	
	//已通電提示
	halLedSet(8);
    halBuzzer(300);
	
	basicRfConfig.myAddr = C_ZONE;
    if (basicRfInit(&basicRfConfig) == FAILED){}
	
	//使RF接收端為常開
    basicRfReceiveOn();		
	
	ProgramDelay = 300;
    halLcdWriteString(HAL_LCD_LINE_1,0,"I.O.L_System:S_C");
    
    while (TRUE){
		
        while (!basicRfPacketIsReady()){
            halLedToggle(7);
            halMcuWaitMs(10);
        }
		
		while(basicRfReceive(pRxData, APP_PAYLOAD_LENGTH, NULL) > 0){
			
			switch(pRxData[0]){
				
				case 0x0001:
					
					halBuzzer(250);
					//LcdWrite();
					halLcdClear();
					halLcdWriteString(HAL_LCD_LINE_1,0,"Mode");
					halLcdWriteChar(HAL_LCD_LINE_1, 4, '1');
					halLcdWriteString(HAL_LCD_LINE_1,5,",Program");
					
					
					while(basicRfReceive(pRxData, APP_PAYLOAD_LENGTH, NULL) > 0){
						
						if(pRxData[0] != 0x0001){
							
							halLcdWriteString(HAL_LCD_LINE_2,10,"Break");
							halMcuWaitMs(3000);
							break;
			
						}else if(pRxData[0] == 0x0001){
		
							Mode(1);
						}
					}
				
				break;
				
				case 0x0002:
				
					halBuzzer(250);
					//LcdWrite();
					halLcdClear();
					halLcdWriteString(HAL_LCD_LINE_1,0,"Mode");
					halLcdWriteChar(HAL_LCD_LINE_1, 4, '2');
					halLcdWriteString(HAL_LCD_LINE_1,5,",Program");
					
					KeyCount = 0;
					halLcdWriteString(HAL_LCD_LINE_2,0,"Input:");
					halMcuWaitMs(300);
						
					Client(); 
					
					while(basicRfReceive(pRxData, APP_PAYLOAD_LENGTH, NULL) > 0){
						
						if(pRxData[0] != 0x0002){
							
							halLcdWriteString(HAL_LCD_LINE_2,10,"Break");
							halMcuWaitMs(3000);
							break;
								
						}else if(pRxData[0] == 0x0002){
								
							Mode(2);	
						}
					}
				
				break;
				
				case 3:
		
					KeyCount = 0;
					halLcdWriteString(HAL_LCD_LINE_1,0,"Input Delay:   ");
					halLcdWriteString(HAL_LCD_LINE_2,0,"0000 ms         ");
		
					while(basicRfReceive(pRxData, APP_PAYLOAD_LENGTH, NULL) > 0){
						
						if(pRxData[0] != 0x0003){
							
							halLcdWriteString(HAL_LCD_LINE_2,10,"Break");
							halMcuWaitMs(3000);
							break;
							
						}else if(pRxData[0] == 0x0003){
						
							Mode(3);
						
						}
						
					}

				break;
				
				default:
				
					halLcdWriteString(HAL_LCD_LINE_1,0,"Nothing");
			}
		}   
    }
}

void LcdWrite(void){
     halLcdClear();
     halLcdWriteString(HAL_LCD_LINE_1,0,"Mode");
     halLcdWriteChar(HAL_LCD_LINE_1, 4, key);
     halLcdWriteString(HAL_LCD_LINE_1,5,",Program");
}

void Mode(uint8 a){
    switch(a)
    {
		case 1:

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
			
		break;
		
		case 2:
		    
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
		
		break;
		
		case 3:
		
			//uint8 ProgramDelayI[4];
		
			while(KeyCount<4){
				
			    halMcuWaitMs(300);
				if(ReadKeyInt() >= 0 && ReadKeyInt() < 10){
					ProgramDelayI[KeyCount] = ReadKeyInt();
					//char *pValue = convInt32ToText(ProgramDelayI[KeyCount]);
					//halLcdWriteString(HAL_LCD_LINE_2,KeyCount,pValue);
					halLcdDisplayUint8(HAL_LCD_LINE_2,KeyCount,HAL_LCD_RADIX_DEC,ProgramDelayI[KeyCount]);
					KeyCount++;
				}				
			}
			ProgramDelay = ProgramDelayI[0] * 1000 + ProgramDelayI[1] * 100 + ProgramDelayI[2] *10 + ProgramDelayI[3];
			halLcdWriteString(HAL_LCD_LINE_1,0,"Set_time_Sucess!");
		
		break;
		
    }
}

void Program(uint8 b){
    
	switch(b){
		case 1:
			ProgramText = '1';
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
		case 2:
			ProgramText = '2';
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
		case 3:
			ProgramText = '3';
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
		case 4:
			ProgramText = '4';
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
    }	
}

void Client(void){
	
	while(KeyCount < 4){
		
		char key = halKeypadPushed();
		if (key > 0){
			if (key == '1'){
				ProgramOrder[KeyCount] = 1;
			}if (key == '2'){
				ProgramOrder[KeyCount] = 2;
			}if (key == '3'){
				ProgramOrder[KeyCount] = 3;
			}if (key == '4'){					
				ProgramOrder[KeyCount] = 4;
			}
			
			halLcdWriteChar(HAL_LCD_LINE_2,6+KeyCount,key);
			KeyCount++;
		}
		halMcuWaitMs(300);
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



