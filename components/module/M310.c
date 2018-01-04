//-------------------------------------------------------------------
// Filename: M310.c
// Description: hal M310 module library ¥ú¾BÂ_°»´ú(DI/DO)
//-------------------------------------------------------------------
//-------------------------------------------------------------------
// INCLUDES
//-------------------------------------------------------------------
#include "hal_defs.h"
#include "hal_cc8051.h"
#include "hal_mcu.h"
#include "hal_board.h"
#include "M310.h"

//-------------------------------------------------------------------
void M310_Init(void)
{
    MCU_IO_INPUT(HAL_BOARD_SEN_1_PORT, HAL_BOARD_SEN_1_PIN, MCU_IO_PULLUP);
    MCU_IO_INPUT(HAL_BOARD_SEN_2_PORT, HAL_BOARD_SEN_2_PIN, MCU_IO_PULLUP);

    MCU_IO_OUTPUT(HAL_BOARD_LED_1_PORT, HAL_BOARD_LED_1_PIN,1);
    MCU_IO_OUTPUT(HAL_BOARD_LED_2_PORT, HAL_BOARD_LED_2_PIN,1);

}

//-------------------------------------------------------------------
uint8 M310_GetSensor(void)
{
	uint8 udi;
    MCU_IO_INPUT(HAL_BOARD_SEN_1_PORT, HAL_BOARD_SEN_1_PIN, MCU_IO_PULLUP);
    MCU_IO_INPUT(HAL_BOARD_SEN_2_PORT, HAL_BOARD_SEN_2_PIN, MCU_IO_PULLUP);
halMcuWaitMs(2);
	udi=0x03;
	if(HAL_SEN_1_DETECT())
		udi&=~(0x01);
	if(HAL_SEN_2_DETECT())
		udi&=~(0x02);
	return udi;
}
