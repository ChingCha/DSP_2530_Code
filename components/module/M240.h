//-------------------------------------------------------------------
// Filename: M240.h
// Description: hal M240 Full-Color LED library header file
//-------------------------------------------------------------------
// LED
#define HAL_BOARD_IO_LED_R_PORT            0
#define HAL_BOARD_IO_LED_R_PIN             5 // P0_5 -> LED_R
#define HAL_BOARD_IO_LED_G_PORT            0
#define HAL_BOARD_IO_LED_G_PIN             7 // P0_7 -> LED_G
#define HAL_BOARD_IO_LED_B_PORT            0
#define HAL_BOARD_IO_LED_B_PIN             4 // P0_4 -> LED_B

#define HAL_LEDR_OUTPUT()           MCU_IO_OUTPUT(HAL_BOARD_IO_LED_R_PORT, HAL_BOARD_IO_LED_R_PIN, 1)
#define HAL_LEDG_OUTPUT()           MCU_IO_OUTPUT(HAL_BOARD_IO_LED_G_PORT, HAL_BOARD_IO_LED_G_PIN, 1)
#define HAL_LEDB_OUTPUT()           MCU_IO_OUTPUT(HAL_BOARD_IO_LED_B_PORT, HAL_BOARD_IO_LED_B_PIN, 1)

#define HAL_LEDR_ON()		        MCU_IO_SET_HIGH(HAL_BOARD_IO_LED_R_PORT, HAL_BOARD_IO_LED_R_PIN)
#define HAL_LEDG_ON()		        MCU_IO_SET_HIGH(HAL_BOARD_IO_LED_G_PORT, HAL_BOARD_IO_LED_G_PIN)
#define HAL_LEDB_ON()		        MCU_IO_SET_HIGH(HAL_BOARD_IO_LED_B_PORT, HAL_BOARD_IO_LED_B_PIN)

#define HAL_LEDR_OFF()		        MCU_IO_SET_LOW(HAL_BOARD_IO_LED_R_PORT, HAL_BOARD_IO_LED_R_PIN)
#define HAL_LEDG_OFF()		        MCU_IO_SET_LOW(HAL_BOARD_IO_LED_G_PORT, HAL_BOARD_IO_LED_G_PIN)
#define HAL_LEDB_OFF()		        MCU_IO_SET_LOW(HAL_BOARD_IO_LED_B_PORT, HAL_BOARD_IO_LED_B_PIN)

//-------------------------------------------------------------------
// GLOBAL FUNCTIONS
//-------------------------------------------------------------------
void M240_Init(void);
void M240_LEDR_On(uint8 duty);
void M240_LEDG_On(uint8 duty);
void M240_LEDB_On(uint8 duty);
void M240_Off(void);
