#ifndef interrupt_h
#define interrupt_h

#include "ez8_64k.h"
#include "devices.h"
#include "adc.h"
#include "uart.h"
//interrupt vectors
//#define interrupt_vector (int*) 0x00
//interrupt vectors
#define  RESET     	0
#define  WDT       	1
#define  TRAP      	2
#define  TIMER2    	3
#define  TIMER1    	4
#define  TIMER0    	5

#define  uart0_rx  	6 // divide the int address by 2 then -1 e.g for ISR_Receive (uart0_rx) = 0x0E=14/2=7-1=6
#define  uart0_tx  	7
#define  I2C       	8
#define  SPI       	9
#define  adc_vec   	10 
#define  P7AD      	11
#define  P6AD      	12
#define  P5AD      	13
#define  P4AD      	14
#define  P3AD      	15
#define  P2AD      	16
#define  P1AD      	17
#define  P0AD      	18
#define TIMER3		19

#define  uart1_rx  	20 
#define  uart1_tx  	21

#define dma_int		22

#define	 C3         23
#define  C2         24
#define  C1         25
#define  C0         26

#define  POTRAP     28
#define  WOTRAP     29

void construct_interrupts(void);
void clearall_interrupts(void);
void clear_recieve_int(char devnum);
void config_uart_int(char devnum);
void config_adc_int(void);
void config_dma_int(void);

//global interrupt functions
intrinsic void EI(void);
intrinsic void DI(void);


extern void receive(char devnum);
//extern void read_adc(void);
#endif 
