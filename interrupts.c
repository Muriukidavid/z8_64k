#include "interrupts.h"
#include "defines.h"
#include "devices.h"

void construct_interrupts(void){
	interrupt_c = (INTERRUPT_CONTROLLER)interrupts;
}
void init_interrupts(void){
	//interrupt_c->irq0enh.u0renh=ON;
	#ifdef UART_R_INTERRUPTS
	if(UART_R_INTERRUPTS==3){
		interrupt_c->irq0enh.u0renh=ON;//UART receive high priority interrups 
		interrupt_c->irq0enl.u0renl=ON;
	}else if(UART_R_INTERRUPTS==2){
		interrupt_c->irq0enh.u0renh=ON;//UART receive nominal priority interrups 
		interrupt_c->irq0enl.u0renl=OFF;
	}else{
		interrupt_c->irq0enh.u0renh=OFF;//UART receive low priority interrups 
		interrupt_c->irq0enl.u0renl=ON;
		}
	#endif 
	#ifdef UART_T_INTERRUPTS
	if(UART_T_INTERRUPTS==3){
		interrupt_c->irq0enh.u0tenh=ON;//UART transmit high priority interrups 
		interrupt_c->irq0enl.u0tenl=ON;
	}else if(UART_T_INTERRUPTS==2){
		interrupt_c->irq0enh.u0tenh=ON;//UART transmit nominal priority interrups 
		interrupt_c->irq0enl.u0tenl=OFF;
	}else{
		interrupt_c->irq0enh.u0tenh=OFF;//UART transmit low priority interrups 
		interrupt_c->irq0enl.u0tenl=ON;
		}	
	#endif
	//adc interrupts
	#ifdef ADC_INTERRUPTS
		if(ADC_INTERRUPTS==3){
		interrupt_c->irq0enh.adcenh=ON;
		interrupt_c->irq0enl.adcenl=ON;
		}else if(ADC_INTERRUPTS==2){
			interrupt_c->irq0enh.adcenh=ON;
			interrupt_c->irq0enl.adcenl=OFF;
			}else{
				interrupt_c->irq0enh.adcenh=OFF;
				interrupt_c->irq0enl.adcenl=ON;
				}
	#endif
}
//global interrupt functions
void EI(void){
	asm("\t ei");
}
void DI(void){
	asm("\t di");
}
#ifdef UART_R_INTERRUPTS
#pragma interrupt // interupt service routine for receive 
void  ISR_Receive(void) {  
    receive();
}
#endif

#ifdef UART_T_INTERRUPTS
#pragma interrupt // interupt service routine for transmit 
void  ISR_Transmit(void) {  
    ;
}
#endif

#ifdef ADC_INTERRUPTS
#pragma interrupt//interrupt service routine for adc conversion
void isr_ADC(void){
	VInHigh=ez8.adc->datah.byte_reg;
	VInLow=ez8.adc->datal.byte_reg;
	data_available=1;
}
#endif
