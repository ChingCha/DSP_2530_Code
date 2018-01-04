//-------------------------------------------------------------------
// Filename: M430.h
// Description: hal M430 module library header file
//-------------------------------------------------------------------

extern uint16 M430_Count;

//-------------------------------------------------------------------
// GLOBAL FUNCTIONS
//-------------------------------------------------------------------
void M430_Init(void); /* Initilization the M430 Module */
uint16 M430_GetValue(void); /* Get the M430 Module ADC value */

void TIMER4_Init(void); /* Initilization the Timer 4 */
void TIMER4_On(void); /* Turn on the Timer 4 */
void TIMER4_Off(void); /* Turn off the Timer4 */

