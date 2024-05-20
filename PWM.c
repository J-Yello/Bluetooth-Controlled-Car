/////////////////////////////////////////////////////////////////////////////
// Course Number: CECS 347
// Assignment: Example project for Hardware PWM controlled Car
// Description: 
/////////////////////////////////////////////////////////////////////////////

//////////////////////1. Pre-processor Directives Section////////////////////
#include "tm4c123gh6pm.h"
#include "PWM.h"

////////// Local Global Variables //////////
/////////////////////////////////////////////////////////////////////////////

//////////////////////3. Subroutines Section/////////////////////////////////
// Dependency: None
// Inputs: None
// Outputs: None
// Description: 
// Initializes the PWM module 0 generator 0 outputs A&B tied to PB76 to be used with the 
//		L298N motor driver allowing for a variable speed of robot car.
void PWM_PB76_Init(void){
	if ((SYSCTL_RCGC2_R&SYSCTL_RCGC2_GPIOB)==0) {
		SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOB;	// Activate B clocks
		while ((SYSCTL_RCGC2_R&SYSCTL_RCGC2_GPIOB)==0){};
	}
	
	GPIO_PORTB_AFSEL_R |= 0xC0;	// enable alt funct: PB76 for PWM
  GPIO_PORTB_PCTL_R &= ~0xFF000000; // PWM to be used
  GPIO_PORTB_PCTL_R |= 0x44000000; // PWM to be used
  GPIO_PORTB_DEN_R |= 0xC0;	// enable digital I/O 
	
	// Initializes PWM settings
	SYSCTL_RCGCPWM_R |= 0x01;	// activate PWM0
	SYSCTL_RCC_R &= ~0x001E0000; // Clear any previous PWM divider values
	
	// PWM0_0 output A&B Initialization for PB76
	PWM0_0_CTL_R = 0;	// re-loading down-counting mode
	PWM0_0_GENA_R |= 0xC8;	// low on LOAD, high on CMPA down
	PWM0_0_GENB_R |= 0xC08;// low on LOAD, high on CMPB down
	PWM0_0_LOAD_R = TOTAL_PERIOD - 1;	// cycles needed to count down to 0
  PWM0_0_CMPA_R = 0;	// count value when output rises
	PWM0_0_CMPB_R = 0;	// count value when output rises
	
	PWM0_0_CTL_R |= 0x00000001;	// Enable PWM0 Generator 0 in Countdown mode
	PWM0_ENABLE_R &= ~0x00000003;	// Disable PB76:PWM0 output 0&1 on initialization
}


// Dependency: PWM_Init()
// Inputs: 
//	duty_L is the value corresponding to the duty cycle of the left wheel
//	duty_R is the value corresponding to the duty cycle of the right wheel
// Outputs: None 
// Description: Changes the duty cycles of PB76 by changing the CMP registers
void PWM_PB76_Duty(unsigned long duty_L, unsigned long duty_R){
	PWM0_0_CMPA_R = duty_L - 1;	// PB6 count value when output rises
  PWM0_0_CMPB_R = duty_R - 1;	// PB7 count value when output rises
}
/////////////////////////////////////////////////////////////////////////////
// Initialize Port A 6-7 to be used for PWM signal for arm
void PWM_PA76_Init(void){
	// activate port A clock
	SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOA;
	// waits for the clock to be active 
	while ((SYSCTL_RCGC2_R&SYSCTL_RCGC2_GPIOA)==0){}; 
	// enable alt functions for PA 6-7
	GPIO_PORTA_AFSEL_R |= 0xC0;
	// Clear the PCTL for PA 6-7
	GPIO_PORTA_PCTL_R &= ~0xFF000000;
	// sets PCTL for PA 6-7 to use PWM
	GPIO_PORTA_PCTL_R |= 0x55000000;
	// enable digital output for PA 6-7
	GPIO_PORTA_DEN_R |= 0xC0; 
		
	// Initialize PWM Settings
	// enables PWM Module 1
	SYSCTL_RCGCPWM_R |= 0x02;
	// Clear any previous PWM divider values
	SYSCTL_RCC_R &= ~0x001E0000; 
		
	// Set up PWM module 1 G2-3 for use
	PWM1_1_GENA_R |= 0xC8;
	PWM1_1_GENB_R |= 0xC08;
	PWM1_1_LOAD_R = TOTAL_PERIOD - 1;
	PWM1_1_CMPA_R = 0;
	PWM1_1_CMPB_R = 0;
	// Enables PWM 1 Gen 1 in cound down mode
	PWM1_1_CTL_R |= 0x00000001;
	// Enable PA6 M1PWM2, PA7 M1PWM3
	PWM1_ENABLE_R |= 0x0000000C;
}

// Changes the duty cycle for PA 6 which is used to controll the up and dowm motion of arm 
void PWM_PA6_Duty(unsigned long duty_arm){
	// PA6 count value when output rises
	PWM1_1_CMPA_R = duty_arm - 1;	
}

// Changes the duty cycle for PA 7 whcih is used to controll the piviot of the arm
void PWM_PA7_Duty(unsigned long duty_pivot){
	// PA7 count value when output rises
	PWM1_1_CMPB_R = duty_pivot - 1;
}

// Initialize Port D0 to be a PWM singal for gripper
void PWM_PD0_Init(void){
	// enables Clock for port D
	SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOD;
	// waits for clock to be active
	while ((SYSCTL_RCGC2_R & SYSCTL_RCGC2_GPIOD)==0){
	}; 
	// enable alt function for PD0
	GPIO_PORTD_AFSEL_R |= 0x01;
	// clear control for PD0
	GPIO_PORTD_PCTL_R &= ~0x0000000F;
	// sets PD0 to use PWM M1G0
	GPIO_PORTD_PCTL_R |= 0x00000005;
	// enables digital output for PD0
	GPIO_PORTD_DEN_R |= 0x01;
	
	// Initialize PWM Settings
	// enables PWM Module 1
	SYSCTL_RCGCPWM_R |= 0x02;
	// Clear any previous PWM divider values
	SYSCTL_RCC_R &= ~0x001E0000; 
	
			
	// Set up PWM module 1 G0 for use
	PWM1_0_GENA_R |= 0xC8;
	PWM1_0_LOAD_R = TOTAL_PERIOD - 1;
	PWM1_0_CMPA_R = 0;
	// Enables PWM 1 Gen 0 in cound down mode
	PWM1_0_CTL_R |= 0x00000001;
	PWM1_ENABLE_R |= 0x00000001;
	
}

// Changes the duty cycle for PD 0 which controlls the claw
void PWM_PD0_Duty(unsigned long duty_claw){
	PWM1_0_CMPA_R = duty_claw - 1; 
}