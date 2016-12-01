#include "..//inc//tm4c123gh6pm.h"
#include <stdint.h>

#define delay 30	// Wait for 30 frames before toggling

int reset;
int count;

// Decrement the count, when it hits 0 then toggle
void Toggle_Heartbeat(){
	count -= 1;
	if(count == 0){
		count = reset;
		// Toggle PF0
		if((GPIO_PORTF_DATA_R&0x01) == 0x01) GPIO_PORTF_DATA_R &= ~0x01;
		else GPIO_PORTF_DATA_R |= 0x01;
	}
}

// Initialize port F as the heartbeat
void Heartbeat_Init(int FPS){
	SYSCTL_RCGCGPIO_R |= 0x20;	// Activate port F
	while((SYSCTL_RCGCGPIO_R & 0x20) != 0x20);	// Wait to activate
	GPIO_PORTF_LOCK_R = 0x4C4F434B;   // 2) unlock GPIO Port F
	GPIO_PORTF_CR_R = 0x1F;           // allow changes to PF4-0
	GPIO_PORTF_DIR_R |= 0x01;	// PF0 as output
	GPIO_PORTF_DEN_R |= 0x01;	// Digital I/O on PF0
	GPIO_PORTF_AMSEL_R = 0;   // Disable analog functionality on PF0
	GPIO_PORTF_AFSEL_R &= ~0x01;	// Disable alternate function on PF0
	GPIO_PORTF_DATA_R &= ~0x01;	// Turn off LED
	
	reset = FPS;	// Reload value for count
	count = reset;
}
