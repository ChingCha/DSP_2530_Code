//-------------------------------------------------------------------
// Filename: hal_lcd.h
// Description:  hal lcd library header file
//-------------------------------------------------------------------
//-------------------------------------------------------------------
// CONSTANTS AND DEFINES
//-------------------------------------------------------------------
enum
{
    HAL_LCD_RADIX_DEC, HAL_LCD_RADIX_HEX
};

enum
{
    HAL_LCD_LINE_1 = 1, HAL_LCD_LINE_2, HAL_LCD_LINE_3, HAL_LCD_LINE_4 
};

//-------------------------------------------------------------------
// GLOBAL FUNCTIONS
//-------------------------------------------------------------------
void halLcdInit(void);
void halLcdClear(void);
void halLcdClearLine(uint8 line);
uint8 halLcdGetLineLength(void);
uint8 halLcdGetNumLines(void);
void halLcdDrawLogo(void);
void halLcdWriteChar(uint8 line, uint8 col, char text);
void halLcdWriteString(uint8 line, uint8 col, char *text);
void halLcdWriteLine(uint8 line, char *text);
void halLcdWriteLines(char *line1, char *line2, char *line3, char *line4);
void halLcdDisplayUint16(uint8 line, uint8 col, uint8 radix, uint16 value);
void halLcdDisplayUint8(uint8 line, uint8 col, uint8 radix, uint8 value);