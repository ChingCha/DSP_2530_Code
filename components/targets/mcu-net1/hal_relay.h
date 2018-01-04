//-------------------------------------------------------------------
// Filename: hal_relay.h
//-------------------------------------------------------------------
// Buttons
#define HAL_BOARD_IO_BTN_1_PORT       2 // Button K1
#define HAL_BOARD_IO_BTN_1_PIN        3
#define HAL_BOARD_IO_BTN_2_PORT       2 // Button K2
#define HAL_BOARD_IO_BTN_2_PIN        4

#define HAL_SW_1_PUSHED() 	      (!MCU_IO_GET(HAL_BOARD_IO_BTN_1_PORT, HAL_BOARD_IO_BTN_1_PIN))
#define HAL_SW_2_PUSHED() 	      (!MCU_IO_GET(HAL_BOARD_IO_BTN_2_PORT, HAL_BOARD_IO_BTN_2_PIN))

// RELAY
#define HAL_BOARD_RELAY1_PORT         1
#define HAL_BOARD_RELAY1_PIN          0
#define HAL_BOARD_RELAY2_PORT         1
#define HAL_BOARD_RELAY2_PIN          1

#define HAL_RELAY1_OUTPUT()           MCU_IO_OUTPUT(HAL_BOARD_RELAY1_PORT, HAL_BOARD_RELAY1_PIN,1);
#define HAL_RELAY2_OUTPUT()           MCU_IO_OUTPUT(HAL_BOARD_RELAY2_PORT, HAL_BOARD_RELAY2_PIN,1);

#define HAL_RELAY1_OFF()              MCU_IO_SET_HIGH(HAL_BOARD_RELAY1_PORT, HAL_BOARD_RELAY1_PIN)
#define HAL_RELAY1_ON()               MCU_IO_SET_LOW(HAL_BOARD_RELAY1_PORT, HAL_BOARD_RELAY1_PIN)
#define HAL_RELAY2_OFF()              MCU_IO_SET_HIGH(HAL_BOARD_RELAY2_PORT, HAL_BOARD_RELAY2_PIN)
#define HAL_RELAY2_ON()               MCU_IO_SET_LOW(HAL_BOARD_RELAY2_PORT, HAL_BOARD_RELAY2_PIN)

//-------------------------------------------------------------------
// GLOBAL FUNCTIONS
//-------------------------------------------------------------------
extern void RELAY_Init(void);
extern void RELAY_SetDO(uint8 udo);
extern uint8 RELAY_GetDI(void);