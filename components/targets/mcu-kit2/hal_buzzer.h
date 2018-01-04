//-------------------------------------------------------------------
// Filename: hal_buzzer.h
// Description: hal buzzer library header file
//-------------------------------------------------------------------
#define BUZZER_FREQ		2730 
//-------------------------------------------------------------------
// GLOBAL FUNCTIONS
//-------------------------------------------------------------------
void halBuzzerInit(uint16 freq);
void halBuzzerOn(uint16 freq);
void halBuzzerOff(void);
void halBuzzer(uint16 ms);
