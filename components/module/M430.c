//-------------------------------------------------------------------
// Filename: M430.c
// Description: hal M430 module library ¤ß¹q¹Ï(A/D)½d¨Ò
//-------------------------------------------------------------------
//-------------------------------------------------------------------
// INCLUDES
//-------------------------------------------------------------------
#include "hal_defs.h"
#include "hal_cc8051.h"
#include "hal_mcu.h"
#include "hal_board.h"
#include "hal_digio.h"
#include "hal_adc.h"
#include "M430.h"

//-------------------------------------------------------------------
// LOCAL VARIABLES
//-------------------------------------------------------------------
uint16 M430_Count;

//-------------------------------------------------------------------
// GLOBAL FUNCTIONS
//-------------------------------------------------------------------
//-------------------------------------------------------------------
// @fn      timerPwm_ISR
// @brief   ISR framework for the 1k timer component
// @param   none
// @return  none
//-------------------------------------------------------------------
HAL_ISR_FUNCTION(T4_ISR, T4_VECTOR)
{
    M430_Count++;
}

//-------------------------------------------------------------------
// Function Name : M430_Init
// Description : Initilization the M440 Module
//-------------------------------------------------------------------
void M430_Init(void)
{
    // Analog input
    MCU_IO_PERIPHERAL(HAL_BOARD_IO_ADC_PORT, HAL_BOARD_IO_ADC_CH);
}

//-------------------------------------------------------------------
// Function Name : M430_GetValue
// Description : Get the M430 Module ADC value
//-------------------------------------------------------------------
uint16 M430_GetValue(void)
{
    uint16 adcValue;
    adcValue = adcSampleSingle(ADC_REF_AVDD, ADC_12_BIT, HAL_BOARD_IO_ADC_CH);
    return adcValue;
}

//-------------------------------------------------------------------
// @fn      TIMER4_Init
// @brief   Set up timer 4 to generate an interrupt 1 kHz for 
//-------------------------------------------------------------------
void TIMER4_Init(void)
{
    // Set prescaler divider value to 128 (8KHz)
//    T4CTL |= 0x80; //T4CTL set value is 0xEB
    T4CTL |= 0x60;
    
    T4CTL &= ~(0x10); // Stop timer
    T4IE = 0; // Disable interrupt
}

//-------------------------------------------------------------------
// @fn         TIMER4_On
// @brief      Turn on the Timer 4.
// @param      uint8 duty
// @return     none
//-------------------------------------------------------------------
void TIMER4_On(void)
{
    T4CTL |= 0x10; // Start timer
    T4IE = 1; // Enable interrupt
}

//-------------------------------------------------------------------
// @fn          TIMER4_Off
// @brief       Turn off the Timer 4.
// @return      none
//-------------------------------------------------------------------
void TIMER4_Off(void)
{
    T4CTL &= ~(0x10); // Stop timer
    T4IE = 0; // Disable interrupt
}