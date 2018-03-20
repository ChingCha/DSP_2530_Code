//-------------------------------------------------------------------
// Filename: Program.c
// Description: I.O.L Program 00~99
//-------------------------------------------------------------------
//-------------------------------------------------------------------
// INCLUDES
//-------------------------------------------------------------------
#include "hal_defs.h"
#include "hal_mcu.h"
#include "hal_board.h"
#include "hal_lcd.h"
#include "hal_led.h"
#include "hal_int.h"
#include "Program.h"
#include "hal_cc8051.h"

//-------------------------------------------------------------------
// LOCAL VARIABLES
//-------------------------------------------------------------------
uint8 ProgramText;
uint8 ProgramROM[8];
//-------------------------------------------------------------------
void LedProgram(uint8 a)
{
	MCU_PORT_OUTPUT(0, ProgramROM[a]);
    halLedSetPort(ProgramROM[a]);
}
void READProgram(uint8 b)
{   
	switch(b)
	{
		case 1:
			ProgramROM[0] = 0x00;
			ProgramROM[1] = 0xFF;
			ProgramROM[2] = 0x00;
			ProgramROM[3] = 0xFF;
			ProgramROM[4] = 0x00;
			ProgramROM[5] = 0xFF;
			ProgramROM[6] = 0x00;
			ProgramROM[7] = 0xFF;
			break;
		case 2:
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
			ProgramROM[0] = 0x80;
			ProgramROM[1] = 0x40;
			ProgramROM[2] = 0x20;
			ProgramROM[3] = 0x10;
			ProgramROM[4] = 0x08;
			ProgramROM[5] = 0x04;
			ProgramROM[6] = 0x02;
			ProgramROM[7] = 0x01;
			break;
		case 4:
			ProgramROM[0] = 0x01;
			ProgramROM[1] = 0x03;
			ProgramROM[2] = 0x07;
			ProgramROM[3] = 0x0F;
			ProgramROM[4] = 0x1F;
			ProgramROM[5] = 0x3F;
			ProgramROM[6] = 0x7F;
			ProgramROM[7] = 0xFF;
			break;
		case 5:
			ProgramROM[0] = 0x80;
			ProgramROM[1] = 0xC0;
			ProgramROM[2] = 0xE0;
			ProgramROM[3] = 0xF0;
			ProgramROM[4] = 0xF8;
			ProgramROM[5] = 0xFC;
			ProgramROM[6] = 0xFE;
			ProgramROM[7] = 0xFF;
			break;
		case 6:
			ProgramROM[0] = 0x11;
			ProgramROM[1] = 0x00;
			ProgramROM[2] = 0x22;
			ProgramROM[3] = 0x00;
			ProgramROM[4] = 0x44;
			ProgramROM[5] = 0x00;
			ProgramROM[6] = 0x88;
			ProgramROM[7] = 0x00;
			break;
		case 7:
			ProgramROM[0] = 0x88;
			ProgramROM[1] = 0x00;
			ProgramROM[2] = 0x44;
			ProgramROM[3] = 0x00;
			ProgramROM[4] = 0x22;
			ProgramROM[5] = 0x00;
			ProgramROM[6] = 0x11;
			ProgramROM[7] = 0x00;
			break;
		case 8:
			ProgramROM[0] = 0x81;
			ProgramROM[1] = 0x42;
			ProgramROM[2] = 0x24;
			ProgramROM[3] = 0x18;
			ProgramROM[4] = 0x24;
			ProgramROM[5] = 0x42;
			ProgramROM[6] = 0x81;
			ProgramROM[7] = 0x00;
			break;
		case 9:
			ProgramROM[0] = 0x18;
			ProgramROM[1] = 0x24;
			ProgramROM[2] = 0x42;
			ProgramROM[3] = 0x81;
			ProgramROM[4] = 0x42;
			ProgramROM[5] = 0x24;
			ProgramROM[6] = 0x18;
			ProgramROM[7] = 0x00;
			break;
		case 10:
			ProgramROM[0] = 0x81;
			ProgramROM[1] = 0xC3;
			ProgramROM[2] = 0xE7;
			ProgramROM[3] = 0xFF;
			ProgramROM[4] = 0xE7;
			ProgramROM[5] = 0xC3;
			ProgramROM[6] = 0x81;
			ProgramROM[7] = 0x00;
			break;
		case 11:
			ProgramROM[0] = 0x01;
			ProgramROM[1] = 0x05;
			ProgramROM[2] = 0x15;
			ProgramROM[3] = 0x55;
			ProgramROM[4] = 0x15;
			ProgramROM[5] = 0x05;
			ProgramROM[6] = 0x01;
			ProgramROM[7] = 0x00;
			break;
		case 12:
			ProgramROM[0] = 0x02;
			ProgramROM[1] = 0x0A;
			ProgramROM[2] = 0x2A;
			ProgramROM[3] = 0xAA;
			ProgramROM[4] = 0x2A;
			ProgramROM[5] = 0x0A;
			ProgramROM[6] = 0x02;
			ProgramROM[7] = 0x00;
			break;
		case 13:
			ProgramROM[0] = 0x01;
			ProgramROM[1] = 0x05;
			ProgramROM[2] = 0x15;
			ProgramROM[3] = 0x55;
			ProgramROM[4] = 0x15;
			ProgramROM[5] = 0x05;
			ProgramROM[6] = 0x01;
			ProgramROM[7] = 0x00;
			break;
		case 14:
			ProgramROM[0] = 0x02;
			ProgramROM[1] = 0x0A;
			ProgramROM[2] = 0x2A;
			ProgramROM[3] = 0xAA;
			ProgramROM[4] = 0xEA;
			ProgramROM[5] = 0xFA;
			ProgramROM[6] = 0xFE;
			ProgramROM[7] = 0xFF;
			break;
		case 15:
			ProgramROM[0] = 0xFF;
			ProgramROM[1] = 0xFE;
			ProgramROM[2] = 0xFA;
			ProgramROM[3] = 0xEA;
			ProgramROM[4] = 0xAA;
			ProgramROM[5] = 0x2A;
			ProgramROM[6] = 0x0A;
			ProgramROM[7] = 0x02;
			break;
		case 16:
			ProgramROM[0] = 0xFF;
			ProgramROM[1] = 0xFD;
			ProgramROM[2] = 0xF5;
			ProgramROM[3] = 0xD5;
			ProgramROM[4] = 0x55;
			ProgramROM[5] = 0x15;
			ProgramROM[6] = 0x05;
			ProgramROM[7] = 0x01;
			break;
		case 17:
			ProgramROM[0] = 0x01;
			ProgramROM[1] = 0x05;
			ProgramROM[2] = 0x0A;
			ProgramROM[3] = 0x14;
			ProgramROM[4] = 0x28;
			ProgramROM[5] = 0x50;
			ProgramROM[6] = 0x41;
			ProgramROM[7] = 0x82;
			break;
		case 18:
			ProgramROM[0] = 0xA0;
			ProgramROM[1] = 0x50;
			ProgramROM[2] = 0x28;
			ProgramROM[3] = 0x14;
			ProgramROM[4] = 0x0A;
			ProgramROM[5] = 0x05;
			ProgramROM[6] = 0x82;
			ProgramROM[7] = 0x41;
			break;
		case 19:
			ProgramROM[0] = 0x11;
			ProgramROM[1] = 0x22;
			ProgramROM[2] = 0x44;
			ProgramROM[3] = 0x88;
			ProgramROM[4] = 0x44;
			ProgramROM[5] = 0x22;
			ProgramROM[6] = 0x11;
			ProgramROM[7] = 0x00;
			break;
		case 20:
			ProgramROM[0] = 0x88;
			ProgramROM[1] = 0x44;
			ProgramROM[2] = 0x22;
			ProgramROM[3] = 0x11;
			ProgramROM[4] = 0x22;
			ProgramROM[5] = 0x44;
			ProgramROM[6] = 0x88;
			ProgramROM[7] = 0x00;
			break;
		case 21:
			ProgramROM[0] = 0x39;
			ProgramROM[1] = 0x27;
			ProgramROM[2] = 0x41;
			ProgramROM[3] = 0x04;
			ProgramROM[4] = 0x42;
			ProgramROM[5] = 0x08;
			ProgramROM[6] = 0x43;
			ProgramROM[7] = 0x12;
			break;
		case 22:
			ProgramROM[0] = 0x44;
			ProgramROM[1] = 0x16;
			ProgramROM[2] = 0x45;
			ProgramROM[3] = 0x20;
			ProgramROM[4] = 0x46;
			ProgramROM[5] = 0x24;
			ProgramROM[6] = 0x47;
			ProgramROM[7] = 0x28;
			break;
		case 23:
			ProgramROM[0] = 0x48;
			ProgramROM[1] = 0x32;
			ProgramROM[2] = 0x49;
			ProgramROM[3] = 0x36;
			ProgramROM[4] = 0x51;
			ProgramROM[5] = 0x05;
			ProgramROM[6] = 0x52;
			ProgramROM[7] = 0x10;
			break;
		case 24:
			ProgramROM[0] = 0x53;
			ProgramROM[1] = 0x15;
			ProgramROM[2] = 0x54;
			ProgramROM[3] = 0x20;
			ProgramROM[4] = 0x55;
			ProgramROM[5] = 0x25;
			ProgramROM[6] = 0x56;
			ProgramROM[7] = 0x30;
			break;
		case 25:
			ProgramROM[0] = 0x57;
			ProgramROM[1] = 0x35;
			ProgramROM[2] = 0x58;
			ProgramROM[3] = 0x40;
			ProgramROM[4] = 0x59;
			ProgramROM[5] = 0x45;
			ProgramROM[6] = 0x61;
			ProgramROM[7] = 0x06;
			break;
		case 26:
			ProgramROM[0] = 0x62;
			ProgramROM[1] = 0x12;
			ProgramROM[2] = 0x63;
			ProgramROM[3] = 0x18;
			ProgramROM[4] = 0x64;
			ProgramROM[5] = 0x24;
			ProgramROM[6] = 0x71;
			ProgramROM[7] = 0x07;
			break;
		case 27:
			ProgramROM[0] = 0x72;
			ProgramROM[1] = 0x14;
			ProgramROM[2] = 0x73;
			ProgramROM[3] = 0x21;
			ProgramROM[4] = 0x74;
			ProgramROM[5] = 0x28;
			ProgramROM[6] = 0x75;
			ProgramROM[7] = 0x35;
			break;
		case 28:
			ProgramROM[0] = 0x76;
			ProgramROM[1] = 0x42;
			ProgramROM[2] = 0x77;
			ProgramROM[3] = 0x49;
			ProgramROM[4] = 0x78;
			ProgramROM[5] = 0x56;
			ProgramROM[6] = 0x79;
			ProgramROM[7] = 0x63;
			break;
		case 29:
			ProgramROM[0] = 0x81;
			ProgramROM[1] = 0x08;
			ProgramROM[2] = 0x82;
			ProgramROM[3] = 0x16;
			ProgramROM[4] = 0x83;
			ProgramROM[5] = 0x24;
			ProgramROM[6] = 0x84;
			ProgramROM[7] = 0x32;
			break;
		case 30:
			ProgramROM[0] = 0x85;
			ProgramROM[1] = 0x40;
			ProgramROM[2] = 0x86;
			ProgramROM[3] = 0x48;
			ProgramROM[4] = 0x87;
			ProgramROM[5] = 0x56;
			ProgramROM[6] = 0x88;
			ProgramROM[7] = 0x64;
			break;
		case 31:
			ProgramROM[0] = 0x89;
			ProgramROM[1] = 0x72;
			ProgramROM[2] = 0x91;
			ProgramROM[3] = 0x09;
			ProgramROM[4] = 0x92;
			ProgramROM[5] = 0x18;
			ProgramROM[6] = 0x93;
			ProgramROM[7] = 0x27;
			break;
		case 32:
			ProgramROM[0] = 0x94;
			ProgramROM[1] = 0x36;
			ProgramROM[2] = 0x95;
			ProgramROM[3] = 0x48;
			ProgramROM[4] = 0x96;
			ProgramROM[5] = 0x54;
			ProgramROM[6] = 0x97;
			ProgramROM[7] = 0x63;
			break;
		case 33:
			ProgramROM[0] = 0x98;
			ProgramROM[1] = 0x72;
			ProgramROM[2] = 0x99;
			ProgramROM[3] = 0x81;
			ProgramROM[4] = 0xA1;
			ProgramROM[5] = 0x0A;
			ProgramROM[6] = 0xA2;
			ProgramROM[7] = 0x20;
			break;
		case 34:
			ProgramROM[0] = 0xA3;
			ProgramROM[1] = 0x30;
			ProgramROM[2] = 0xA4;
			ProgramROM[3] = 0x40;
			ProgramROM[4] = 0xA5;
			ProgramROM[5] = 0x50;
			ProgramROM[6] = 0xA6;
			ProgramROM[7] = 0x60;
			break;
		case 35:
			ProgramROM[0] = 0xA7;
			ProgramROM[1] = 0x70;
			ProgramROM[2] = 0xA8;
			ProgramROM[3] = 0x80;
			ProgramROM[4] = 0xA9;
			ProgramROM[5] = 0x90;
			ProgramROM[6] = 0xB1;
			ProgramROM[7] = 0x11;
			break;
		case 36:
			ProgramROM[0] = 0xB2;
			ProgramROM[1] = 0x22;
			ProgramROM[2] = 0xB3;
			ProgramROM[3] = 0x33;
			ProgramROM[4] = 0xB4;
			ProgramROM[5] = 0x44;
			ProgramROM[6] = 0xB5;
			ProgramROM[7] = 0x55;
			break;
		case 37:
			ProgramROM[0] = 0xB6;
			ProgramROM[1] = 0x66;
			ProgramROM[2] = 0xB7;
			ProgramROM[3] = 0x77;
			ProgramROM[4] = 0xB8;
			ProgramROM[5] = 0x88;
			ProgramROM[6] = 0xB9;
			ProgramROM[7] = 0x99;
			break;
		case 38:
			ProgramROM[0] = 0x21;
			ProgramROM[1] = 0x02;
			ProgramROM[2] = 0x22;
			ProgramROM[3] = 0x04;
			ProgramROM[4] = 0x23;
			ProgramROM[5] = 0x06;
			ProgramROM[6] = 0x24;
			ProgramROM[7] = 0x08;
			break;
		case 39:
			ProgramROM[0] = 0x25;
			ProgramROM[1] = 0x10;
			ProgramROM[2] = 0x26;
			ProgramROM[3] = 0x12;
			ProgramROM[4] = 0x27;
			ProgramROM[5] = 0x14;
			ProgramROM[6] = 0x28;
			ProgramROM[7] = 0x16;
			break;
		case 40:
			ProgramROM[0] = 0x29;
			ProgramROM[1] = 0x18;
			ProgramROM[2] = 0x2A;
			ProgramROM[3] = 0x08;
			ProgramROM[4] = 0xC8;
			ProgramROM[5] = 0x76;
			ProgramROM[6] = 0x03;
			ProgramROM[7] = 0x74;
			break;
		case 41:
			ProgramROM[0] = 0x61;
			ProgramROM[1] = 0x50;
			ProgramROM[2] = 0x2D;
			ProgramROM[3] = 0xD5;
			ProgramROM[4] = 0x4B;
			ProgramROM[5] = 0x06;
			ProgramROM[6] = 0x98;
			ProgramROM[7] = 0x34;
			break;
		case 42:
			ProgramROM[0] = 0x01;
			ProgramROM[1] = 0x03;
			ProgramROM[2] = 0x05;
			ProgramROM[3] = 0x07;
			ProgramROM[4] = 0x09;
			ProgramROM[5] = 0x11;
			ProgramROM[6] = 0x13;
			ProgramROM[7] = 0x15;
			break;
		case 43:
			ProgramROM[0] = 0x17;
			ProgramROM[1] = 0x19;
			ProgramROM[2] = 0x21;
			ProgramROM[3] = 0x23;
			ProgramROM[4] = 0x25;
			ProgramROM[5] = 0x27;
			ProgramROM[6] = 0x29;
			ProgramROM[7] = 0x31;
			break;
		case 44:
			ProgramROM[0] = 0x33;
			ProgramROM[1] = 0x35;
			ProgramROM[2] = 0x37;
			ProgramROM[3] = 0x39;
			ProgramROM[4] = 0x41;
			ProgramROM[5] = 0x43;
			ProgramROM[6] = 0x45;
			ProgramROM[7] = 0x47;
			break;
		case 45:
			ProgramROM[0] = 0x51;
			ProgramROM[1] = 0x53;
			ProgramROM[2] = 0x55;
			ProgramROM[3] = 0x57;
			ProgramROM[4] = 0x59;
			ProgramROM[5] = 0x61;
			ProgramROM[6] = 0x63;
			ProgramROM[7] = 0x65;
			break;
		case 46:
			ProgramROM[0] = 0x67;
			ProgramROM[1] = 0x69;
			ProgramROM[2] = 0x71;
			ProgramROM[3] = 0x73;
			ProgramROM[4] = 0x75;
			ProgramROM[5] = 0x77;
			ProgramROM[6] = 0x79;
			ProgramROM[7] = 0x81;
			break;
		case 47:
			ProgramROM[0] = 0x83;
			ProgramROM[1] = 0x85;
			ProgramROM[2] = 0x87;
			ProgramROM[3] = 0x89;
			ProgramROM[4] = 0x91;
			ProgramROM[5] = 0x93;
			ProgramROM[6] = 0x95;
			ProgramROM[7] = 0x97;
			break;
		case 48:
			ProgramROM[0] = 0x99;
			ProgramROM[1] = 0x02;
			ProgramROM[2] = 0x03;
			ProgramROM[3] = 0x05;
			ProgramROM[4] = 0x07;
			ProgramROM[5] = 0x11;
			ProgramROM[6] = 0x13;
			ProgramROM[7] = 0x17;
			break;
		case 49:
			ProgramROM[0] = 0x19;
			ProgramROM[1] = 0x23;
			ProgramROM[2] = 0x29;
			ProgramROM[3] = 0x31;
			ProgramROM[4] = 0x37;
			ProgramROM[5] = 0x41;
			ProgramROM[6] = 0x43;
			ProgramROM[7] = 0x47;
			break;
		case 50:
			ProgramROM[0] = 0x51;
			ProgramROM[1] = 0x53;
			ProgramROM[2] = 0x57;
			ProgramROM[3] = 0x59;
			ProgramROM[4] = 0x61;
			ProgramROM[5] = 0x67;
			ProgramROM[6] = 0x71;
			ProgramROM[7] = 0x73;
			break;
		case 51:
			ProgramROM[0] = 0x77;
			ProgramROM[1] = 0x79;
			ProgramROM[2] = 0x83;
			ProgramROM[3] = 0x87;
			ProgramROM[4] = 0x89;
			ProgramROM[5] = 0x91;
			ProgramROM[6] = 0x97;
			ProgramROM[7] = 0x00;
			break;
		case 52:
			ProgramROM[0] = 0xA1;
			ProgramROM[1] = 0x00;
			ProgramROM[2] = 0xB2;
			ProgramROM[3] = 0x00;
			ProgramROM[4] = 0xC4;
			ProgramROM[5] = 0x00;
			ProgramROM[6] = 0xD8;
			ProgramROM[7] = 0x00;
			break;
		case 53:
			ProgramROM[0] = 0x1A;
			ProgramROM[1] = 0x00;
			ProgramROM[2] = 0x2B;
			ProgramROM[3] = 0x00;
			ProgramROM[4] = 0x4C;
			ProgramROM[5] = 0x00;
			ProgramROM[6] = 0x8D;
			ProgramROM[7] = 0x00;
			break;
		case 54:
			ProgramROM[0] = 0xA1;
			ProgramROM[1] = 0xFF;
			ProgramROM[2] = 0xB2;
			ProgramROM[3] = 0xFF;
			ProgramROM[4] = 0xC4;
			ProgramROM[5] = 0xFF;
			ProgramROM[6] = 0xD8;
			ProgramROM[7] = 0xFF;
			break;
		case 55:
			ProgramROM[0] = 0x1A;
			ProgramROM[1] = 0xFF;
			ProgramROM[2] = 0x2B;
			ProgramROM[3] = 0xFF;
			ProgramROM[4] = 0x4C;
			ProgramROM[5] = 0xFF;
			ProgramROM[6] = 0x8D;
			ProgramROM[7] = 0xFF;
			break;
		case 56:
			ProgramROM[0] = 0x19;
			ProgramROM[1] = 0x28;
			ProgramROM[2] = 0x37;
			ProgramROM[3] = 0x45;
			ProgramROM[4] = 0x55;
			ProgramROM[5] = 0x64;
			ProgramROM[6] = 0x73;
			ProgramROM[7] = 0x82;
			break;
		case 57:
			ProgramROM[0] = 0xA1;
			ProgramROM[1] = 0xB0;
			ProgramROM[2] = 0xC2;
			ProgramROM[3] = 0xD0;
			ProgramROM[4] = 0xE4;
			ProgramROM[5] = 0xF0;
			ProgramROM[6] = 0x88;
			ProgramROM[7] = 0x10;
			break;
		case 58:
			ProgramROM[0] = 0x1A;
			ProgramROM[1] = 0x0B;
			ProgramROM[2] = 0x2C;
			ProgramROM[3] = 0x0D;
			ProgramROM[4] = 0x4E;
			ProgramROM[5] = 0x0F;
			ProgramROM[6] = 0x88;
			ProgramROM[7] = 0x01;
			break;
		case 59:
			ProgramROM[0] = 0x11;
			ProgramROM[1] = 0x01;
			ProgramROM[2] = 0x22;
			ProgramROM[3] = 0x02;
			ProgramROM[4] = 0x44;
			ProgramROM[5] = 0x16;
			ProgramROM[6] = 0x88;
			ProgramROM[7] = 0x64;
			break;
		case 60:
			ProgramROM[0] = 0x76;
			ProgramROM[1] = 0x54;
			ProgramROM[2] = 0x32;
			ProgramROM[3] = 0x10;
			ProgramROM[4] = 0x01;
			ProgramROM[5] = 0x02;
			ProgramROM[6] = 0x04;
			ProgramROM[7] = 0x06;
			break;
		case 61:
			ProgramROM[0] = 0x08;
			ProgramROM[1] = 0x10;
			ProgramROM[2] = 0x12;
			ProgramROM[3] = 0x14;
			ProgramROM[4] = 0x16;
			ProgramROM[5] = 0x18;
			ProgramROM[6] = 0x20;
			ProgramROM[7] = 0x22;
			break;
		case 62:
			ProgramROM[0] = 0x24;
			ProgramROM[1] = 0x26;
			ProgramROM[2] = 0x28;
			ProgramROM[3] = 0x30;
			ProgramROM[4] = 0x32;
			ProgramROM[5] = 0x34;
			ProgramROM[6] = 0x36;
			ProgramROM[7] = 0x38;
			break;
		case 63:
			ProgramROM[0] = 0x40;
			ProgramROM[1] = 0x42;
			ProgramROM[2] = 0x44;
			ProgramROM[3] = 0x46;
			ProgramROM[4] = 0x48;
			ProgramROM[5] = 0x50;
			ProgramROM[6] = 0x52;
			ProgramROM[7] = 0x54;
			break;
		case 64:
			ProgramROM[0] = 0x56;
			ProgramROM[1] = 0x58;
			ProgramROM[2] = 0x60;
			ProgramROM[3] = 0x62;
			ProgramROM[4] = 0x64;
			ProgramROM[5] = 0x68;
			ProgramROM[6] = 0x70;
			ProgramROM[7] = 0x72;
			break;
		case 65:
			ProgramROM[0] = 0x74;
			ProgramROM[1] = 0x76;
			ProgramROM[2] = 0x78;
			ProgramROM[3] = 0x80;
			ProgramROM[4] = 0x82;
			ProgramROM[5] = 0x84;
			ProgramROM[6] = 0x86;
			ProgramROM[7] = 0x88;
			break;
		case 66:
			ProgramROM[0] = 0x90;
			ProgramROM[1] = 0x92;
			ProgramROM[2] = 0x94;
			ProgramROM[3] = 0x96;
			ProgramROM[4] = 0x98;
			ProgramROM[5] = 0xA0;
			ProgramROM[6] = 0x82;
			ProgramROM[7] = 0x83;
			break;
		case 67:
			ProgramROM[0] = 0xC8;
			ProgramROM[1] = 0x00;
			ProgramROM[2] = 0xC4;
			ProgramROM[3] = 0x00;
			ProgramROM[4] = 0xC2;
			ProgramROM[5] = 0x00;
			ProgramROM[6] = 0xC1;
			ProgramROM[7] = 0x00;
			break;
		case 68:
			ProgramROM[0] = 0xC8;
			ProgramROM[1] = 0xFF;
			ProgramROM[2] = 0xC2;
			ProgramROM[3] = 0xFF;
			ProgramROM[4] = 0xC4;
			ProgramROM[5] = 0xFF;
			ProgramROM[6] = 0xC8;
			ProgramROM[7] = 0xFF;
			break;
		case 69:
			ProgramROM[0] = 0x1C;
			ProgramROM[1] = 0x00;
			ProgramROM[2] = 0x2C;
			ProgramROM[3] = 0x00;
			ProgramROM[4] = 0x4C;
			ProgramROM[5] = 0x00;
			ProgramROM[6] = 0x8C;
			ProgramROM[7] = 0x00;
			break;
		case 70:
			ProgramROM[0] = 0x11;
			ProgramROM[1] = 0x0C;
			ProgramROM[2] = 0x22;
			ProgramROM[3] = 0xC0;
			ProgramROM[4] = 0x44;
			ProgramROM[5] = 0x0C;
			ProgramROM[6] = 0x88;
			ProgramROM[7] = 0xC0;
			break;
		case 71:
			ProgramROM[0] = 0xA1;
			ProgramROM[1] = 0x00;
			ProgramROM[2] = 0xA2;
			ProgramROM[3] = 0x00;
			ProgramROM[4] = 0xA4;
			ProgramROM[5] = 0x00;
			ProgramROM[6] = 0xA8;
			ProgramROM[7] = 0x00;
			break;
		case 72:
			ProgramROM[0] = 0x1A;
			ProgramROM[1] = 0xFF;
			ProgramROM[2] = 0x2A;
			ProgramROM[3] = 0xFF;
			ProgramROM[4] = 0x4A;
			ProgramROM[5] = 0xFF;
			ProgramROM[6] = 0x8A;
			ProgramROM[7] = 0xFF;
			break;
		case 73:
			ProgramROM[0] = 0x11;
			ProgramROM[1] = 0xA0;
			ProgramROM[2] = 0x22;
			ProgramROM[3] = 0x0A;
			ProgramROM[4] = 0x44;
			ProgramROM[5] = 0xA0;
			ProgramROM[6] = 0x88;
			ProgramROM[7] = 0x0A;
			break;
		case 74:
			ProgramROM[0] = 0xB1;
			ProgramROM[1] = 0x00;
			ProgramROM[2] = 0xB2;
			ProgramROM[3] = 0x00;
			ProgramROM[4] = 0xB4;
			ProgramROM[5] = 0x00;
			ProgramROM[6] = 0xB8;
			ProgramROM[7] = 0x00;
			break;
		case 75:
			ProgramROM[0] = 0xB1;
			ProgramROM[1] = 0xFF;
			ProgramROM[2] = 0xB2;
			ProgramROM[3] = 0xFF;
			ProgramROM[4] = 0xB4;
			ProgramROM[5] = 0xFF;
			ProgramROM[6] = 0xB8;
			ProgramROM[7] = 0xFF;
			break;
		case 76:
			ProgramROM[0] = 0x11;
			ProgramROM[1] = 0xB0;
			ProgramROM[2] = 0x22;
			ProgramROM[3] = 0x0B;
			ProgramROM[4] = 0x44;
			ProgramROM[5] = 0xB0;
			ProgramROM[6] = 0x88;
			ProgramROM[7] = 0x0B;
			break;
		case 77:
			ProgramROM[0] = 0xD1;
			ProgramROM[1] = 0x00;
			ProgramROM[2] = 0xD2;
			ProgramROM[3] = 0x00;
			ProgramROM[4] = 0xD4;
			ProgramROM[5] = 0x00;
			ProgramROM[6] = 0xD8;
			ProgramROM[7] = 0x00;
			break;
		case 78:
			ProgramROM[0] = 0xD1;
			ProgramROM[1] = 0xFF;
			ProgramROM[2] = 0xD2;
			ProgramROM[3] = 0xFF;
			ProgramROM[4] = 0xD4;
			ProgramROM[5] = 0xFF;
			ProgramROM[6] = 0xD8;
			ProgramROM[7] = 0xFF;
			break;
		case 79:
			ProgramROM[0] = 0x11;
			ProgramROM[1] = 0xD0;
			ProgramROM[2] = 0x22;
			ProgramROM[3] = 0x0D;
			ProgramROM[4] = 0x44;
			ProgramROM[5] = 0xD0;
			ProgramROM[6] = 0x88;
			ProgramROM[7] = 0x0D;
			break;
		case 80:
			ProgramROM[0] = 0xE1;
			ProgramROM[1] = 0x00;
			ProgramROM[2] = 0xE2;
			ProgramROM[3] = 0x00;
			ProgramROM[4] = 0xE4;
			ProgramROM[5] = 0x00;
			ProgramROM[6] = 0xE8;
			ProgramROM[7] = 0x00;
			break;
		case 81:
			ProgramROM[0] = 0xE1;
			ProgramROM[1] = 0xFF;
			ProgramROM[2] = 0xE2;
			ProgramROM[3] = 0xFF;
			ProgramROM[4] = 0xE4;
			ProgramROM[5] = 0xFF;
			ProgramROM[6] = 0xE8;
			ProgramROM[7] = 0xFF;
			break;
		case 82:
			ProgramROM[0] = 0x11;
			ProgramROM[1] = 0xE0;
			ProgramROM[2] = 0x22;
			ProgramROM[3] = 0x0E;
			ProgramROM[4] = 0x44;
			ProgramROM[5] = 0xE0;
			ProgramROM[6] = 0x88;
			ProgramROM[7] = 0x0E;
			break;
		case 83:
			ProgramROM[0] = 0xF1;
			ProgramROM[1] = 0x00;
			ProgramROM[2] = 0xF2;
			ProgramROM[3] = 0x00;
			ProgramROM[4] = 0xF4;
			ProgramROM[5] = 0x00;
			ProgramROM[6] = 0xF8;
			ProgramROM[7] = 0x00;
			break;
		case 84:
			ProgramROM[0] = 0x1F;
			ProgramROM[1] = 0x00;
			ProgramROM[2] = 0x2F;
			ProgramROM[3] = 0x00;
			ProgramROM[4] = 0x4F;
			ProgramROM[5] = 0x00;
			ProgramROM[6] = 0x8F;
			ProgramROM[7] = 0x00;
			break;
		case 85:
			ProgramROM[0] = 0xFF;
			ProgramROM[1] = 0x00;
			ProgramROM[2] = 0xFF;
			ProgramROM[3] = 0x00;
			ProgramROM[4] = 0xFF;
			ProgramROM[5] = 0x00;
			ProgramROM[6] = 0xFF;
			ProgramROM[7] = 0x00;
			break;
		case 86:
			ProgramROM[0] = 0x11;
			ProgramROM[1] = 0x00;
			ProgramROM[2] = 0x11;
			ProgramROM[3] = 0x00;
			ProgramROM[4] = 0x11;
			ProgramROM[5] = 0x00;
			ProgramROM[6] = 0x11;
			ProgramROM[7] = 0x00;
			break;
		case 87:
			ProgramROM[0] = 0x22;
			ProgramROM[1] = 0x00;
			ProgramROM[2] = 0x22;
			ProgramROM[3] = 0x00;
			ProgramROM[4] = 0x22;
			ProgramROM[5] = 0x00;
			ProgramROM[6] = 0x22;
			ProgramROM[7] = 0x00;
			break;
		case 88:
			ProgramROM[0] = 0x44;
			ProgramROM[1] = 0x00;
			ProgramROM[2] = 0x44;
			ProgramROM[3] = 0x00;
			ProgramROM[4] = 0x44;
			ProgramROM[5] = 0x00;
			ProgramROM[6] = 0x44;
			ProgramROM[7] = 0x00;
			break;
		case 89:
			ProgramROM[0] = 0x88;
			ProgramROM[1] = 0x00;
			ProgramROM[2] = 0x88;
			ProgramROM[3] = 0x00;
			ProgramROM[4] = 0x88;
			ProgramROM[5] = 0x00;
			ProgramROM[6] = 0x88;
			ProgramROM[7] = 0x00;
			break;
		case 90:
			ProgramROM[0] = 0x10;
			ProgramROM[1] = 0x24;
			ProgramROM[2] = 0x05;
			ProgramROM[3] = 0x12;
			ProgramROM[4] = 0x02;
			ProgramROM[5] = 0x56;
			ProgramROM[6] = 0x01;
			ProgramROM[7] = 0x28;
			break;
		case 91:
			ProgramROM[0] = 0x00;
			ProgramROM[1] = 0x64;
			ProgramROM[2] = 0x00;
			ProgramROM[3] = 0x32;
			ProgramROM[4] = 0x00;
			ProgramROM[5] = 0x16;
			ProgramROM[6] = 0x00;
			ProgramROM[7] = 0x08;
			break;
		case 92:
			ProgramROM[0] = 0x00;
			ProgramROM[1] = 0x04;
			ProgramROM[2] = 0x00;
			ProgramROM[3] = 0x02;
			ProgramROM[4] = 0x00;
			ProgramROM[5] = 0xFF;
			ProgramROM[6] = 0x88;
			ProgramROM[7] = 0x00;
			break;
		case 93:
			ProgramROM[0] = 0x93;
			ProgramROM[1] = 0x39;
			ProgramROM[2] = 0x84;
			ProgramROM[3] = 0x48;
			ProgramROM[4] = 0x75;
			ProgramROM[5] = 0x57;
			ProgramROM[6] = 0x65;
			ProgramROM[7] = 0x56;
			break;
		case 94:
			ProgramROM[0] = 0x94;
			ProgramROM[1] = 0x49;
			ProgramROM[2] = 0x85;
			ProgramROM[3] = 0x58;
			ProgramROM[4] = 0x76;
			ProgramROM[5] = 0x67;
			ProgramROM[6] = 0x68;
			ProgramROM[7] = 0x86;
			break;
		case 95:
			ProgramROM[0] = 0x31;
			ProgramROM[1] = 0x13;
			ProgramROM[2] = 0x25;
			ProgramROM[3] = 0x52;
			ProgramROM[4] = 0xC8;
			ProgramROM[5] = 0x8C;
			ProgramROM[6] = 0x76;
			ProgramROM[7] = 0x67;
			break;
		case 96:
			ProgramROM[0] = 0xD8;
			ProgramROM[1] = 0x8D;
			ProgramROM[2] = 0xB7;
			ProgramROM[3] = 0x7B;
			ProgramROM[4] = 0x6A;
			ProgramROM[5] = 0xA6;
			ProgramROM[6] = 0x5F;
			ProgramROM[7] = 0xF5;
			break;
		case 97:
			ProgramROM[0] = 0xE4;
			ProgramROM[1] = 0x4E;
			ProgramROM[2] = 0xA8;
			ProgramROM[3] = 0x9C;
			ProgramROM[4] = 0x67;
			ProgramROM[5] = 0x77;
			ProgramROM[6] = 0x96;
			ProgramROM[7] = 0x53;
			break;
		case 98:
			ProgramROM[0] = 0x98;
			ProgramROM[1] = 0x89;
			ProgramROM[2] = 0x88;
			ProgramROM[3] = 0x86;
			ProgramROM[4] = 0x40;
			ProgramROM[5] = 0x04;
			ProgramROM[6] = 0x69;
			ProgramROM[7] = 0x96;
			break;
		case 99:
			ProgramROM[0] = 0x70;
			ProgramROM[1] = 0x06;
			ProgramROM[2] = 0x50;
			ProgramROM[3] = 0x04;
			ProgramROM[4] = 0x30;
			ProgramROM[5] = 0x02;
			ProgramROM[6] = 0x10;
			ProgramROM[7] = 0x08;
			break;
		case 0:
			ProgramROM[0] = 0x00;
			ProgramROM[1] = 0x00;
			ProgramROM[2] = 0x00;
			ProgramROM[3] = 0x00;
			ProgramROM[4] = 0x00;
			ProgramROM[5] = 0x00;
			ProgramROM[6] = 0x00;
			ProgramROM[7] = 0x00;
			break;
    }	
}