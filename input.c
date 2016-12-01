#include "..//inc//tm4c123gh6pm.h"
#include <stdint.h>
#include "input.h"
#include "SysTick.h"

#define DELAY10US 800	// 10 microseconds for a 80MHz clock

// Neither pressed - 0x00
// SW1 Pressed - 0x01
// SW2 Pressed - 0x10
// Both Pressed - 0x11
int Board_Input(){
	int sw1 = (GPIO_PORTE_DATA_R & 0x10) >> 4;
	int sw2 = (GPIO_PORTE_DATA_R & 0x20) >> 1;
	return sw1+sw2;
}

// Debounce the switch inputs
// Value has to remain constant for 10ms
int Switch_Debounce(){
	int in,old,time; 
  time = 1000; // 10 ms
  old = Board_Input();
  while(time){
    //SysTick_Wait(DELAY10US); // 10us
    in = Board_Input();
    if(in == old){
      time--; // same value 
    }else{
      time = 1000;  // different
      old = in;
    }
  }
  return old;
}

//------------ADC0_InSeq0------------
// Busy-wait Analog to digital conversion
// Input: none
// Output: 12-bit result of ADC conversion
Movement ADC0_InSeq0(void){
  ADC0_PSSI_R = 0x0001;            // 1) initiate SS0
  while((ADC0_RIS_R&0x01)==0){};   // 2) wait for conversion done
    // if you have an A0-A3 revision number, you need to add an 8 usec wait here
  int x = ADC0_SSFIFO0_R&0xFFF;   // read X
	int y = ADC0_SSFIFO0_R&0xFFF;		// read Y
  ADC0_ISC_R = 0x0001;             // 4) acknowledge completion
	Movement result = {.X=x, .Y=y};
  return result;
}

// Return the current X and Y voltages
Movement Get_XY(){
	return ADC0_InSeq0();
}

int Get_SW(){
	//return Switch_Debounce();
	return Switch_Debounce();
}

// Initialize the user-input modele for the system
void Input_Init(){
	// Initialize PE4/PE5 switches, PE2/PE3 ADC
	SYSCTL_RCGCGPIO_R |= 0x10;	// Activate Port E
	SYSCTL_RCGCADC_R |= 0x01;	// Activate ADC module 0
  while((SYSCTL_PRGPIO_R&0x10) != 0x10){};
	GPIO_PORTE_DIR_R &= ~0x3C;	// PE2, PE3, PE4, PE5 input
	GPIO_PORTE_DEN_R |= 0x30;	// PE4, PE5 digital input
	GPIO_PORTE_DEN_R &= ~0x0C;	// Disable digital I/O on PE2, PE3
	GPIO_PORTE_AFSEL_R |= 0x0C;	// PE2, PE3 alternate function
	GPIO_PORTE_AMSEL_R |= 0x0C;	// PE2, PE3 analog function (ADC)
	
	// Initialize the ADC Sample Sequencer 0
	ADC0_ACTSS_R &= ~0x01;	// Disable SS0
	ADC0_EMUX_R &= ~0x000F;         // seq0 is software trigger
	ADC0_SSMUX0_R &= ~0x00FF;       // clear first and second sample field
  ADC0_SSMUX0_R |= 0x0010;             // set channel (PE3 first sample, PE2 second sample)
	ADC0_SSCTL0_R &= ~0x00FF;	// Clear the first two samples
	ADC0_SSCTL0_R |= 0x60;	// Second sample is the last sample
	ADC0_ACTSS_R |= 0x01;	// Enable SS3
}
