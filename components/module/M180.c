//-------------------------------------------------------------------
// Filename: M180.c
// Description: hal M180 library
//-------------------------------------------------------------------
//-------------------------------------------------------------------
// INCLUDES
//-------------------------------------------------------------------
#include "hal_defs.h"
#include "hal_cc8051.h"
#include "hal_mcu.h"
#include "hal_board.h"
#include "hal_digio.h"
#include "M180.h"

//-------------------------------------------------------------------
// LOCAL VARIABLES
//-------------------------------------------------------------------
uint16 M180_MotionValue;

static const digioConfig pinM180_Motion = 
{
    HAL_BOARD_IO_INT_PORT, HAL_BOARD_IO_INT_PIN, BV(HAL_BOARD_IO_INT_PIN), HAL_DIGIO_INPUT, 0
};

//-------------------------------------------------------------------
// LOCAL FUNCTIONS
//-------------------------------------------------------------------
static void M180_MotionISR(void)
{
    M180_MotionValue++;
}

//-------------------------------------------------------------------
// GLOBAL FUNCTIONS
//-------------------------------------------------------------------
void M180_Init(void)
{
    M180_MotionValue = 0;
    halDigioConfig(&pinM180_Motion);
    MCU_IO_INPUT(HAL_BOARD_IO_INT_PORT, HAL_BOARD_IO_INT_PIN, MCU_IO_TRISTATE); //MCU_IO_TRISTATE MCU_IO_PULLUP
    halDigioIntSetEdge(&pinM180_Motion, HAL_DIGIO_INT_RISING_EDGE);
    halDigioIntConnect(&pinM180_Motion, &M180_MotionISR);
}

//-------------------------------------------------------------------
uint16 M180_GetValue(void)
{
    return M180_MotionValue;
}

//-------------------------------------------------------------------
void M180_Enable(void)
{
    M180_MotionValue = 0;
    halDigioIntEnable(&pinM180_Motion);
}

//-------------------------------------------------------------------
void M180_Disable(void)
{
    halDigioIntDisable(&pinM180_Motion);
}

