//-------------------------------------------------------------------
// Filename: hal_buzzer.c
// Description: hal buzzer library
//-------------------------------------------------------------------
//-------------------------------------------------------------------
// INCLUDES
//-------------------------------------------------------------------
#include "hal_defs.h"
#include "hal_cc8051.h"
#include "hal_mcu.h"
#include "hal_board.h"
#include "hal_buzzer.h"

//-------------------------------------------------------------------
// @fn      halBuzzerInit
// @brief    Set up timer 1  to generate an interrupt freq
// @param       uint16 freq
// @return  none
//-------------------------------------------------------------------
void halBuzzerInit(uint16 freq)
{
//    // Set prescaler divider value to 128
//    T1CTL |= 0x0C;
//
//    // Multiply cycles by 8 to get freq cycles
//    // 32MHz/128/64 gives approximately freq
//    // Set compare value
//    T1CC0H = HI_UINT16((32000000 / 256) / freq);
//    T1CC0L = LO_UINT16((32000000 / 256) / freq);
//
//    T1CCTL0 = 0x44;
//
//    T1CTL &= ~0x10; // T1CTL.OVFIF = 0
//    T1CTL &= ~0x02; // Stop timer
//    IEN1 &= ~0x02; // Disable interrupt
}

//-------------------------------------------------------------------
// @fn          halBuzzerOn
// @brief       Turn Buzzer on.
// @param       uint16 freq
// @return      none
//-------------------------------------------------------------------
void halBuzzerOn(uint16 freq)
{
//    T1CNTL = 0x00; // Reset counter value
//
//    T1CC0H = HI_UINT16((32000000 / 256) / freq);
//    T1CC0L = LO_UINT16((32000000 / 256) / freq);
//
//    T1CTL |= 0x02; // Start timer
//    IEN1 |= 0x02; // Enable interrupt
}

//-------------------------------------------------------------------
// @fn          halBuzzerOff
// @brief       Turn Buzzer off.
// @return      none
//-------------------------------------------------------------------
void halBuzzerOff(void)
{
//    T1CTL &= ~0x02; // Stop timer
//    IEN1 &= ~0x02; // Disable interrupt
//    HAL_BUZZER_OFF();
}

//-------------------------------------------------------------------
// @fn          halBuzzer
// @brief       Turn Buzzer on.
// @param       uint16 freq
// @return      none
//-------------------------------------------------------------------
void halBuzzer(uint16 ms)
{
//    T1CNTL = 0x00; // Reset counter value
//    T1CTL |= 0x02; // Start timer
//    IEN1 |= 0x02; // Enable interrupt
//    halMcuWaitMs(ms);
//    T1CTL &= ~0x02; // Stop timer
//    IEN1 &= ~0x02; // Disable interrupt
//    HAL_BUZZER_OFF();
}

//-------------------------------------------------------------------
// @fn      timer32k0_ISR
// @brief   ISR framework for the 32KHz timer component
// @param   none
// @return  none
//-------------------------------------------------------------------
//HAL_ISR_FUNCTION(T1_ISR, T1_VECTOR)
//{
//    HAL_BUZZER_TGL();
//}
