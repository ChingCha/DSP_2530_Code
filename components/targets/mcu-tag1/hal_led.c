//-------------------------------------------------------------------
// Filename: hal_led.c
// Description: zigbee-mcu1 led implementation library
//-------------------------------------------------------------------
//-------------------------------------------------------------------
// INCLUDES
//-------------------------------------------------------------------
#include "hal_defs.h"
#include "hal_cc8051.h"
#include "hal_mcu.h"
#include "hal_board.h"
#include "hal_led.h"

//-------------------------------------------------------------------
// GLOBAL FUNCTIONS
//-------------------------------------------------------------------
//-------------------------------------------------------------------
// @fn          halLedSet
// @brief       Turn LED on.
// @param       uint8 id - led to set
// @return      none
//-------------------------------------------------------------------
void halLedSet(uint8 id)
{
    switch (id)
    {
        case 1:
            HAL_LED_SET_1();
            break;
        case 2:
            HAL_LED_SET_2();
            break;
        case 3:
            HAL_LED_SET_3();
            break;
        case 4:
            HAL_LED_SET_4();
            break;
        case 5:
            HAL_LED_SET_5();
            break;
        case 6:
            HAL_LED_SET_6();
            break;
        case 7:
            HAL_LED_SET_7();
            break;
        case 8:
            HAL_LED_SET_8();
            break;

        default:
            break;
    }
}

//-------------------------------------------------------------------
// @fn          halLedClear
// @brief       Turn LED off.
// @param       uint8 id - led to clear
// @return      none
//-------------------------------------------------------------------
void halLedClear(uint8 id)
{
    switch (id)
    {
        case 1:
            HAL_LED_CLR_1();
            break;
        case 2:
            HAL_LED_CLR_2();
            break;
        case 3:
            HAL_LED_CLR_3();
            break;
        case 4:
            HAL_LED_CLR_4();
            break;
        case 5:
            HAL_LED_CLR_5();
            break;
        case 6:
            HAL_LED_CLR_6();
            break;
        case 7:
            HAL_LED_CLR_7();
            break;
        case 8:
            HAL_LED_CLR_8();
            break;
        default:
            break;
    }
}

//-------------------------------------------------------------------
// @fn          halLedToggle
// @brief       Change state of LED. If on, turn it off. Else turn on.
// @param       uint8 id - led to toggle
// @return      none
//-------------------------------------------------------------------
void halLedToggle(uint8 id)
{
    switch (id)
    {
        case 1:
            HAL_LED_TGL_1();
            break;
        case 2:
            HAL_LED_TGL_2();
            break;
        case 3:
            HAL_LED_TGL_3();
            break;
        case 4:
            HAL_LED_TGL_4();
            break;
        case 5:
            HAL_LED_TGL_5();
            break;
        case 6:
            HAL_LED_TGL_6();
            break;
        case 7:
            HAL_LED_TGL_7();
            break;
        case 8:
            HAL_LED_TGL_8();
            break;
        default:
            break;
    }
}

//-------------------------------------------------------------------
void halLedSetPort(uint8 port)
{
    HAL_LED_PORT(port);
}