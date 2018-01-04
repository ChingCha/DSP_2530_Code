//-------------------------------------------------------------------
// Filename: M300.c
// Description: hal M300 module library ¶W­µªi´ú¶Z(DI/DO)
//-------------------------------------------------------------------
//-------------------------------------------------------------------
// INCLUDES
//-------------------------------------------------------------------
#include "hal_defs.h"
#include "hal_cc8051.h"
#include "hal_mcu.h"
#include "hal_board.h"
#include "M300.h"

//-------------------------------------------------------------------
void M300_Init(void)
{
    MCU_IO_INPUT(HAL_BOARD_RX_PORT, HAL_BOARD_RX_PIN, MCU_IO_PULLUP);
    MCU_IO_OUTPUT(HAL_BOARD_TX_PORT, HAL_BOARD_TX_PIN,1);
}

//-------------------------------------------------------------------
void M300_TX(void)
{
    HAL_TX_ON();
    halMcuWaitUs(5);  
    HAL_TX_OFF();
}

//-------------------------------------------------------------------
uint8 M300_GetValue(void)
{
	uint8 udi;
    for(udi=0;udi<250;udi++)
    {
	    if(HAL_RX_READY())
            break;
        halMcuWaitUs(1);
    }
	return udi;
}
