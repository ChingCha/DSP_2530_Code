//-------------------------------------------------------------------
// Filename: hal_motion.c
// Description: hal motion library
//-------------------------------------------------------------------
//-------------------------------------------------------------------
// INCLUDES
//-------------------------------------------------------------------
#include "hal_defs.h"
#include "hal_cc8051.h"
#include "hal_mcu.h"
#include "hal_board.h"
#include "hal_digio.h"
#include "M110.h"

uint16 M110_MotionValue;

static const digioConfig pinM110_Motion = 
{
    HAL_BOARD_IO_INT_PORT, HAL_BOARD_IO_INT_PIN, BV(HAL_BOARD_IO_INT_PIN), HAL_DIGIO_INPUT, 0
};
static void M110_MotionISR(void);

//-------------------------------------------------------------------
// @fn      M110_Init
// @brief    Set up port M110 motion interrupt
// @return  none
//-------------------------------------------------------------------
void M110_Init(void)
{
    M110_MotionValue = 0;
    halDigioConfig(&pinM110_Motion);
    MCU_IO_INPUT(HAL_BOARD_IO_INT_PORT, HAL_BOARD_IO_INT_PIN, MCU_IO_TRISTATE); //MCU_IO_TRISTATE MCU_IO_PULLUP
    halDigioIntSetEdge(&pinM110_Motion, HAL_DIGIO_INT_RISING_EDGE);
    halDigioIntConnect(&pinM110_Motion, &M110_MotionISR);
}

//-------------------------------------------------------------------
// @fn      M110_GetValue
// @brief   Enable int move interrupt
// @param   none
// @return  none
//-------------------------------------------------------------------
uint16 M110_GetValue(void)
{
    return M110_MotionValue;
}

//-------------------------------------------------------------------
// @fn      M110_Enable
// @brief   Enable int move interrupt
// @param   none
// @return  none
//-------------------------------------------------------------------
void M110_Enable(void)
{
    M110_MotionValue = 0;
    halDigioIntEnable(&pinM110_Motion);
}

//-------------------------------------------------------------------
// @fn      M110_Disable
// @brief   Disable Motion move interrupt
// @param   none
// @return  none
//-------------------------------------------------------------------
void M110_Disable(void)
{
    halDigioIntDisable(&pinM110_Motion);
}

//-------------------------------------------------------------------
// @fn      M110_MotionISR
// @brief   Interrupt service routine for Motion interrupt
// @param   none
// @return  none
//-------------------------------------------------------------------
static void M110_MotionISR(void)
{
    M110_MotionValue++;
}
