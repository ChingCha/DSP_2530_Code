//-------------------------------------------------------------------
// Filename: M310.h
// Description: hal M310 module library header file
//-------------------------------------------------------------------
#define HAL_BOARD_SEN_1_PORT        0
#define HAL_BOARD_SEN_1_PIN         4
#define HAL_BOARD_SEN_2_PORT        0
#define HAL_BOARD_SEN_2_PIN         6

#define HAL_BOARD_LED_1_PORT        0
#define HAL_BOARD_LED_1_PIN         5
#define HAL_BOARD_LED_2_PORT        0
#define HAL_BOARD_LED_2_PIN         7

#define HAL_SEN_1_DETECT()          (!MCU_IO_GET(HAL_BOARD_SEN_1_PORT, HAL_BOARD_SEN_1_PIN))
#define HAL_SEN_2_DETECT() 	    (!MCU_IO_GET(HAL_BOARD_SEN_2_PORT, HAL_BOARD_SEN_2_PIN))

//-------------------------------------------------------------------
// GLOBAL FUNCTIONS
//-------------------------------------------------------------------
void M310_Init(void);
uint8 M310_GetSensor(void);