#include "interrupts.h"
#include "defines.h"
#include "devices.h"

void construct_interrupts(void){
	interrupt_c = (INTERRUPT_CONTROLLER)interrupts;
}

void config_adc_int(void){ 
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

void config_uart_int(char devnum){
	switch(devnum){
		case 0:
			#ifdef UART0_R_INTERRUPTS
			if(UART0_R_INTERRUPTS==3){
				interrupt_c->irq0enh.u0renh=ON;//UART receive high priority interrups 
				interrupt_c->irq0enl.u0renl=ON;
			}else if(UART0_R_INTERRUPTS==2){
				interrupt_c->irq0enh.u0renh=ON;//UART receive nominal priority interrups 
				interrupt_c->irq0enl.u0renl=OFF;
			}else if(UART0_R_INTERRUPTS==1){
				interrupt_c->irq0enh.u0renh=OFF;//UART receive low priority interrups 
				interrupt_c->irq0enl.u0renl=ON;
				}
			#else //incase any other number given
				interrupt_c->irq0enh.u0renh=OFF;//UART receive interrups off
				interrupt_c->irq0enl.u0renl=OFF;
			#endif
			#ifdef UART0_T_INTERRUPTS
			if(UART0_T_INTERRUPTS==3){
				interrupt_c->irq0enh.u0tenh=ON;//UART transmit high priority interrups 
				interrupt_c->irq0enl.u0tenl=ON;
			}else if(UART0_T_INTERRUPTS==2){
				interrupt_c->irq0enh.u0tenh=ON;//UART transmit nominal priority interrups 
				interrupt_c->irq0enl.u0tenl=OFF;
			}else if(UART0_T_INTERRUPTS==1){
				interrupt_c->irq0enh.u0tenh=OFF;//UART transmit low priority interrups 
				interrupt_c->irq0enl.u0tenl=ON;
				}		
			#else
				interrupt_c->irq0enh.u0tenh=OFF;//UART transmit interrups off
				interrupt_c->irq0enl.u0tenl=OFF;
			#endif
		break;
		case 1:
			#ifdef UART1_R_INTERRUPTS
			if(UART1_R_INTERRUPTS==3){
				interrupt_c->irq2enh.u1renh=ON;//UART receive high priority interrups 
				interrupt_c->irq2enl.u1renl=ON;
			}else if(UART1_R_INTERRUPTS==2){
				interrupt_c->irq2enh.u1renh=ON;//UART receive nominal priority interrups 
				interrupt_c->irq2enl.u1renl=OFF;
			}else if(UART1_R_INTERRUPTS==1){
				interrupt_c->irq2enh.u1renh=OFF;//UART receive low priority interrups 
				interrupt_c->irq2enl.u1renl=ON;
				}
			#else
				interrupt_c->irq2enh.u1renh=OFF;//UART receive interrups off 
				interrupt_c->irq2enl.u1renl=OFF;
			#endif
			#ifdef UART1_T_INTERRUPTS
			if(UART1_T_INTERRUPTS==3){
				interrupt_c->irq2enh.u1tenh=ON;//UART transmit high priority interrups 
				interrupt_c->irq2enl.u1tenl=ON;
			}else if(UART0_T_INTERRUPTS==2){
				interrupt_c->irq2enh.u1tenh=ON;//UART transmit nominal priority interrups 
				interrupt_c->irq2enl.u1tenl=OFF;
			}else{
				interrupt_c->irq2enh.u1tenh=OFF;//UART transmit low priority interrups 
				interrupt_c->irq2enl.u1tenl=ON;
				}	
				
			#else
				interrupt_c->irq2enh.u1tenh=OFF;//UART transmit interrups off
				interrupt_c->irq2enl.u1tenl=OFF;
			#endif
		break;
	}
	
}

/*
void config_dma_int(void){
	interrupt_c->irq2enh.dmaenh = ON;//Set the DMA_ADC interrupt priority to highest
	interrupt_c->irq2enl.dmaenl = ON;
}
*/


//clear all interrupts
void clearall_interrupts(void){	
	//interrupt_c->irq0.byte_reg=0x00;
	//interrupt_c->irq1.byte_reg=0x00;
	interrupt_c->irq2e.irqtwo.byte_reg=0x00;
}

void clear_recieve_int(char devnum){
	switch(devnum){
		case 0:
			interrupt_c->irq0.u0rxi=OFF;
		break;
		case 1:
			interrupt_c->irq2e.irq2.u1rxi=OFF;
		break;
	}
	
}

