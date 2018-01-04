//-------------------------------------------------------------------
// Filename: hal_led.c
// Description: hal led library
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
            pLedData |= 0x01;
            break;
        case 2:
            pLedData |= 0x02;
            break;
        case 3:
            pLedData |= 0x04;
            break;
        case 4:
            pLedData |= 0x08;
            break;
        case 5:
            pLedData |= 0x10;
            break;
        case 6:
            pLedData |= 0x20;
            break;
        case 7:
            pLedData |= 0x40;
            break;
        case 8:
            pLedData |= 0x80;
            break;

        default:
            break;
    }
    HAL_LED_PORT(pLedData);
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
            pLedData &= ~(0x01);
            break;
        case 2:
            pLedData &= ~(0x02);
            break;
        case 3:
            pLedData &= ~(0x04);
            break;
        case 4:
            pLedData &= ~(0x08);
            break;
        case 5:
            pLedData &= ~(0x10);
            break;
        case 6:
            pLedData &= ~(0x20);
            break;
        case 7:
            pLedData &= ~(0x40);
            break;
        case 8:
            pLedData &= ~(0x80);
            break;
        default:
            break;
    }
    HAL_LED_PORT(pLedData);
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
            pLedData ^= 0x01;
            break;
        case 2:
            pLedData ^= 0x02;
            break;
        case 3:
            pLedData ^= 0x04;
            break;
        case 4:
            pLedData ^= 0x08;
            break;
        case 5:
            pLedData ^= 0x10;
            break;
        case 6:
            pLedData ^= 0x20;
            break;
        case 7:
            pLedData ^= 0x40;
            break;
        case 8:
            pLedData ^= 0x80;
            break;
        default:
            break;
    }
    HAL_LED_PORT(pLedData);
}


//-------------------------------------------------------------------
void halLedSetPort(uint8 port)
{
    HAL_LED_PORT(port);
}