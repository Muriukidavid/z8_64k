#ifndef buttons
#define buttons

#include "gpio.h"
#include "interrupts.h"
#define BTN_INTERRUPTS
#define BTN0
#define BTN1
#define BTN2
#define BTN3

void btn0_pressed(void){
	;
}
void btn1_pressed(void){
	;
}
void btn2_pressed(void){
	;
}
void btn3_pressed(void){
	;
}

//button interrupts
#pragma interrupt // interupt service routine for receive 
void  ISR_btn0(void) {  
    btn0_pressed();
}

#pragma interrupt // interupt service routine for receive 
void  ISR_btn1(void) {  
    btn1_pressed();
}

#pragma interrupt // interupt service routine for receive 
void  ISR_btn2(void) {  
    btn2_pressed();
}

#pragma interrupt // interupt service routine for receive 
void  ISR_btn3(void) {  
    btn3_pressed();
}

#endif 