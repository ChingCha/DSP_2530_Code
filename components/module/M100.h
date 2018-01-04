//-------------------------------------------------------------------
// Filename: M100.h
// Description: RTC library header file
//-------------------------------------------------------------------
#define HAL_BOARD_RTC_SCK_PORT        0
#define HAL_BOARD_RTC_SCK_PIN         5
#define HAL_BOARD_RTC_SIO_PORT        0
#define HAL_BOARD_RTC_SIO_PIN         4
#define HAL_BOARD_RTC_CS_PORT         0
#define HAL_BOARD_RTC_CS_PIN          7



#define HAL_RTC_SCK_DIR_OUT()           MCU_IO_OUTPUT(HAL_BOARD_RTC_SCK_PORT, HAL_BOARD_RTC_SCK_PIN, 1)
#define HAL_RTC_SCK_SET()              	MCU_IO_SET_HIGH(HAL_BOARD_RTC_SCK_PORT, HAL_BOARD_RTC_SCK_PIN)
#define HAL_RTC_SCK_CLR()              	MCU_IO_SET_LOW(HAL_BOARD_RTC_SCK_PORT, HAL_BOARD_RTC_SCK_PIN)

#define HAL_RTC_SIO_SET()              	MCU_IO_SET_HIGH(HAL_BOARD_RTC_SIO_PORT, HAL_BOARD_RTC_SIO_PIN)
#define HAL_RTC_SIO_CLR()              	MCU_IO_SET_LOW(HAL_BOARD_RTC_SIO_PORT, HAL_BOARD_RTC_SIO_PIN)
#define HAL_RTC_SIO_DIR_OUT()           MCU_IO_OUTPUT(HAL_BOARD_RTC_SIO_PORT, HAL_BOARD_RTC_SIO_PIN, 1)
#define HAL_RTC_SIO_DIR_IN()            MCU_IO_INPUT(HAL_BOARD_RTC_SIO_PORT, HAL_BOARD_RTC_SIO_PIN, MCU_IO_PULLUP)
#define HAL_RTC_SIO_VAL()              	MCU_IO_GET(HAL_BOARD_RTC_SIO_PORT, HAL_BOARD_RTC_SIO_PIN)

#define HAL_RTC_CS_DIR_OUT()           MCU_IO_OUTPUT(HAL_BOARD_RTC_CS_PORT, HAL_BOARD_RTC_CS_PIN, 0)
#define HAL_RTC_CS_EN()               	MCU_IO_SET_HIGH(HAL_BOARD_RTC_CS_PORT, HAL_BOARD_RTC_CS_PIN)
#define HAL_RTC_CS_DIS()               	MCU_IO_SET_LOW(HAL_BOARD_RTC_CS_PORT, HAL_BOARD_RTC_CS_PIN)

//-------------------------------------------------------------------
// GLOBAL FUNCTIONS
//-------------------------------------------------------------------
extern uint16 Year;
extern uint8 Month, Day, Hour, Min, Sec;

void M100_Init(void);
void SetDateTime(void);
void GetDateTime(void);
