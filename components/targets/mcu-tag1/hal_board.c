//-------------------------------------------------------------------
// Filename: hal_board.c
// Description: zigbee-mcu1 board peripherals library
//-------------------------------------------------------------------
//-------------------------------------------------------------------
// INCLUDES
//-------------------------------------------------------------------
#include "hal_defs.h"
#include "hal_cc8051.h"
#include "hal_mcu.h"
#include "hal_int.h"
#include "hal_board.h"
#include "hal_buzzer.h"
#include "hal_uart.h"

//-------------------------------------------------------------------
// GLOBAL FUNCTIONS
//-------------------------------------------------------------------
//-------------------------------------------------------------------
// @fn      halBoardInit
// @brief   Set up board. Initialize MCU, configure I/O pins and user interfaces
//-------------------------------------------------------------------
void halBoardInit(void)
{
    halMcuInit();

    // LEDs
    MCU_IO_OUTPUT(HAL_BOARD_IO_LED_1_PORT, HAL_BOARD_IO_LED_1_PIN, 0);
    MCU_IO_OUTPUT(HAL_BOARD_IO_LED_2_PORT, HAL_BOARD_IO_LED_2_PIN, 0);
    MCU_IO_OUTPUT(HAL_BOARD_IO_LED_3_PORT, HAL_BOARD_IO_LED_3_PIN, 0);
    MCU_IO_OUTPUT(HAL_BOARD_IO_LED_4_PORT, HAL_BOARD_IO_LED_4_PIN, 0);
    MCU_IO_OUTPUT(HAL_BOARD_IO_LED_5_PORT, HAL_BOARD_IO_LED_5_PIN, 0);
    MCU_IO_OUTPUT(HAL_BOARD_IO_LED_6_PORT, HAL_BOARD_IO_LED_6_PIN, 0);
    MCU_IO_OUTPUT(HAL_BOARD_IO_LED_7_PORT, HAL_BOARD_IO_LED_7_PIN, 0);
    MCU_IO_OUTPUT(HAL_BOARD_IO_LED_8_PORT, HAL_BOARD_IO_LED_8_PIN, 0);

    // Buttons
    MCU_IO_INPUT(HAL_BOARD_IO_BTN_1_PORT, HAL_BOARD_IO_BTN_1_PIN, MCU_IO_PULLUP);
    MCU_IO_INPUT(HAL_BOARD_IO_BTN_2_PORT, HAL_BOARD_IO_BTN_2_PIN, MCU_IO_PULLUP);

    // Buzzer
    MCU_IO_OUTPUT(HAL_BOARD_IO_BUZZER_PORT, HAL_BOARD_IO_BUZZER_PIN, 1);
    halBuzzerInit(2730);
    
    //halUartInit();
    halIntOn();
}

//-------------------------------------------------------------------
// @fn      halPAInit
// @brief   Initilization the PA 2591
//-------------------------------------------------------------------
void halPAInit(void)
{
    // Initilization PA-2591
    HAL_PA_EN();
    HAL_2591_EN();
    HAL_PA_HGM_HI();
}

//-------------------------------------------------------------------
// @fn          halAssertHandler
// @brief       Assert Prints error message
// @param       szErrMsg - String with error message.
//-------------------------------------------------------------------
void halAssertHandler(char *szErrMsg)
{
    while (1)
    {
        HAL_LED_PORT(0x00);
        halMcuWaitMs(200);
        HAL_LED_PORT(0xFF);
        halMcuWaitMs(200);
    }
}
