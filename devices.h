#ifndef mappings
#define mappings
/*
 **********************
 register file mappings 
 **********************
*/

//TIMERS
#define timer00			0xF00
#define timer01			0xF08
#define timer02 		0xF10
#define timer03 		0xF18

//UART
#define uart00 			0xF40
#define uart01 			0xF48

//I2C
#define i2c 			0xF50

//SPI
#define spi				0xF60

//ADC
#define adc 			0xF70

//DMA
#define dma00 			0xFB0
#define dma01 			0xFB8
#define dmaadc 			0xFBD

//INTERRUPTS
#define interrupts	 	0xFC0 


//GPIO
#define porta 			0xFD0 //AF: timer0, uart0/ir, i2c
#define portb 			0xFD4 //AF: ADC(ANA0:ANA7)
#define portc 			0xFD8 //AF: timer1, SPI, Timer2
#define portd 			0xFDC //AF: timer3, uart1, Watch-Dog Timer RC Oscillator Output
#define porte 			0xFE0 //no alternate functions
#define portf 			0xFE4 //no alternate functions
#define portg 			0xFE8 //no alternate functions -> LCD(g0:g4)
#define porth 			0xFEC //AF: ADC(ANA8:ANA11)

//WATCHDOG
#define watchdog 		0xFF0

//FLASH MEMORY
#define flash			0xFF8

//ROM
#define rom				0xFF9

//CPU
#define ez8cpu			0xFFC

//#define trim_bit_c0		0xFF6
#endif 