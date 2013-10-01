#ifndef ADC_H
#define ADC_H
#include "ez8_64k.h"
#include "defines.h"
#include "interrupts.h"
#include "devices.h"


typedef unsigned char volatile far *IORegInt8;
#define IO_ADDR(addr) *((IORegInt8) addr)

// Store ADC output at RAM location 0xDE0 and onwards
/*
#define BUFFER_START 	0xDE
#define CONTINEOUS	 	0x01
#define SINGLESHOT	 	0x00
*/
//configuration parameters
//#define CONTINUOUS 1 		//comment this out if singleshot is needed
#define INTERNAL_REF 	1	//comment it out for no internal reference
#define ADC_INTERRUPTS 	3//whether to use adc interrupts comment this for polled

//flag to be monitored for data display update
extern unsigned char data_available;
//to hold contineous or single shot
//unsigned char flag;

//extern unsigned int RAM_location;
unsigned char channel = 0;
extern unsigned int far store_adc_value[12];

void isr_DMA_ADC(void);
extern void adc_config(void);
extern void config_adc_int();
//extern void config_dma_int(void);
void construct_adc(void);
void init_adc(void);
//void init_dma_adc (unsigned char conversion_type, unsigned char no_of_channels);
//void read_all_channels(unsigned char no_of_channels);
//void start_dmaadc(void);
void isr_ADC(void);
void read_adc(unsigned char channel);
void select_input(unsigned char channel);
#endif 
