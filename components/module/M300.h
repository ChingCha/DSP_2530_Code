//-------------------------------------------------------------------
// Filename: M300.h
// Description: hal M300 module library header file
//-------------------------------------------------------------------
#define HAL_BOARD_RX_PORT        0
#define HAL_BOARD_RX_PIN         5
#define HAL_RX_READY() 		    	(MCU_IO_GET(HAL_BOARD_RX_PORT, HAL_BOARD_RX_PIN))

#define HAL_BOARD_TX_PORT        0
#define HAL_BOARD_TX_PIN         4
#define HAL_TX_OFF()              	MCU_IO_SET_HIGH(HAL_BOARD_TX_PORT, HAL_BOARD_TX_PIN)
#define HAL_TX_ON()               	MCU_IO_SET_LOW(HAL_BOARD_TX_PORT, HAL_BOARD_TX_PIN)

//-------------------------------------------------------------------
// GLOBAL FUNCTIONS
//-------------------------------------------------------------------
void M300_Init(void);
void M300_TX(void);
uint8 M300_GetValue(void);