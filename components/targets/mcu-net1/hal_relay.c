//-------------------------------------------------------------------
// Filename: hal_relay.c
//-------------------------------------------------------------------
//-------------------------------------------------------------------
// INCLUDES
//-------------------------------------------------------------------
#include "hal_defs.h"
#include "hal_cc8051.h"
#include "hal_mcu.h"
#include "hal_board.h"
#include "hal_relay.h"

//-------------------------------------------------------------------
void RELAY_Init(void)
{   
    // switch init
    MCU_IO_INPUT(HAL_BOARD_IO_BTN_1_PORT, HAL_BOARD_IO_BTN_1_PIN, MCU_IO_PULLUP);
    MCU_IO_INPUT(HAL_BOARD_IO_BTN_2_PORT, HAL_BOARD_IO_BTN_2_PIN, MCU_IO_PULLUP);
    // relay init
    MCU_IO_OUTPUT(HAL_BOARD_RELAY1_PORT, HAL_BOARD_RELAY1_PIN,1);
    MCU_IO_OUTPUT(HAL_BOARD_RELAY2_PORT, HAL_BOARD_RELAY2_PIN,1);
    HAL_RELAY1_OFF();
    HAL_RELAY2_OFF();
}

//-------------------------------------------------------------------
void RELAY_SetDO(uint8 udo)
{
	if(udo == 0)
        {
          HAL_RELAY2_ON();
          HAL_RELAY1_OFF();
        }
	else
          {
            HAL_RELAY1_ON();
            HAL_RELAY2_OFF();
          }
}

//-------------------------------------------------------------------
uint8 RELAY_GetDI(void)
{
	uint8 udi;

	udi=0x03;
        
	if(HAL_SW_1_PUSHED())
		udi&=~(0x01);
	
        if(HAL_SW_2_PUSHED())
		udi&=~(0x02);
	
        return udi;
}