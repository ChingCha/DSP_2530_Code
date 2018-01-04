//-------------------------------------------------------------------
// Filename: hal_board.h
// Description: MCU-KIT1 board with CC2530
//-------------------------------------------------------------------
//-------------------------------------------------------------------
// CONSTANTS
//-------------------------------------------------------------------
// Clock
#define BSP_CONFIG_CLOCK_MHZ                32

// SPI
#define HAL_BOARD_IO_SPI_MISO_PORT          0
#define HAL_BOARD_IO_SPI_MISO_PIN           6
#define HAL_BOARD_IO_SPI_MOSI_PORT          0
#define HAL_BOARD_IO_SPI_MOSI_PIN           4
#define HAL_BOARD_IO_SPI_CLK_PORT           0
#define HAL_BOARD_IO_SPI_CLK_PIN            5
#define HAL_BOARD_IO_SPI_CS_PORT            0
#define HAL_BOARD_IO_SPI_CS_PIN             7

// I2C 
#define HAL_BOARD_IO_I2C_SCL_PORT           0
#define HAL_BOARD_IO_I2C_SCL_PIN            5
#define HAL_BOARD_IO_I2C_SDA_PORT           0
#define HAL_BOARD_IO_I2C_SDA_PIN            4

// A/D
#define HAL_BOARD_IO_ADC_PORT               0
#define HAL_BOARD_IO_ADC_CH                 0

// INT
#define HAL_BOARD_IO_INT_PORT               0
#define HAL_BOARD_IO_INT_PIN                0

// DO
#define HAL_BOARD_IO_DO_PORT                0
#define HAL_BOARD_IO_DO_PIN                 0

// Buzzer
#define HAL_BOARD_IO_BUZZER_PORT            0 
#define HAL_BOARD_IO_BUZZER_PIN             1

// UART
#define HAL_BOARD_IO_UART_TXD_PORT          0
#define HAL_BOARD_IO_UART_TXD_PIN           3
#define HAL_BOARD_IO_UART_RXD_PORT          0
#define HAL_BOARD_IO_UART_RXD_PIN           2

// RTC
#define HAL_BOARD_RTC_SCK_PORT              1
#define HAL_BOARD_RTC_SCK_PIN               3
#define HAL_BOARD_RTC_SIO_PORT              1
#define HAL_BOARD_RTC_SIO_PIN               2
#define HAL_BOARD_RTC_CS_PORT               1
#define HAL_BOARD_RTC_CS_PIN                4

// RELAY
#define HAL_BOARD_RELAY1_PORT               1
#define HAL_BOARD_RELAY1_PIN                0
#define HAL_BOARD_RELAY2_PORT               1
#define HAL_BOARD_RELAY2_PIN                1

// RS485
#define HAL_BOARD_RS485_EN_PORT             1
#define HAL_BOARD_RS485_EN_PIN              6

// Debounce
#define HAL_DEBOUNCE(expr)    { char i; for (i=0; i<50; i++) { if (!(expr)) i = 0; } }

// Assert
#define HAL_ASSERT(szErrMsg) { halAssertHandler(szErrMsg); }

//-------------------------------------------------------------------
// MACROS
//-------------------------------------------------------------------

// RELAY
#define HAL_RELAY1_OFF()               MCU_IO_SET_HIGH(HAL_BOARD_RELAY1_PORT, HAL_BOARD_RELAY1_PIN)
#define HAL_RELAY1_ON()                MCU_IO_SET_LOW(HAL_BOARD_RELAY1_PORT, HAL_BOARD_RELAY1_PIN)
#define HAL_RELAY2_OFF()               MCU_IO_SET_HIGH(HAL_BOARD_RELAY2_PORT, HAL_BOARD_RELAY2_PIN)
#define HAL_RELAY2_ON()                MCU_IO_SET_LOW(HAL_BOARD_RELAY2_PORT, HAL_BOARD_RELAY2_PIN)

// Buzzer
#define HAL_BUZZER_OFF()               MCU_IO_SET_HIGH(HAL_BOARD_IO_BUZZER_PORT, HAL_BOARD_IO_BUZZER_PIN)
#define HAL_BUZZER_ON()                MCU_IO_SET_LOW(HAL_BOARD_IO_BUZZER_PORT, HAL_BOARD_IO_BUZZER_PIN)
#define HAL_BUZZER_TGL()               MCU_IO_TGL(HAL_BOARD_IO_BUZZER_PORT, HAL_BOARD_IO_BUZZER_PIN)

// SPI
#define HAL_SPI_INIT()                 {MCU_IO_OUTPUT(HAL_BOARD_IO_SPI_MOSI_PORT, HAL_BOARD_IO_SPI_MOSI_PIN, 1);MCU_IO_OUTPUT(HAL_BOARD_IO_SPI_CLK_PORT, HAL_BOARD_IO_SPI_CLK_PIN, 1);MCU_IO_OUTPUT(HAL_BOARD_IO_SPI_CS_PORT, HAL_BOARD_IO_SPI_CS_PIN, 1);MCU_IO_INPUT(HAL_BOARD_IO_SPI_MISO_PORT, HAL_BOARD_IO_SPI_MISO_PIN,MCU_IO_PULLUP);}

#define HAL_SPI_MOSI_SET()             MCU_IO_SET_HIGH(HAL_BOARD_IO_SPI_MOSI_PORT, HAL_BOARD_IO_SPI_MOSI_PIN)
#define HAL_SPI_MOSI_CLR()             MCU_IO_SET_LOW(HAL_BOARD_IO_SPI_MOSI_PORT, HAL_BOARD_IO_SPI_MOSI_PIN)

#define HAL_SPI_CLK_SET()              MCU_IO_SET_HIGH(HAL_BOARD_IO_SPI_CLK_PORT, HAL_BOARD_IO_SPI_CLK_PIN)
#define HAL_SPI_CLK_CLR()              MCU_IO_SET_LOW(HAL_BOARD_IO_SPI_CLK_PORT, HAL_BOARD_IO_SPI_CLK_PIN)

#define HAL_SPI_CS_EN()                MCU_IO_SET_LOW(HAL_BOARD_IO_SPI_CS_PORT, HAL_BOARD_IO_SPI_CS_PIN)
#define HAL_SPI_CS_DIS()               MCU_IO_SET_HIGH(HAL_BOARD_IO_SPI_CS_PORT, HAL_BOARD_IO_SPI_CS_PIN)

#define HAL_SPI_MISO_VAL() 	       MCU_IO_GET(HAL_BOARD_IO_SPI_MISO_PORT, HAL_BOARD_IO_SPI_MISO_PIN)

// I2C
#define HAL_I2C_SCL_DIR_OUT()          MCU_IO_OUTPUT(HAL_BOARD_IO_I2C_SCL_PORT, HAL_BOARD_IO_I2C_SCL_PIN,0)
#define HAL_I2C_SCL_SET()              MCU_IO_SET_HIGH(HAL_BOARD_IO_I2C_SCL_PORT, HAL_BOARD_IO_I2C_SCL_PIN)
#define HAL_I2C_SCL_CLR()              MCU_IO_SET_LOW(HAL_BOARD_IO_I2C_SCL_PORT, HAL_BOARD_IO_I2C_SCL_PIN)

#define HAL_I2C_SDA_SET()              MCU_IO_SET_HIGH(HAL_BOARD_IO_I2C_SDA_PORT, HAL_BOARD_IO_I2C_SDA_PIN)
#define HAL_I2C_SDA_CLR()              MCU_IO_SET_LOW(HAL_BOARD_IO_I2C_SDA_PORT, HAL_BOARD_IO_I2C_SDA_PIN)
#define HAL_I2C_SDA_DIR_OUT()          MCU_IO_OUTPUT(HAL_BOARD_IO_I2C_SDA_PORT, HAL_BOARD_IO_I2C_SDA_PIN,1)
#define HAL_I2C_SDA_DIR_IN()           MCU_IO_INPUT(HAL_BOARD_IO_I2C_SDA_PORT, HAL_BOARD_IO_I2C_SDA_PIN,MCU_IO_PULLUP)
#define HAL_I2C_SDA_VAL()              MCU_IO_GET(HAL_BOARD_IO_I2C_SDA_PORT, HAL_BOARD_IO_I2C_SDA_PIN)

// DO
#define HAL_DO_OFF()                   MCU_IO_SET_HIGH(HAL_BOARD_IO_DO_PORT, HAL_BOARD_IO_DO_PIN)
#define HAL_DO_ON()                    MCU_IO_SET_LOW(HAL_BOARD_IO_DO_PORT, HAL_BOARD_IO_DO_PIN)
#define HAL_DO_OUTPUT()                MCU_IO_OUTPUT(HAL_BOARD_IO_DO_PORT, HAL_BOARD_IO_DO_PIN, 1)

// RTC
#define HAL_RTC_SCK_DIR_OUT()          MCU_IO_OUTPUT(HAL_BOARD_RTC_SCK_PORT, HAL_BOARD_RTC_SCK_PIN, 1)
#define HAL_RTC_SCK_SET()              MCU_IO_SET_HIGH(HAL_BOARD_RTC_SCK_PORT, HAL_BOARD_RTC_SCK_PIN)
#define HAL_RTC_SCK_CLR()              MCU_IO_SET_LOW(HAL_BOARD_RTC_SCK_PORT, HAL_BOARD_RTC_SCK_PIN)

#define HAL_RTC_SIO_SET()              MCU_IO_SET_HIGH(HAL_BOARD_RTC_SIO_PORT, HAL_BOARD_RTC_SIO_PIN)
#define HAL_RTC_SIO_CLR()              MCU_IO_SET_LOW(HAL_BOARD_RTC_SIO_PORT, HAL_BOARD_RTC_SIO_PIN)
#define HAL_RTC_SIO_DIR_OUT()          MCU_IO_OUTPUT(HAL_BOARD_RTC_SIO_PORT, HAL_BOARD_RTC_SIO_PIN, 1)
#define HAL_RTC_SIO_DIR_IN()           MCU_IO_INPUT(HAL_BOARD_RTC_SIO_PORT, HAL_BOARD_RTC_SIO_PIN, MCU_IO_PULLUP)
#define HAL_RTC_SIO_VAL()              MCU_IO_GET(HAL_BOARD_RTC_SIO_PORT, HAL_BOARD_RTC_SIO_PIN)

#define HAL_RTC_CS_DIR_OUT()           MCU_IO_OUTPUT(HAL_BOARD_RTC_CS_PORT, HAL_BOARD_RTC_CS_PIN, 0)
#define HAL_RTC_CS_EN()                MCU_IO_SET_HIGH(HAL_BOARD_RTC_CS_PORT, HAL_BOARD_RTC_CS_PIN)
#define HAL_RTC_CS_DIS()               MCU_IO_SET_LOW(HAL_BOARD_RTC_CS_PORT, HAL_BOARD_RTC_CS_PIN)

// RS485
#define HAL_RS485_SET_OUTPUT()         MCU_IO_OUTPUT(HAL_BOARD_RS485_EN_PORT, HAL_BOARD_RS485_EN_PIN,1)
#define HAL_RS485_SET_TX()             MCU_IO_SET_HIGH(HAL_BOARD_RS485_EN_PORT, HAL_BOARD_RS485_EN_PIN)
#define HAL_RS485_SET_RX()             MCU_IO_SET_LOW(HAL_BOARD_RS485_EN_PORT, HAL_BOARD_RS485_EN_PIN)

//-------------------------------------------------------------------
// GLOBAL DATA
//-------------------------------------------------------------------

//-------------------------------------------------------------------
// FUNCTION PROTOTYPES
//-------------------------------------------------------------------
void halBoardInit(void);
void halAssertHandler(char *szErrMsg);
