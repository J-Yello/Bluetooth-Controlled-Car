#include "BTControl.h"
#include "GPIO.h"
#include "PWM.h"
#include "tm4c123gh6pm.h"

const int PWMSpeed [5] = {START_SPEED, SPEED2, SPEED3, SPEED4, SPEED5};
unsigned char throttle = 0;

void MoveForward(void){
	LED = Green;
	WHEEL_DIR = FORWARD;
	PWM0_ENABLE_R |= 0x00000003; // enable both wheels
}
void MoveBackward(void){
	LED = Blue;
	WHEEL_DIR = BACKWARD;
	PWM0_ENABLE_R |= 0x00000003; // enable both wheels
}
void LeftTurn(void){
	LED = Yellow;
	//WHEEL_DIR=FORWARD;
	PWM0_ENABLE_R &= ~0x00000002; // Disable right wheel
	PWM0_ENABLE_R |= 0x00000001; // Enable left wheel
}
void RightTurn(void){
	LED = Purple;
	//WHEEL_DIR=FORWARD;
	PWM0_ENABLE_R |= 0x00000002; // Enable right wheel
	PWM0_ENABLE_R &= ~0x00000001; // Disable left wheel
}
void StopMoving(void){
	LED = Dark;
	PWM0_ENABLE_R &= ~0x00000003; // stop both wheels
}
void SpeedUp(void){
	if(throttle < 4) throttle += 1;
	PWM_PB76_Duty(PWMSpeed[throttle], PWMSpeed[throttle]);
}
void SlowDown(void){
	if(throttle > 0) throttle -= 1;
	PWM_PB76_Duty(PWMSpeed[throttle], PWMSpeed[throttle]);
}
