//-------------------------------------------------------------------
// Filename: M250.h
// Description: M250 library header file
//-------------------------------------------------------------------

#define HAL_BOARD_RF_CLK_PORT        0
#define HAL_BOARD_RF_CLK_PIN         4
#define HAL_BOARD_RF_DAT_PORT        0
#define HAL_BOARD_RF_DAT_PIN         5
#define HAL_BOARD_RF_MOD_PORT        0
#define HAL_BOARD_RF_MOD_PIN         7

#define HAL_RF_DAT() 		    	    MCU_IO_GET(HAL_BOARD_RF_DAT_PORT, HAL_BOARD_RF_DAT_PIN)
#define HAL_RF_CLK() 		    	    MCU_IO_GET(HAL_BOARD_RF_CLK_PORT, HAL_BOARD_RF_CLK_PIN)

#define HAL_RF_MOD_SET()              	MCU_IO_SET_HIGH(HAL_BOARD_RF_MOD_PORT, HAL_BOARD_RF_MOD_PIN)
#define HAL_RF_MOD_CLR()               	MCU_IO_SET_LOW(HAL_BOARD_RF_MOD_PORT, HAL_BOARD_RF_MOD_PIN)

#define HAL_RF_CLK_DIR_IN()             MCU_IO_OUTPUT(HAL_BOARD_RF_CLK_PORT, HAL_BOARD_RF_CLK_PIN, 1)
#define HAL_RF_DAT_DIR_IN()             MCU_IO_INPUT(HAL_BOARD_RF_DAT_PORT, HAL_BOARD_RF_DAT_PIN, MCU_IO_PULLUP)
#define HAL_RF_MOD_DIR_OUT()            MCU_IO_INPUT(HAL_BOARD_RF_MOD_PORT, HAL_BOARD_RF_MOD_PIN, MCU_IO_PULLUP)

extern uint8 rfTagUID[5];
//-------------------------------------------------------------------
// GLOBAL FUNCTIONS
//-------------------------------------------------------------------
void M250_Init(void);
uint8 M250_ReadTag(void);
