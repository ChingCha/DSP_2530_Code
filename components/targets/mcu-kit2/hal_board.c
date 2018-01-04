//-------------------------------------------------------------------
// Filename: hal_board.c
// Description: HAL board peripherals library
//-------------------------------------------------------------------
//-------------------------------------------------------------------
// INCLUDES
//-------------------------------------------------------------------
#include "hal_defs.h"
#include "hal_cc8051.h"
#include "hal_mcu.h"
#include "hal_digio.h"
#include "hal_int.h"
#include "hal_board.h"
#include "hal_lcd.h"
#include "hal_keypad.h"
#include "hal_uart.h"
#include "hal_buzzer.h"

//-------------------------------------------------------------------
// GLOBAL VARIABLES
//-------------------------------------------------------------------
uint8 pLedData;

//-------------------------------------------------------------------
// GLOBAL FUNCTIONS
//-------------------------------------------------------------------
//-------------------------------------------------------------------
// @fn      halBoardInit
// @brief   Set up board. Initialize MCU, configure I/O pins and user interfaces
// @param   none
// @return  none
//-------------------------------------------------------------------
void halBoardInit(void)
{
    halMcuInit();

    // All Led Off
    MCU_PORT_SET_OUTPUT(HAL_BOARD_IO_LED_DATA_PORT,0x00);
    pLedData = 0x00;
    HAL_LED_PORT(pLedData);

    // Keypad
    MCU_IO_OUTPUT(HAL_BOARD_IO_KEY_SCL_PORT, HAL_BOARD_IO_KEY_SCL_PIN, 1);
    MCU_IO_OUTPUT(HAL_BOARD_IO_KEY_SDA_PORT, HAL_BOARD_IO_KEY_SDA_PIN, 1);
    MCU_IO_INPUT(HAL_BOARD_IO_KEY_SDA_PORT, HAL_BOARD_IO_KEY_SDA_PIN, MCU_IO_TRISTATE);

    // LCD
    MCU_IO_OUTPUT(HAL_BOARD_IO_LCD_CS_PORT, HAL_BOARD_IO_LCD_CS_PIN, 1);
    MCU_IO_OUTPUT(HAL_BOARD_IO_LCD_A0_PORT, HAL_BOARD_IO_LCD_A0_PIN, 1);
    MCU_IO_OUTPUT(HAL_BOARD_IO_LCD_SCL_PORT, HAL_BOARD_IO_LCD_SCL_PIN, 1);
    MCU_IO_OUTPUT(HAL_BOARD_IO_LCD_SI_PORT, HAL_BOARD_IO_LCD_SI_PIN, 1);

    // Buzzer
    MCU_IO_OUTPUT(HAL_BOARD_IO_BUZZER_PORT, HAL_BOARD_IO_BUZZER_PIN, 1);
    halBuzzerInit(2730);


    halLcdInit();

    halKeypadInit();
    halUartInit();

    halIntOn();
}

//-------------------------------------------------------------------
// @fn          halAssertHandler
// @brief       Assert Prints error message
// @param       szErrMsg - String with error message.
// @return      none
//-------------------------------------------------------------------
void halAssertHandler(char *szErrMsg)
{
    char lcdLine1[16] = "Assert Message";

    halLcdWriteLine(HAL_LCD_LINE_1, lcdLine1);
    halLcdWriteLine(HAL_LCD_LINE_2, szErrMsg);
    while (1)
    {
        HAL_LED_PORT(0x00);
        halMcuWaitMs(200);
        HAL_LED_PORT(0xFF);
        halMcuWaitMs(200);
    }
}
