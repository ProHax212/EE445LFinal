// SysTickTestMain.c
// Runs on LM4F120/TM4C123
// Test the SysTick functions by activating the PLL, initializing the
// SysTick timer, and flashing an LED at a constant rate.
// Daniel Valvano
// September 12, 2013

/* This example accompanies the books
   "Embedded Systems: Introduction to ARM Cortex M Microcontrollers",
   ISBN: 978-1469998749, Jonathan Valvano, copyright (c) 2015
   Volume 1, Program 4.7

   "Embedded Systems: Real Time Interfacing to Arm Cortex M Microcontrollers",
   ISBN: 978-1463590154, Jonathan Valvano, copyright (c) 2015
   Program 2.11, Section 2.6

 Copyright 2015 by Jonathan W. Valvano, valvano@mail.utexas.edu
    You may use, edit, run or distribute this file
    as long as the above copyright notice remains
 THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 VALVANO SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 For more information about my classes, my research, and my books, see
 http://users.ece.utexas.edu/~valvano/
 */

// PF2 is an output for debugging
#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"

#include "SysTick.h"
#include "PLL.h"
#include "input.h"
#include "sound.h"
#include "heartbeat.h"
#include "ST7735.h"
#include "frame.h"

#define FPS 30

bool resetGame = false;

void resetAll(void){
	Init_Game();
	Heartbeat_Init(FPS);
	Sound_Init();
	ST7735_InitR(INITR_REDTAB);
	Frame_Init(FPS);
	SysTick_Init(FPS);
}

int main(void){
  PLL_Init(Bus80MHz);         // set system clock to 80 MHz
	Input_Init();
	resetAll();
	int i = 0;
	while(!resetGame){
		i++;
	}
}
