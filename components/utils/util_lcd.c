//-------------------------------------------------------------------
// Filename: util_lcd.c
// Description: Utility library for LCD control
//-------------------------------------------------------------------
#include "hal_defs.h"
#include "hal_mcu.h"
#include "hal_board.h"
#include "hal_lcd.h"
#include "hal_rf.h"
#include "hal_keypad.h"
#include "hal_buzzer.h"
#include "util.h"
#include <string.h>

//-------------------------------------------------------------------
// GLOBAL FUNCTIONS
//-------------------------------------------------------------------
//-------------------------------------------------------------------
// @fn          utilLcdMenuSelect
// @brief       Show a horisontally scrolled text menu on the LCD. Text lines given in
//               an array is shown in line 2 of the LCD, these lines are browsable.
//               The menu is navigated by using the joystick left and right, and press
//               S1 button to select an option. The function then returns the element number
//               in the given menu list that was chosen by the user.
// @param       ppMenu - pointer to list of texts to display for menu options
//              nMenuItems - number of menu options
// @return      uint8 - index to which of the menu items that was chosen
//-------------------------------------------------------------------
uint8 utilMenuSelect(const menu_t *pMenu)
{
    uint8 index;
    uint8 updateLCD;

	if(pMenu==NULL)
		return 0;
    index = 0;
    updateLCD = TRUE; // Force update first time
    while (1)
    {
        // Keypad input: Reset = UP, Decr = LEFT, Incr = RIGHT
        uint8 key;
        halMcuWaitMs(100);
        key = halKeypadPushed();
        if (key == '#')
        //Enter
        {
            halMcuWaitMs(200);
            break;
        }
        else if (key == 'N')
        //Next
        {
            index++;
            index %= pMenu->nItems;
            updateLCD = TRUE;
        }
        else if (key == 'U')
        //Prev
        {
            if (index == 0)
            {
                index = pMenu->nItems - 1;
            }
            else
            {
                index--;
            }

            updateLCD = TRUE;
        }

        if (updateLCD)
        {
            // Display the updated value and arrows
            // Make space for left arrow at left end of display
			halLcdClearLine(HAL_LCD_LINE_2);
            halLcdWriteString(HAL_LCD_LINE_2,3,(char *)pMenu->pMenuItems[index].szDescr);
            halLcdWriteChar(HAL_LCD_LINE_2, 0, '<');
            halLcdWriteChar(HAL_LCD_LINE_2, halLcdGetLineLength() - 1, '>');
            updateLCD = FALSE;
            halMcuWaitMs(100);
        }
    }
    return pMenu->pMenuItems[index].value;
}

//-------------------------------------------------------------------
// @fn          utilPrintLogo
// @brief       Prints splash screen and logo
// @param       szAppName - String with name of application.
// @return      none
//-------------------------------------------------------------------
void utilPrintLogo(char *szAppName)
{
    char lcdLine1[20] = "** CCxxxx ( ) **";

    strncpy(&lcdLine1[5], utilChipIdToStr(halRfGetChipId()), 4);
    lcdLine1[11] = (char)halRfGetChipVer() + '0';

    halLcdWriteLine(HAL_LCD_LINE_1, lcdLine1);
    halLcdWriteLine(HAL_LCD_LINE_2, szAppName);
}
