/////////////////////////////////////////////////////////////////////////////
// Course Number: CECS 347
// Assignment: Example project for Hardware PWM controlled Car
// Description: 
/////////////////////////////////////////////////////////////////////////////

//////////////////////1. Pre-processor Directives Section////////////////////
#include "tm4c123gh6pm.h"
#include "PWM.h"
#include "GPIO.h"
#include "BTControl.h"
#include "UART.h"
/////////////////////////////////////////////////////////////////////////////

//////////////////////2. Declarations Section////////////////////////////////

////////// Local Global Variables //////////

////////// Function Prototypes //////////
void DisableInterrupts(void);
void EnableInterrupts(void);
void WaitForInterrupt(void);
void Delay(void);

//////////////////////3. Subroutines Section/////////////////////////////////
// MAIN: This main is meant for the command configuration of the hc05.
int main(void){ 
  LED_Init();
  Car_Dir_Init();
  PWM_PB76_Init();
	UART_Init();
  PWM_PB76_Duty(START_SPEED, START_SPEED);

	char BT_input;

  while(1){
		BT_input = UART1_InChar();
		switch(BT_input){
			case('w'):
				MoveForward();
				break;
			case('a'):
				LeftTurn();
				break;
			case('s'):
				MoveBackward();
				break;
			case('d'):
				RightTurn();
				break;
			case('q'):
				SlowDown();
				break;
			case('e'):
				SpeedUp();
				break;
			case(SP):
				StopMoving();
				break;
			default: break;
		}
	}
}

// Subroutine to wait 0.25 sec
// Inputs: None
// Outputs: None
// Notes: ...
void Delay(void){
	unsigned long volatile time;
  time = 727240*500/91;  // 0.25sec
  while(time){
		time--;
  }
}
