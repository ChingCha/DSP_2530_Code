//-------------------------------------------------------------------
// Filename: M100.h
// Description: RTC library header file
//-------------------------------------------------------------------

//-------------------------------------------------------------------
// GLOBAL FUNCTIONS
//-------------------------------------------------------------------
extern uint16 Year;
extern uint8 Month, Day, Hour, Min, Sec;

void RTC_Init(void);
void SetDateTime(void);
void GetDateTime(void);
