//-------------------------------------------------------------------
// Filename: M270.h
// Description: hal M270 module library header file
//-------------------------------------------------------------------
#define HAL_BOARD_KEY_1_PORT        0
#define HAL_BOARD_KEY_1_PIN         4
#define HAL_BOARD_KEY_2_PORT        0
#define HAL_BOARD_KEY_2_PIN         5

#define HAL_KEY_1_PUSHED() 		    	(!MCU_IO_GET(HAL_BOARD_KEY_1_PORT, HAL_BOARD_KEY_1_PIN))
#define HAL_KEY_2_PUSHED() 			    (!MCU_IO_GET(HAL_BOARD_KEY_2_PORT, HAL_BOARD_KEY_2_PIN))

#define HAL_BOARD_RELAY_PORT            0
#define HAL_BOARD_RELAY_PIN             7

#define HAL_RELAY_OFF()              	MCU_IO_SET_HIGH(HAL_BOARD_RELAY_PORT, HAL_BOARD_RELAY_PIN)
#define HAL_RELAY_ON()               	MCU_IO_SET_LOW(HAL_BOARD_RELAY_PORT, HAL_BOARD_RELAY_PIN)

//-------------------------------------------------------------------
// GLOBAL FUNCTIONS
//-------------------------------------------------------------------
void M270_Init(void);
void M270_SetDO(uint8 udo);
uint8 M270_GetDI(void);