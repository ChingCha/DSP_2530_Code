//-------------------------------------------------------------------
// Filename: M130.h
// Description: hal M130 module library header file
//-------------------------------------------------------------------

// DI
#define HAL_BOARD_IO_IN_PORT               0
#define HAL_BOARD_IO_IN_PIN                0

#define HAL_IRIN_DIR_IN()           MCU_IO_INPUT(HAL_BOARD_IO_IN_PORT, HAL_BOARD_IO_IN_PIN, MCU_IO_PULLUP)
#define HAL_IRIN()                  MCU_IO_GET(HAL_BOARD_IO_IN_PORT, HAL_BOARD_IO_IN_PIN)

extern uint8 M130_Buf[];
//-------------------------------------------------------------------
// GLOBAL FUNCTIONS
//-------------------------------------------------------------------
void M130_Init(void);
uint8 M130_GetData(void);
