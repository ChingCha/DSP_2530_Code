//-------------------------------------------------------------------
// Filename: M130.c
// Description: hal M130 module library 紅外線接收模組(DI)
//-------------------------------------------------------------------
//-------------------------------------------------------------------
// INCLUDES
//-------------------------------------------------------------------
#include "hal_defs.h"
#include "hal_cc8051.h"
#include "hal_mcu.h"
#include "hal_board.h"
#include "M130.h"

uint8 M130_Buf[4];
//-------------------------------------------------------------------
// GLOBAL FUNCTIONS
//-------------------------------------------------------------------
// @fn      M130_Init
// @return  none
//-------------------------------------------------------------------
void M130_Init(void)
{
    HAL_IRIN_DIR_IN();
}

//-------------------------------------------------------------------
// @fn      M130_GetValue
// @brief   Get this M190 module value
// @param   none
// @return  none
//-------------------------------------------------------------------
uint8 M130_GetData(void)
{
    uint8 i, n;

    for (i = 0; i < 8; i++)
    {
        M130_Buf[i] = 0;
    }

    i = 0;
    while (TRUE)
    {
        if (HAL_IRIN() == 0)
        {
            break;
        }
        halMcuWaitUs(500);
        i++;
        if (i > 200)
        {
            return 0;
        }
    }

    i = 0;
    while (TRUE)
    {
        if (HAL_IRIN() == 1)
        {
            break;
        }
        halMcuWaitUs(100);
        i++;
        if (i > 200)
        {
            return 0;
        }
    }

    i = 0;
    while (TRUE)
    {
        if (HAL_IRIN() == 0)
        {
            break;
        }
        halMcuWaitUs(50);
        i++;
        if (i > 200)
        {
            return 0;
        }
    }

    for (n = 0; n < 32; n++)
    {
        i = 0;
        while (TRUE)
        {
            if (HAL_IRIN() == 1)
            {
                break;
            }
            halMcuWaitUs(50);
            i++;
            if (i > 200)
            {
                return 1;
            }
        }
        while (TRUE)
        {
            if (HAL_IRIN() == 0)
            {
                break;
            }
            halMcuWaitUs(50);
            i++;
            if (i > 200)
            {
                return 1;
            }
        }
        if (i > 30)
        {
            M130_Buf[n / 8] |= (0x01 << (n % 8));
        }
    }
    return 1;
}
