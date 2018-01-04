//-------------------------------------------------------------------
// Filename: hal_board.h
// Description: zigbee-mcu1 board header file
//-------------------------------------------------------------------
//-------------------------------------------------------------------
// CONSTANTS
//-------------------------------------------------------------------
// Board properties
#define BOARD_NAME                     "ZIGBEE-MCU1"
#define NUM_LEDS                        8
#define NUM_BUTTONS                     2
#define NUM_BUZZER                      1

// Clock
#define BSP_CONFIG_CLOCK_MHZ            32

// LEDs
#define HAL_BOARD_IO_LED_PORT          1 

#define HAL_BOARD_IO_LED_1_PORT        1 
#define HAL_BOARD_IO_LED_1_PIN         0
#define HAL_BOARD_IO_LED_2_PORT        1 
#define HAL_BOARD_IO_LED_2_PIN         1
#define HAL_BOARD_IO_LED_3_PORT        1 
#define HAL_BOARD_IO_LED_3_PIN         2
#define HAL_BOARD_IO_LED_4_PORT        1 
#define HAL_BOARD_IO_LED_4_PIN         3
#define HAL_BOARD_IO_LED_5_PORT        1 
#define HAL_BOARD_IO_LED_5_PIN         4
#define HAL_BOARD_IO_LED_6_PORT        1 
#define HAL_BOARD_IO_LED_6_PIN         5
#define HAL_BOARD_IO_LED_7_PORT        1 
#define HAL_BOARD_IO_LED_7_PIN         6
#define HAL_BOARD_IO_LED_8_PORT        1 
#define HAL_BOARD_IO_LED_8_PIN         7

// Buttons
#define HAL_BOARD_IO_BTN_1_PORT        2   // Button K1
#define HAL_BOARD_IO_BTN_1_PIN         3
#define HAL_BOARD_IO_BTN_2_PORT        2   // Button K2
#define HAL_BOARD_IO_BTN_2_PIN         4

// Buzzer
#define HAL_BOARD_IO_BUZZER_PORT       0 
#define HAL_BOARD_IO_BUZZER_PIN        1

//-------------------------------------------------------------------
// MACROS
//-------------------------------------------------------------------
// LED
#define HAL_LED_SET_1()                 MCU_IO_SET_HIGH(HAL_BOARD_IO_LED_1_PORT, HAL_BOARD_IO_LED_1_PIN)
#define HAL_LED_SET_2()                 MCU_IO_SET_HIGH(HAL_BOARD_IO_LED_2_PORT, HAL_BOARD_IO_LED_2_PIN)
#define HAL_LED_SET_3()                 MCU_IO_SET_HIGH(HAL_BOARD_IO_LED_3_PORT, HAL_BOARD_IO_LED_3_PIN)
#define HAL_LED_SET_4()                 MCU_IO_SET_HIGH(HAL_BOARD_IO_LED_4_PORT, HAL_BOARD_IO_LED_4_PIN)
#define HAL_LED_SET_5()                 MCU_IO_SET_HIGH(HAL_BOARD_IO_LED_5_PORT, HAL_BOARD_IO_LED_5_PIN)
#define HAL_LED_SET_6()                 MCU_IO_SET_HIGH(HAL_BOARD_IO_LED_6_PORT, HAL_BOARD_IO_LED_6_PIN)
#define HAL_LED_SET_7()                 MCU_IO_SET_HIGH(HAL_BOARD_IO_LED_7_PORT, HAL_BOARD_IO_LED_7_PIN)
#define HAL_LED_SET_8()                 MCU_IO_SET_HIGH(HAL_BOARD_IO_LED_8_PORT, HAL_BOARD_IO_LED_8_PIN)

#define HAL_LED_CLR_1()                 MCU_IO_SET_LOW(HAL_BOARD_IO_LED_1_PORT, HAL_BOARD_IO_LED_1_PIN)
#define HAL_LED_CLR_2()                 MCU_IO_SET_LOW(HAL_BOARD_IO_LED_2_PORT, HAL_BOARD_IO_LED_2_PIN)
#define HAL_LED_CLR_3()                 MCU_IO_SET_LOW(HAL_BOARD_IO_LED_3_PORT, HAL_BOARD_IO_LED_3_PIN)
#define HAL_LED_CLR_4()                 MCU_IO_SET_LOW(HAL_BOARD_IO_LED_4_PORT, HAL_BOARD_IO_LED_4_PIN)
#define HAL_LED_CLR_5()                 MCU_IO_SET_LOW(HAL_BOARD_IO_LED_5_PORT, HAL_BOARD_IO_LED_5_PIN)
#define HAL_LED_CLR_6()                 MCU_IO_SET_LOW(HAL_BOARD_IO_LED_6_PORT, HAL_BOARD_IO_LED_6_PIN)
#define HAL_LED_CLR_7()                 MCU_IO_SET_LOW(HAL_BOARD_IO_LED_7_PORT, HAL_BOARD_IO_LED_7_PIN)
#define HAL_LED_CLR_8()                 MCU_IO_SET_LOW(HAL_BOARD_IO_LED_8_PORT, HAL_BOARD_IO_LED_8_PIN)

#define HAL_LED_TGL_1()                 MCU_IO_TGL(HAL_BOARD_IO_LED_1_PORT, HAL_BOARD_IO_LED_1_PIN)
#define HAL_LED_TGL_2()                 MCU_IO_TGL(HAL_BOARD_IO_LED_2_PORT, HAL_BOARD_IO_LED_2_PIN)
#define HAL_LED_TGL_3()                 MCU_IO_TGL(HAL_BOARD_IO_LED_3_PORT, HAL_BOARD_IO_LED_3_PIN)
#define HAL_LED_TGL_4()                 MCU_IO_TGL(HAL_BOARD_IO_LED_4_PORT, HAL_BOARD_IO_LED_4_PIN)
#define HAL_LED_TGL_5()                 MCU_IO_TGL(HAL_BOARD_IO_LED_5_PORT, HAL_BOARD_IO_LED_5_PIN)
#define HAL_LED_TGL_6()                 MCU_IO_TGL(HAL_BOARD_IO_LED_6_PORT, HAL_BOARD_IO_LED_6_PIN)
#define HAL_LED_TGL_7()                 MCU_IO_TGL(HAL_BOARD_IO_LED_7_PORT, HAL_BOARD_IO_LED_7_PIN)
#define HAL_LED_TGL_8()                 MCU_IO_TGL(HAL_BOARD_IO_LED_8_PORT, HAL_BOARD_IO_LED_8_PIN)

#define HAL_LED_PORT(val)               MCU_PORT_OUTPUT(HAL_BOARD_IO_LED_PORT, val)

// Buttons
#define HAL_BUTTON_1_PUSHED()          (!MCU_IO_GET(HAL_BOARD_IO_BTN_1_PORT, HAL_BOARD_IO_BTN_1_PIN))
#define HAL_BUTTON_2_PUSHED()          (!MCU_IO_GET(HAL_BOARD_IO_BTN_2_PORT, HAL_BOARD_IO_BTN_2_PIN))

// Buzzer
#define HAL_BUZZER_OFF()               MCU_IO_SET_HIGH(HAL_BOARD_IO_BUZZER_PORT, HAL_BOARD_IO_BUZZER_PIN)
#define HAL_BUZZER_ON()                MCU_IO_SET_LOW(HAL_BOARD_IO_BUZZER_PORT, HAL_BOARD_IO_BUZZER_PIN)
#define HAL_BUZZER_TGL()               MCU_IO_TGL(HAL_BOARD_IO_BUZZER_PORT, HAL_BOARD_IO_BUZZER_PIN)

// Debounce
#define HAL_DEBOUNCE(expr)             { char i; for (i=0; i<50; i++) { if (!(expr)) i = 0; } }

// Assert
#define HAL_ASSERT(szErrMsg)           { halAssertHandler(szErrMsg); }

//-------------------------------------------------------------------
// GLOBAL FUNCTIONS
//-------------------------------------------------------------------
void halBoardInit(void);
void halAssertHandler(char *szErrMsg);
