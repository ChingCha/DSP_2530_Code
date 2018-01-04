//-------------------------------------------------------------------
// Filename: hal_lcd.c  NT7605H
// Description: Functions for controlling the LCD
//-------------------------------------------------------------------
//-------------------------------------------------------------------
// INCLUDES
//-------------------------------------------------------------------
#include "hal_defs.h"
#include "hal_cc8051.h"
#include "hal_mcu.h"
#include "hal_board.h"
#include "hal_lcd.h"
#include "hal_button.h"
#include "util.h"
#include <string.h>

//-------------------------------------------------------------------
// CONSTANTS AND DEFINES
//-------------------------------------------------------------------
// LCD instruction set definitions

// Function set
#define DOT_5X10_OFF                    0x00
#define DOT_5X10_ON                     0x04
#define DUAL_LINE_OFF                   0x00
#define DUAL_LINE_ON                    0x08
#define BUS_8BIT_OFF                    0x00
#define BUS_8BIT_ON                     0x10
#define FUNCTION_SET(options)           lcdControl(0x20 | (options))

// Display clear
#define DISPLAY_CLEAR()                 lcdControl(0x01)

// Set display control
#define DISPLAY_CTRL_ON                 0x04
#define DISPLAY_CTRL_OFF                0x00
#define DISPLAY_CTRL_BLINK_ON           0x01
#define DISPLAY_CTRL_BLINK_OFF          0x00
#define DISPLAY_CTRL_CURSOR_ON          0x02
#define DISPLAY_CTRL_CURSOR_OFF         0x00
#define SET_DISPLAY_CTRL(options)       lcdControl(0x08 | (options))

// Set enter mode
#define INCREMENT_ON                    0x02
#define INCREMENT_OFF                   0x00
#define DISPLAY_SHIFT_ON                0x01
#define DISPLAY_SHIFT_OFF               0x00
#define SET_ENTER_MODE(options)         lcdControl(0x04 | (options))

// Set display control
#define SHITF_DISPLAY_ON                0x04
#define SHITF_DISPLAY_OFF               0x00
#define SHITF_RIGHT_ON                  0x02
#define SHITF_RIGHT_OFF                 0x00
#define SET_CURSOR_SHIFT(options)       lcdControl(0x10 | (options))

// Set Display Start Line
#define LINE1                           0x00
#define LINE2                           0x40
#define SET_DISPLAY_LINE(line)          lcdControl(0x80 | (line))

// Set DD/CGRAM address
#define SET_DDRAM_ADDR(charIndex)       lcdControl(0x80 | (charIndex))
#define SET_GCRAM_CHAR(specIndex)       lcdControl(0x40 | (specIndex))

// LCD lines
#define LCD_LINE_COUNT                  2
#define LCD_LINE_LENGTH                 16

//-------------------------------------------------------------------
// LOCAL VARIABLES
//-------------------------------------------------------------------
static char pLcdLineBuffer[LCD_LINE_LENGTH];

//-------------------------------------------------------------------
// LOCAL FUNCTIONS
//-------------------------------------------------------------------
static void lcdControl(uint8 command);
static void lcdWrite(uint8 ch);
static void lcdWriteMany(char *pData, uint8 count);
static void lcdWriteLine(uint8 line, char *pText);
//-------------------------------------------------------------------
// @fn          lcdControl
// @brief(Ê¶ÇË?) Send command to display(?ÅÂá∫?á‰ª§‰∏¶È°ØÁ§?
// @param       uint8 command
// @return      none
//-------------------------------------------------------------------
static void lcdControl(uint8 command)
{
    MCU_IO_DIR_OUTPUT(HAL_BOARD_IO_LCD_RS_PORT, HAL_BOARD_IO_LCD_RS_PIN);
    HAL_LCD_RS_CLR();
    HAL_LCD_DATA(command);
    HAL_LCD_EN_SET();
    halMcuWaitUs(2);
    HAL_LCD_EN_CLR();
    halMcuWaitUs(80);
    HAL_LCD_DATA(pLedData);
}

//-------------------------------------------------------------------
// @fn          lcdWrite
// @brief       Write character to display
// @param       uint8 ch - character to display
// @return      none
//-------------------------------------------------------------------
static void lcdWrite(uint8 ch)
{
    MCU_IO_DIR_OUTPUT(HAL_BOARD_IO_LCD_RS_PORT, HAL_BOARD_IO_LCD_RS_PIN);
    HAL_LCD_RS_SET();
    HAL_LCD_DATA(ch);
    HAL_LCD_EN_SET();
    halMcuWaitUs(2);
    HAL_LCD_EN_CLR();
    halMcuWaitUs(80);
    HAL_LCD_DATA(pLedData);
}

//-------------------------------------------------------------------
// @fn          lcdWriteMany
// @brief       Write text to display
// @param       char *pData - text buffer
//              uint16 count - number of bytes
// @return      none
//-------------------------------------------------------------------
static void lcdWriteMany(char *pData, uint8 count)
{
    while (count--)
    {
        lcdWrite(*(pData++));
    }
}

//-------------------------------------------------------------------
// @fn          lcdWriteLine
// @brief       Write line on display
// @param       uint8 line - display line
//              char *pText - text buffer to write
// @return      none
//-------------------------------------------------------------------
static void lcdWriteLine(uint8 line, char *pText)
{
    if (line == HAL_LCD_LINE_2)
    {
        SET_DISPLAY_LINE(LINE2);
    }
    else
    {
        SET_DISPLAY_LINE(LINE1);
    }
    lcdWriteMany(pText, LCD_LINE_LENGTH);
}

//-------------------------------------------------------------------
// GLOBAL FUNCTIONS
//-------------------------------------------------------------------
// @fn          halLcdInit
// @brief       Initalise LCD
// @param       none
// @return      none
//-------------------------------------------------------------------
void halLcdInit(void)
{
    // Perform the initialization sequence
    MCU_IO_DIR_OUTPUT(HAL_BOARD_IO_LCD_RS_PORT, HAL_BOARD_IO_LCD_RS_PIN);
    HAL_LCD_EN_CLR();
    halMcuWaitMs(30);

    FUNCTION_SET(BUS_8BIT_ON);
    halMcuWaitMs(2);
    FUNCTION_SET(BUS_8BIT_ON);
    halMcuWaitMs(2);
    FUNCTION_SET(BUS_8BIT_ON);
    halMcuWaitMs(2);
    FUNCTION_SET(BUS_8BIT_ON | DUAL_LINE_ON);
    halMcuWaitMs(2);
    FUNCTION_SET(BUS_8BIT_ON | DUAL_LINE_ON);
    halMcuWaitMs(2);
    SET_CURSOR_SHIFT(SHITF_DISPLAY_OFF);
    SET_ENTER_MODE(INCREMENT_ON);
    DISPLAY_CLEAR();
    halMcuWaitMs(2);
    // Clear the display
    halLcdClear();
    SET_DISPLAY_CTRL(DISPLAY_CTRL_ON | DISPLAY_CTRL_BLINK_OFF | DISPLAY_CTRL_CURSOR_OFF);
}
//-------------------------------------------------------------------
// @fn          halLcdClearLine
// @brief       Clear one lines on display
// @param       uint8 line - display line
// @return      none
//-------------------------------------------------------------------
void halLcdClearLine(uint8 line)
{
    uint8 n;
    if (line == HAL_LCD_LINE_2)
    {
        SET_DISPLAY_LINE(LINE2);
    }
    else
    {
        SET_DISPLAY_LINE(LINE1);
    }
    for (n = 0; n < LCD_LINE_LENGTH; n++)
    {
        lcdWrite(' ');
    }
}

//-------------------------------------------------------------------
// @fn          halLcdClear
// @brief       Clear all lines on display
// @param       none
// @return      none
//-------------------------------------------------------------------
void halLcdClear(void)
{
    uint8 n;
    SET_DISPLAY_LINE(LINE1);
    for (n = 0; n < LCD_LINE_LENGTH; n++)
    {
        lcdWrite(' ');
    }
    SET_DISPLAY_LINE(LINE2);
    for (n = 0; n < LCD_LINE_LENGTH; n++)
    {
        lcdWrite(' ');
    }
}

//-------------------------------------------------------------------
// @fn          halLcdGetLineLength
// @brief       Get max number of characters on each line
// @param       nono
// @return      uint8 - number of characters on a line
//-------------------------------------------------------------------
uint8 halLcdGetLineLength(void)
{
    return LCD_LINE_LENGTH;
}

//-------------------------------------------------------------------
// @fn          halLcdGetNumLines
// @brief       Get number of lines on display
// @param       nono
// @return      uint8 - number of characters on a line
//-------------------------------------------------------------------
uint8 halLcdGetNumLines(void)
{
    return LCD_LINE_COUNT;
}

//-------------------------------------------------------------------
// @fn          halLcdWriteChar
// @brief       Write single character
// @param       uint8 line - display line
//              uint8 col - column
//              char text - character to display
// @return      none
//-------------------------------------------------------------------
void halLcdWriteChar(uint8 line, uint8 col, char text)
{
    if (line == HAL_LCD_LINE_2)
    {
        SET_DISPLAY_LINE(LINE2 + col);
    }
    else
    {
        SET_DISPLAY_LINE(LINE1 + col);
    }
    lcdWrite(text);
}

//-------------------------------------------------------------------
// @fn          halLcdWriteString
// @brief       Write string on display
// @param       uint8 line - display line
//              uint8 col - column
//              char *pText - text buffer to write
// @return      none
//-------------------------------------------------------------------
void halLcdWriteString(uint8 line, uint8 col, char *pText)
{
    if (line == HAL_LCD_LINE_2)
    {
        SET_DISPLAY_LINE(LINE2+col);
    }
    else
    {
        SET_DISPLAY_LINE(LINE1+col);
    }
    lcdWriteMany(pText, strlen(pText));
}

//-------------------------------------------------------------------
// @fn          halLcdWriteLine
// @brief       Write line on display
// @param       uint8 line - display line
//              char *pLine2 - pointer to text buffer to write
// @return      none
//-------------------------------------------------------------------
void halLcdWriteLine(uint8 line, char *pLine)
{
    uint8 n;
    if (pLine)
    {
        for (n = 0; n < LCD_LINE_LENGTH; n++)
        {
            if (*pLine)
            {
                pLcdLineBuffer[n] = *(pLine++);
            }
            else
            {
                pLcdLineBuffer[n] = ' ';
            }
        }
        lcdWriteLine(line, pLcdLineBuffer);
    }
}

//-------------------------------------------------------------------
// @fn          halLcdWriteLines
// @brief       Write lines on display
// @param       char *pLine1 - pointer to text buffer for line 1
//              char *pLine2 - pointer to text buffer for line 2
// @return      none
//-------------------------------------------------------------------
void halLcdWriteLines(char *pLine1, char *pLine2)
{
    if (pLine1)
    {
        halLcdWriteLine(HAL_LCD_LINE_1, pLine1);
    }
    if (pLine2)
    {
        halLcdWriteLine(HAL_LCD_LINE_2, pLine2);
    }
}

//-------------------------------------------------------------------
// @fn          halLcdDisplayValue
// @brief       Display value on display with optional text on right and left side
// @param       uint8 line
//              char *pLeft
//              int32 value
//              char *pRight
// @return      none
//-------------------------------------------------------------------
void halLcdDisplayValue(uint8 line, char *pLeft, int32 value, char *pRight)
{
    uint8 n;
    char *pValue = convInt32ToText(value);
    for (n = 0; n < LCD_LINE_LENGTH; n++)
    {
        if (pLeft &&  *pLeft)
        {
            pLcdLineBuffer[n] = *(pLeft++);
        }
        else if (*pValue)
        {
            pLcdLineBuffer[n] = *(pValue++);
        }
        else if (pRight &&  *pRight)
        {
            pLcdLineBuffer[n] = *(pRight++);
        }
        else
        {
            pLcdLineBuffer[n] = ' ';
        }
    }
    lcdWriteLine(line, pLcdLineBuffer);
}

//-------------------------------------------------------------------
// @fn          halLcdDisplayCounters
// @brief       Display counter values with text on display
// @param       uint8 line - display line
//              int32 lValue - left value
//              char lChar - left text
//              int32 rValue - right value
//              char rChar - right text
// @return      none
//-------------------------------------------------------------------
void halLcdDisplayCounters(uint8 line, int32 lValue, char lChar, int32 rValue, char rChar)
{
    uint8 n;
    char *pCounter;
	
    // Left part
    pLcdLineBuffer[0] = lChar;
    pLcdLineBuffer[1] = '=';
    pCounter = convInt32ToText(lValue);
    for (n = 2; n < 8; n++)
    {
        if (*pCounter)
        {
            pLcdLineBuffer[n] = *(pCounter++);
        }
        else
        {
            pLcdLineBuffer[n] = ' ';
        }
    }
	// Right Part
    pLcdLineBuffer[8] = rChar;
    pLcdLineBuffer[9] = '=';
    pCounter = convInt32ToText(rValue);
    for (n = 10; n < 16; n++)
    {
        if (*pCounter)
        {
            pLcdLineBuffer[n] = *(pCounter++);
        }
        else
        {
            pLcdLineBuffer[n] = ' ';
        }
    }
    lcdWriteLine(line, pLcdLineBuffer);
}

static const char hex[] = 
{
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'
};
//-------------------------------------------------------------------
// @fn          halLcdDisplayUint16
// @brief       Write a 16 bit value on the specified line on the LCD
// @param       uint16 value - value to display
//              uint8 radix - must be HAL_LCD_RADIX_DEC
//              uint8 line - line on display
// @return      none
//-------------------------------------------------------------------
void halLcdDisplayUint16(uint8 line, uint8 col, uint8 radix, uint16 value)
{
    if (radix == HAL_LCD_RADIX_DEC)
    {
        uint8 n = 0;
        char *pValue = convInt32ToText((uint32)value);
        while (*pValue)
        {
            halLcdWriteChar(line, col + n++, *(pValue++));
        }
        while (n < 5)
        {
            halLcdWriteChar(line, col + n++, ' ');
        }
    }
    else if (radix == HAL_LCD_RADIX_HEX)
    {
        halLcdWriteChar(line, col, hex[(value &0xF000) >> 12]);
        halLcdWriteChar(line, col + 1, hex[(value &0x0F00) >> 8]);
        halLcdWriteChar(line, col + 2, hex[(value &0x00F0) >> 4]);
        halLcdWriteChar(line, col + 3, hex[(value &0x000F)]);
    }
}

//-------------------------------------------------------------------
// @fn          halLcdDisplayUint8
// @brief       Write a 8 bit value on the specified line on the LCD
// @param       uint8 value - value to display
//              uint8 radix - must be HAL_LCD_RADIX_DEC
//              uint8 line - line on display
// @return      none
//-------------------------------------------------------------------
void halLcdDisplayUint8(uint8 line, uint8 col, uint8 radix, uint8 value)
{
    if (radix == HAL_LCD_RADIX_DEC)
    {
        uint8 n = 0;
        char *pValue = convInt32ToText((uint32)value);
        while (*pValue)
        {
            halLcdWriteChar(line, col + n++, *(pValue++));
        }
        while (n < 3)
        {
            halLcdWriteChar(line, col + n++, ' ');
        }
    }
    else if (radix == HAL_LCD_RADIX_HEX)
    {
        halLcdWriteChar(line, col, hex[(value &0xF0) >> 4]);
        halLcdWriteChar(line, col + 1, hex[(value &0x0F)]);
    }
}
//-------------------------------------------------------------------
// @fn          halLcdDisplayItem
// @brief       
// @param       Display Value
//              
//              
// @return
// @date		2017/04/26     
// @creater		TOM 
//-------------------------------------------------------------------
void halLcdDisplayItem(uint8 line, int32 lValue, char lChar, int32 rValue, char rChar)
{
	char *pCounter; 						//´≈ßi*pCounter¨∞char∏ÍÆ∆´¨∫A(*•N™Ì¶π≈‹º∆•i¬‡¥´)
pCounter = convInt32ToText(lValue);			//pCounter∏gπL"convInt32ToText"¬‡¥´¨∞Text(2530LCD∞}¶C•u¶Y≥o≠”...)
    // LCD part(LCD∞}¶C¡`¶@¶≥16≠”¶Ï∏m)
    pLcdLineBuffer[0] = lChar;
    pLcdLineBuffer[1] = '=';
	pLcdLineBuffer[2] = *(pCounter++);		// Try to add(Fail)∞}¶C§§¡ø®D∂∂ß«°A±o¶b´e§@¶Ê¿∞pCounter add π≥§U§@¶Ê§@ºÀ
	pCounter = convInt32ToText(++lValue); 	// Try to add(Sucess)Value on pLcdLineBuffer[10]
	pLcdLineBuffer[3] = ' ';				//™≈•’
	pLcdLineBuffer[4] = ' ';
	pLcdLineBuffer[5] = ' ';
	pLcdLineBuffer[6] = ' ';
	pLcdLineBuffer[7] = ' ';
    pLcdLineBuffer[8] = rChar;
    pLcdLineBuffer[9] = '=';
	pLcdLineBuffer[10] = *(pCounter++);		//Be added
	//pLcdLineBuffer[11~15]®S•Œ®Ï°A≈„•‹§@πŒ∂¬¶‚©«™F¶Ë
    lcdWriteLine(line, pLcdLineBuffer);
}
//-------------------------------------------------------------------
// @fn          halLcdDisplayWithButton
// @brief       
// @param       
//              
//              
// @return    
// @date		2017/04/27  
// @creater		TOM   
//-------------------------------------------------------------------
void halLcdDisplayWithButton(uint8 line, int32 lValue, char lChar)
{
	char *pCounter;
	pCounter = convInt32ToText(lValue);
    pLcdLineBuffer[0] = lChar;
    pLcdLineBuffer[1] = ':';
	pLcdLineBuffer[2] = *pCounter;
	for(int i = 3;i<=15;i++){
		pLcdLineBuffer[i] = ' ';
	}
	lcdWriteLine(line, pLcdLineBuffer);
}
