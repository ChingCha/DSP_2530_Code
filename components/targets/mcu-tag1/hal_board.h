//-------------------------------------------------------------------
// Filename: hal_board.h
// Description: zigbee-mcu1 board header file
//-------------------------------------------------------------------
//-------------------------------------------------------------------
// CONSTANTS
//-------------------------------------------------------------------
// Clock
#define BSP_CONFIG_CLOCK_MHZ          32

//#define HAL_BOARD_IO_SPI_MISO_PORT    0
//#define HAL_BOARD_IO_SPI_MISO_PIN     2
//#define HAL_BOARD_IO_SPI_MOSI_PORT    0
//#define HAL_BOARD_IO_SPI_MOSI_PIN     0
//#define HAL_BOARD_IO_SPI_CLK_PORT     0
//#define HAL_BOARD_IO_SPI_CLK_PIN      1
//#define HAL_BOARD_IO_SPI_CS_PORT      0
//#define HAL_BOARD_IO_SPI_CS_PIN       3


// SPI
#define HAL_BOARD_IO_SPI_MISO_PORT    0
#define HAL_BOARD_IO_SPI_MISO_PIN     6
#define HAL_BOARD_IO_SPI_MOSI_PORT    0
#define HAL_BOARD_IO_SPI_MOSI_PIN     4
#define HAL_BOARD_IO_SPI_CLK_PORT     0
#define HAL_BOARD_IO_SPI_CLK_PIN      5
#define HAL_BOARD_IO_SPI_CS_PORT      0
#define HAL_BOARD_IO_SPI_CS_PIN       7

// I2C 
#define HAL_BOARD_IO_I2C_SCL_PORT     0
#define HAL_BOARD_IO_I2C_SCL_PIN      5
#define HAL_BOARD_IO_I2C_SDA_PORT     0
#define HAL_BOARD_IO_I2C_SDA_PIN      4

// LEDs
#define HAL_BOARD_IO_LED_PORT         1 

#define HAL_BOARD_IO_LED_1_PORT       1 
#define HAL_BOARD_IO_LED_1_PIN        0
#define HAL_BOARD_IO_LED_2_PORT       1 
#define HAL_BOARD_IO_LED_2_PIN        1
#define HAL_BOARD_IO_LED_3_PORT       1 
#define HAL_BOARD_IO_LED_3_PIN        2
#define HAL_BOARD_IO_LED_4_PORT       1 
#define HAL_BOARD_IO_LED_4_PIN        3
#define HAL_BOARD_IO_LED_5_PORT       1 
#define HAL_BOARD_IO_LED_5_PIN        4
#define HAL_BOARD_IO_LED_6_PORT       1 
#define HAL_BOARD_IO_LED_6_PIN        5
#define HAL_BOARD_IO_LED_7_PORT       1 
#define HAL_BOARD_IO_LED_7_PIN        6
#define HAL_BOARD_IO_LED_8_PORT       1 
#define HAL_BOARD_IO_LED_8_PIN        7

// Buttons
#define HAL_BOARD_IO_BTN_1_PORT       2   // Button K1
#define HAL_BOARD_IO_BTN_1_PIN        3
#define HAL_BOARD_IO_BTN_2_PORT       2   // Button K2
#define HAL_BOARD_IO_BTN_2_PIN        4

// Buzzer
#define HAL_BOARD_IO_BUZZER_PORT      0 
#define HAL_BOARD_IO_BUZZER_PIN       1

// A/D
#define HAL_BOARD_IO_ADC_PORT         0
#define HAL_BOARD_IO_ADC_CH           0

// INT
#define HAL_BOARD_IO_INT_PORT         0
#define HAL_BOARD_IO_INT_PIN          0

// DO
#define HAL_BOARD_IO_DO_PORT          0
#define HAL_BOARD_IO_DO_PIN           0

// UART
#define HAL_BOARD_IO_UART_TXD_PORT    0
#define HAL_BOARD_IO_UART_TXD_PIN     3
#define HAL_BOARD_IO_UART_RXD_PORT    0
#define HAL_BOARD_IO_UART_RXD_PIN     2

// PA-2591 IO Setting
#define HAL_BOARD_PA_EN_PORT          1
#define HAL_BOARD_PA_EN_PIN           1
#define HAL_BOARD_PA_2591EN_PORT      1
#define HAL_BOARD_PA_2591EN_PIN       4
#define HAL_BOARD_PA_HGM_PORT         0
#define HAL_BOARD_PA_HGM_PIN          7

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

// PA-2591
#define HAL_PA_EN()                    MCU_IO_SET_HIGH(HAL_BOARD_PA_EN_PORT, HAL_BOARD_PA_EN_PIN)
#define HAL_PA_DIS()                   MCU_IO_SET_LOW(HAL_BOARD_PA_EN_PORT, HAL_BOARD_PA_EN_PIN)
#define HAL_2591_EN()                  MCU_IO_SET_HIGH(HAL_BOARD_PA_2591EN_PORT, HAL_BOARD_PA_2591EN_PORT)
#define HAL_2591_DIS()                 MCU_IO_SET_LOW(HAL_BOARD_PA_2591EN_PORT, HAL_BOARD_PA_2591EN_PORT)
#define HAL_PA_HGM_HI()                MCU_IO_SET_HIGH(HAL_BOARD_PA_HGM_PORT, HAL_BOARD_PA_HGM_PIN)
#define HAL_PA_HGM_LO()                MCU_IO_SET_LOW(HAL_BOARD_PA_HGM_PORT, HAL_BOARD_PA_HGM_PIN)

// Debounce
#define HAL_DEBOUNCE(expr)             { char i; for (i=0; i<50; i++) { if (!(expr)) i = 0; } }

// Assert
#define HAL_ASSERT(szErrMsg)           { halAssertHandler(szErrMsg); }

//-------------------------------------------------------------------
// GLOBAL FUNCTIONS
//-------------------------------------------------------------------
void halBoardInit(void);
void halPAInit(void);
void halAssertHandler(char *szErrMsg);
