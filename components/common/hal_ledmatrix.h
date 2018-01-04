//MAX7219暫存器巨集定義

#define DIGIT0		 	0x01	//A販賣機暫存器
#define DIGIT1		 	0x02	//B販賣機暫存器
#define DIGIT2			0x03
#define DIGIT7			0x08
#define REG_DECODE        0x09                        // "decode mode" register
#define REG_INTENSITY     0x0a                        // "intensity" register
#define REG_SCAN_LIMIT    0x0b                        // "scan limit" register
#define REG_SHUTDOWN      0x0c                        // "shutdown" register
#define REG_DISPLAY_TEST  0x0f                        // "display test" register


//CC2530腳位功能巨集定義

#define MAX7219DIN    P0_4		//CC2530 P0_4>>>模組DIN腳位
#define MAX7219LOAD   P0_5		//CC2530 P0_5>>>模組CS(LOAD)腳位
#define MAX7219CLK    P0_6		//CC2530 P0_6>>>模組CLK腳位

void MAX7219_SendByte (unsigned char DINout);
void MAX7219_Write (unsigned char reg_number, unsigned char DINout);
void MAX7219_Init(void);
void MAX7219_Clear (void);
void MAX7219_SetBrightness (char brightness);
void Delay(unsigned int t);
void A1_Warning();
void A2_Warning();
void B1_Warning();
void B2_Warning();