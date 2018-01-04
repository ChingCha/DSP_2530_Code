//-------------------------------------------------------------------
// Filename: M440.h
// Description: hal M440 module library header file
//-------------------------------------------------------------------

//-------------------------------------------------------------------
// GLOBAL VARIABLE
//-------------------------------------------------------------------
/* The MI-Sensor data */
extern uint16 M440_X_AXIS_Value;
extern uint16 M440_Y_AXIS_Value;
extern uint16 M440_Z_AXIS_Value;

/* The Device Information */
extern uint16 M440_Ver;
extern uint16 M440_Ser;
extern uint8 M440_Dev;

//-------------------------------------------------------------------
// GLOBAL FUNCTIONS
//-------------------------------------------------------------------
void M440_Init(void); /* Initilization M440 Module */
void M440_Pooling(void); /* Get M440 Module Digital/Analog */
void M440_Version(void); /* Get M440 Module Version and Info */
void M440_WriteReg(uint8 addr,uint8 ch); /* Write Register */
uint8 M440_RedReg(uint8 addr); /* Read Register */
uint16 M440_ReadRegWord(uint8 addr);
void M440_Offset(void);

//-------------------------------------------------------------------
//Register names and address
//-------------------------------------------------------------------
#define AMI304_INFO_0            0x0D /* Information LSB */
#define AMI304_INFO_1            0x0E /* Information MSB */
#define AMI304_DEVICE            0x0F /* Device ID(who am I) */
#define AMI304_INS               0x16 /* Interrupt source 1 */ 
#define AMI304_STATE             0x18 /* Status 1 */
#define AMI304_INL               0x1A /* Interrupt release */
#define AMI304_INC               0x1E /* Interrupt control 1 */ 
#define AMI304_ITHER_0           0x26 /* Interrupt threshold LSB */ 
#define AMI304_ITHER_1           0x27 /* Interrupt threshold MSB */
#define AMI304_PRET              0x30 /* Preset time */ 
#define AMI304_TEMP              0x60 /* Temperature value */ 
#define AMI304_VER_0             0xE8 /* Firmware version LSB */
#define AMI304_VER_1             0xE9 /* Firmware version MSB */
#define AMI304_SN_0              0xEA /* Serial number LSB */
#define AMI304_SN_1              0xEB /* Serial number MSB */
#define AMI304_DATAX_0           0x10 /* X-axis output value LSB */ 
#define AMI304_DATAX_1           0x11 /* X-axis output value MSB */
#define AMI304_DATAY_0           0x12 /* Y-axis output value LSB */
#define AMI304_DATAY_1           0x13 /* Y-axis output value MSB */
#define AMI304_DATAZ_0           0x14 /* Z-axis output value LSB */
#define AMI304_DATAZ_1           0x15 /* Z-axis output value MSB */
#define AMI304_CNTL1             0x1B /* Control setting 1 */ 
#define AMI304_CNTL2             0x1C /* Control setting 2 */
#define AMI304_CNTL3             0x1D /* Control setting 3 */
#define AMI304_CNTL4_0           0x5C /* Control setting 4 LSB */
#define AMI304_CNTL4_1           0x5D /* Control setting 4 MSB */
#define AMI304_B0X_0             0x20 /* B0 X value LSB */
#define AMI304_B0X_1             0x21 /* B0 X value MSB */
#define AMI304_B0Y_0             0x22 /* B0 Y value LSB */
#define AMI304_B0Y_1             0x23 /* B0 Y value MSB */
#define AMI304_B0Z_0             0x24 /* B0 Z value LSB */
#define AMI304_B0Z_1             0x25 /* B0 Z value MSB */
#define AMI304_DELAYX            0x68 /* Delay X value */
#define AMI304_DELAYY            0x6E /* Delay Y value */
#define AMI304_DELAYZ            0x74 /* Delay Z value */
#define AMI304_OFFX_0            0x6C /* Offset X value LSB */
#define AMI304_OFFX_1            0x6D /* Offset X value MSB */
#define AMI304_OFFY_0            0x72 /* Offset Y value LSB */
#define AMI304_OFFY_1            0x73 /* Offset Y value MSB */
#define AMI304_OFFZ_0            0x78 /* Offset Z value LSB */
#define AMI304_OFFZ_1            0x79 /* Offset Z value MSB */

