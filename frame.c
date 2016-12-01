#include "../inc/tm4c123gh6pm.h"
#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"
#include "heartbeat.h"
#include "input.h"
#include "ST7735.h"
#include "sound.h"
#include "SysTick.h"
#include <stdint.h>

void (*PeriodicTask)(void);   // user function

// ***************** Timer3_Init ****************
// Activate Timer3 interrupts to run user task periodically
// Inputs:  task is a pointer to a user function
//          period in units (1/clockfreq)
// Outputs: none
void Timer3_Init(void(*task)(void), unsigned long period){
  SYSCTL_RCGCTIMER_R |= 0x08;   // 0) activate TIMER3
  PeriodicTask = task;          // user function
  TIMER3_CTL_R = 0x00000000;    // 1) disable TIMER3A during setup
  TIMER3_CFG_R = 0x00000000;    // 2) configure for 32-bit mode
  TIMER3_TAMR_R = 0x00000002;   // 3) configure for periodic mode, default down-count settings
  TIMER3_TAILR_R = period-1;    // 4) reload value
  TIMER3_TAPR_R = 0;            // 5) bus clock resolution
  TIMER3_ICR_R = 0x00000001;    // 6) clear TIMER3A timeout flag
  TIMER3_IMR_R = 0x00000001;    // 7) arm timeout interrupt
  NVIC_PRI8_R = (NVIC_PRI8_R&0x00FFFFFF)|0x80000000; // 8) priority 4
// interrupts enabled in the main program after all devices initialized
// vector number 51, interrupt number 35
  NVIC_EN1_R = 1<<(35-32);      // 9) enable IRQ 35 in NVIC
  TIMER3_CTL_R = 0x00000001;    // 10) enable TIMER3A
}

void Timer3A_Handler(void){
  TIMER3_ICR_R = TIMER_ICR_TATOCINT;// acknowledge TIMER3A timeout
  (*PeriodicTask)();                // execute user task
}

// Frame of the game
static int times[100];
static int differences[100];
static int count = 0;
void Frame_Task(void){
	// Get the user input
	Movement m = Get_XY();
	int sw = Get_SW();
	Input input = {.x=m.X, .y=m.Y, .b=((sw&0x10) >> 1), .a=(sw&0x01)};
	
	// Send the user input to the World(logic) module
	Frame frame = Next_Frame(input);
	
	// Play the sounds that the World module says to play
	Set_Sound_Effect(frame.sound);
	
	// Display the image that the World module returns
	drawFrame(160, 128, frame.pixels);
	
	if(count < 100){
		times[count] = NVIC_ST_CURRENT_R & 0xFFFFFF;
		count += 1;
	}else{
		for(int i = 0; i < count; i++){
			if(i < 99) differences[i] = (times[i+1] - times[i]);
		}
		int x = 5;
		x = 6;
	}
	
	// Heartbeat
	//Toggle_Heartbeat();
	
}

void Frame_Init(int FPS){
		Timer3_Init(&Frame_Task, 80000000/FPS);
}
