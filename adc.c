#include "adc.h"

void construct_adc(void){
	adc0=(ADC)adc;
	//dmaadc = (DMA_ADC)dma_adc;
}

void init_adc(void){
	//enable adc gpio input pins
	adc_config();
	config_adc_int();
	SET_VECTOR(adc_vec,isr_ADC);
	//set vref to 0 select internal reference
	#ifdef INTERNAL_REF
		adc0->control.vref=0;
	#endif
	#ifdef EXTERNAL_REF
		adc0->control.vref=1;
	#endif
	//Continuous Conversion
	#ifndef CONTINUOUS
		adc0->control.cont = OFF;
	#else
		adc0->control.cont = ON;
	#endif
	adc0->control.cen=ON;
}

void read_adc(unsigned char channel){
	unsigned int VInHigh=0, VInLow=0, ADC_data=0;
	double ADC_read=0;
	/*#ifndef ADC_INTERRUPTS //blocking polled adc read
	adc0->control.cen=ON;
	while(adc0->control.cen==1){
		asm("nop");
		}
	VInHigh=adc0->datah.byte_reg; //all high byte first 8 bits msbs
	VInLow=adc0->datal.byte_reg;  //2-bits
		
	VInLow = VInLow >> 6;
	VInLow &=0x03;
		
	VInHigh = VInHigh << 2;
		
	ADC_data = (VInHigh| VInLow); //ADC output word
	
	#else
*/	//non-blocking wait for interrupts
		//if(data_available){//check if from ISR
	VInHigh=(adc0->datah.byte_reg)&0x00ff;
	VInLow=(adc0->datal.byte_reg)&0x00ff;
	VInLow = VInLow >> 6;
	VInLow &=0x03;
		
	VInHigh = VInHigh << 2;	
	ADC_data = (VInHigh| VInLow); //ADC output word
		//}
	//#endif
	store_adc_value[channel] = ADC_data;	
}


void select_input(unsigned char channel){
	adc0->control.anain = channel; 
}


#pragma interrupt
void isr_ADC(void){
	DI();
	read_adc(channel);
	channel++;
	if (channel>11)
		channel=0;
	EI();
select_input(channel);
adc0->control.cen=ON;	
}
	
	
/*
void init_dma_adc (unsigned char conversion_type, unsigned char no_of_channels){
	if(conversion_type==1)
		flag=CONTINEOUS;
		else
		flag=SINGLESHOT;// 1 for Continuous conversion.Set flag=1;
						//0 for one shot conversion.Set flag =0;
		dmaadc->addr.byte_reg = BUFFER_START;//Load the Ram location to the DMA ADDRESS register
		config_dma_int();
		dmaadc->control.irqen=ON;
		dmaadc->control.adcin = no_of_channels;  // Load the maximum channel number, up to which the conversion is required.
}

void start_dmaadc(void){
	// Pass the vector number and the ISR address to be placed into the interrupt table
	SET_VECTOR(dma_int,isr_DMA_ADC);
	//enable dmaadc and set interrupts enabled bit
	dmaadc->control.daen=ON;
	dmaadc->control.irqen=ON;
}


#pragma interrupt
void isr_DMA_ADC(void)
{
	//disable interrupts globally
	DI();
	//Stop conversion and disable the interrupt request.
	dmaadc->control.daen=OFF;	// equ to (DACLT &= 0x0F)
	dmaadc->control.irqen=OFF;
	//check if interrupt was due to dmaadc
	if(dmaadc->status.irqa){
		data_ready=0x01;
		if(flag== SINGLESHOT){
			// Disable DMA_ADC.if the type of conversion one shot.
			dmaadc->control.daen=OFF;	
			dmaadc->control.irqen=OFF;
		}
		else if(flag== CONTINEOUS) {
		// Keep the interrupt continuously enabled.
		//read_all_channels(4);
		dmaadc->control.irqen=ON;
		}
	}
	//enable global interrupts
	EI();
}

void read_all_channels(unsigned char no_of_channels){
	unsigned char count;
	int ADCvalue_temp, valueH, valueL;
	RAM_location = BUFFER_START;//base address of RAM location
	RAM_location = (RAM_location << 4) & 0xff0;//convert to required format
	for ( count=0; count <= no_of_channels; count++){//loop through the channels
		valueH = IO_ADDR (RAM_location + 2*count);// Get ADC Data High from memory
		valueH &= 0x0ff;
		valueH = valueH << 2;//shift left 2 bits
		valueL = IO_ADDR (RAM_location + 2*count+ 1);// Get ADC Data Low from memory
		valueL = valueL >> 6; 
		valueL &= 0x03; //only last 2 bits needed, clear the rest
		ADCvalue_temp = valueH | valueL; //10 bit value
		store_adc_value[count]=ADCvalue_temp;		
	}
	
}
*/
