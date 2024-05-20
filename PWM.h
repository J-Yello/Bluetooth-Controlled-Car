/////////////////////////////////////////////////////////////////////////////
// Course Number: CECS 347
// Assignment: Example project for Hardware PWM controlled Car
// Description: 
/////////////////////////////////////////////////////////////////////////////

// Constant definitions based on the following hardware interface:
// System clock is 16MHz.
#define TOTAL_PERIOD 40000 //  16MHz/1000=16000
#define START_SPEED 16000*0.25
#define SPEED2 10000
#define SPEED3 12000
#define SPEED4 14000
#define SPEED5 15999

// defines the max range for the arm/gripper at 16MHz
#define ArmUpMAx 


// PB5432 are used for direction control on L298.
// Motor 1 is connected to the left wheel, Motor 2 is connected to the right wheel.

//////////////////////1. Declarations Section////////////////////////////////
////////// Function Prototypes //////////
// Dependency: None
// Inputs: None
// Outputs: None
// Description: 
//	Initializes the PWM module 1 signals tied to PF321 on the Tiva Launchpad 
//		to allow for changing brightness of LEDs based on vehicle speed.
//	Initializes the PWM module 0 signals tied to PB76 to be used with the 
//		L298N motor driver allowing for a variable speed of robot car.
void PWM_PB76_Init(void);

// Dependency: PWM_PB76_Init()
// Inputs: 
//	duty_L is the value corresponding to the duty cycle of the left wheel
//	duty_R is the value corresponding to the duty cycle of the right wheel
// Outputs: None 
// Description: Changes the duty cycles of PB76 by changing the CMP registers
void PWM_PB76_Duty(unsigned long duty_L, unsigned long duty_R);
/////////////////////////////////////////////////////////////////////////////

// Initialize Port A 6-7 to be used for PWM signal for arm
void PWM_PA76_Init(void);

// Changes the duty cycle for PA 6 which is used to controll the up and dowm motion of arm 
void PWM_PA6_Duty(unsigned long duty_arm);

// Changes the duty cycle for PA 7 whcih is used to controll the piviot of the arm
void PWM_PA7_Duty(unsigned long duty_pivot);

// Initialize Port D0 to be a PWM singal for claw 
void PWM_PD0_Init(void);

// Changes the duty cycle for PD 0 which controlls the claw
void PWM_PD0_Duty(unsigned long duty_claw);

