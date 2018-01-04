//-------------------------------------------------------------------
// Filename: M240.c
// Description: hal M240 Full-Color LED library
//-------------------------------------------------------------------
//-------------------------------------------------------------------
// INCLUDES
//-------------------------------------------------------------------
#include "hal_defs.h"
#include "hal_cc8051.h"
#include "hal_mcu.h"
#include "hal_board.h"
#include "M240.h"

//-------------------------------------------------------------------
// LOCAL VARIABLES
//-------------------------------------------------------------------
uint8 M240_LEDR_DutyCount;
uint8 M240_LEDR_DutyValue;
uint8 M240_LEDG_DutyCount;
uint8 M240_LEDG_DutyValue;
uint8 M240_LEDB_DutyCount;
uint8 M240_LEDB_DutyValue;

//-------------------------------------------------------------------
// LOCAL FUNCTIONS
//-------------------------------------------------------------------
//-------------------------------------------------------------------
// @fn      timerPwm_ISR
// @brief   ISR framework for the 1k timer component
// @param   none
// @return  none
//-------------------------------------------------------------------
HAL_ISR_FUNCTION(T4_ISR, T4_VECTOR)
{
    M240_LEDR_DutyCount++;
    if (M240_LEDR_DutyCount >= 100)
    {
        M240_LEDR_DutyCount = 0;
    }
    if (M240_LEDR_DutyCount >= M240_LEDR_DutyValue)
    {
        HAL_LEDR_OFF();
    }
    else
    {
        HAL_LEDR_ON();
    }
    M240_LEDG_DutyCount++;
    if (M240_LEDG_DutyCount >= 100)
    {
        M240_LEDG_DutyCount = 0;
    }
    if (M240_LEDG_DutyCount >= M240_LEDG_DutyValue)
    {
        HAL_LEDG_OFF();
    }
    else
    {
        HAL_LEDG_ON();
    }

    M240_LEDB_DutyCount++;
    if (M240_LEDB_DutyCount >= 100)
    {
        M240_LEDB_DutyCount = 0;
    }
    if (M240_LEDB_DutyCount >= M240_LEDB_DutyValue)
    {
        HAL_LEDB_OFF();
    }
    else
    {
        HAL_LEDB_ON();
    }
}

//-------------------------------------------------------------------
// GLOBAL FUNCTIONS
//-------------------------------------------------------------------
//-------------------------------------------------------------------
// @fn      M240_Init
// @brief    Set up timer 4 to generate an interrupt 10 kHz for PWM
// @return  none
//-------------------------------------------------------------------
void M240_Init(void)
{
	HAL_LEDR_OUTPUT();
	HAL_LEDG_OUTPUT();
	HAL_LEDB_OUTPUT();

	HAL_LEDR_OFF();
	HAL_LEDG_OFF();
	HAL_LEDB_OFF();

    M240_LEDR_DutyValue = 0;
    M240_LEDG_DutyValue = 0;
    M240_LEDB_DutyValue = 0;

    // Set prescaler divider value to 128 (8KHz)
    T4CTL |= 0x80;
    T4CTL &= ~(0x10); // Stop timer
    T4IE = 0; // Disable interrupt

}

//-------------------------------------------------------------------
void M240_LEDR_On(uint8 duty)
{
    M240_LEDR_DutyCount = 0;
    M240_LEDR_DutyValue = duty;

    T4CTL |= 0x10; // Start timer
    T4IE = 1; // Enable interrupt
}

//-------------------------------------------------------------------
void M240_LEDG_On(uint8 duty)
{
    M240_LEDG_DutyCount = 0;
    M240_LEDG_DutyValue = duty;

    T4CTL |= 0x10; // Start timer
    T4IE = 1; // Enable interrupt
}

//-------------------------------------------------------------------
void M240_LEDB_On(uint8 duty)
{
    M240_LEDB_DutyCount = 0;
    M240_LEDB_DutyValue = duty;

    T4CTL |= 0x10; // Start timer
    T4IE = 1; // Enable interrupt
}

//-------------------------------------------------------------------
void M240_Off(void)
{
    T4CTL &= ~(0x10); // Stop timer
    T4IE = 0; // Disable interrupt

    HAL_LEDR_OFF();
    HAL_LEDG_OFF();
    HAL_LEDB_OFF();
}
