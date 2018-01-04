//-------------------------------------------------------------------
// Filename: M150.c
// Description: hal motion library 霍爾元件電流偵測(A/D)
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
#include "M150.h"

//-------------------------------------------------------------------
// @fn      M150_Init
// @return  none
//-------------------------------------------------------------------
void M150_Init(void)
{
    // Analog input
    MCU_IO_PERIPHERAL(HAL_BOARD_IO_ADC_PORT, HAL_BOARD_IO_ADC_CH);
}

//-------------------------------------------------------------------
// @fn      M150_GetValue
// @brief   Get this M150 module value
// @param   none
// @return  none
//-------------------------------------------------------------------
uint16 M150_GetValue(void)
{
    uint16 adcValue;
    adcValue = adcSampleSingle(ADC_REF_AVDD, ADC_12_BIT, HAL_BOARD_IO_ADC_CH);
    return adcValue;
}
