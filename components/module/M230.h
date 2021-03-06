//-------------------------------------------------------------------
// Filename: M230.h
// Description: hal M230 module library header file
//-------------------------------------------------------------------
//-------------------------------------------------------------------
// GLOBAL FUNCTIONS
//-------------------------------------------------------------------
void M230_Init(void);
void M230_WriteEEPROM(uint8 addr, uint8 ch);
uint8 M230_ReadEEPROM(uint8 addr);
