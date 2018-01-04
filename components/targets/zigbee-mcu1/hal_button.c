//-------------------------------------------------------------------
// Filename: hal_button.c
// Description: zigbee-mcu1 button implementation library
//-------------------------------------------------------------------
//-------------------------------------------------------------------
// INCLUDES
//-------------------------------------------------------------------
#include "hal_defs.h"
#include "hal_cc8051.h"
#include "hal_mcu.h"
#include "hal_board.h"
#include "hal_button.h"

//-------------------------------------------------------------------
// GLOBAL FUNCTIONS
//-------------------------------------------------------------------
//-------------------------------------------------------------------
// @fn  halButtonPushed
// @brief
//      This function detects if 'S1' is being pushed. The function
//      implements software debounce. Return true only if previuosly called
//      with button not pushed. Return true only once each time the button
//      is pressed.
// Parameters:
// @param  void
// @return uint8
//          1: Button is being pushed
//          0: Button is not being pushed
//-------------------------------------------------------------------
uint8 halButtonPushed(void)
{
    uint8 v = HAL_BUTTON_NONE;

    if (HAL_BUTTON_1_PUSHED())
    {
        HAL_DEBOUNCE(!HAL_BUTTON_1_PUSHED());
        v = HAL_BUTTON_1;
    }
    if (HAL_BUTTON_2_PUSHED())
    {
        HAL_DEBOUNCE(!HAL_BUTTON_2_PUSHED());
        v = HAL_BUTTON_2;
    }

    return v;
}
