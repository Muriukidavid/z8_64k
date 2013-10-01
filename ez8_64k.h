#ifndef z8_64k
#define z8_64k
#include "generics.h"
//ez8 4k XP defines 
unsigned long int ez8_freq = 18432000; //the ez864K frequency

//type port
typedef struct {
	volatile REG addr;
	volatile REG control;
	volatile REG input;
	volatile REG output;
}*PORT;

//TYPE GPIO
typedef struct{
	PORT portA;
	PORT portB;
	PORT portC;
	PORT portD;
	PORT portE;
	PORT portF;
	PORT portG;
	PORT portH;
}GPIO;

typedef struct {
	volatile unsigned char 
	cen:1,
	reserved:1,
	vref:1,
	cont:1,
	anain:4;
}ADCCTL;

//adc
typedef struct {
	ADCCTL control;
	volatile REG reserved;	
	volatile REG datah;	
	volatile REG datal;			
}*ADC;

//uart
//uart status reg 0
typedef struct {
	volatile unsigned char 
	 rda:1, 
	  pe:1, 
	  oe:1,
	  fe:1,
	brkd:1,
	tdre:1,
	 txe:1,
	 cts:1;
}STATUS0;
//uart status reg 1
typedef struct {
	volatile unsigned char 
	 status1_reserved:6, 
	 newfrm:1,
	 mprx:1;
}STATUS1;
//uart control 0 register
//TEN REN CTSE PEN PSEL SBRK STOP LBEN
typedef struct {
	volatile unsigned char	
	ten:1,
	ren:1,
	ctse:1,
	pen:1,
	psel:1,
	sbrk:1,
	stopbits:1,
	lben:1;
}CONTROL0;
//uart control 1 register
//MPMD[1] MPEN MPMD[0] MPBT DEPOL BRGCTL RDAIRQ IREN
typedef struct {
	volatile unsigned char
	mpmd1:1,
	mpen:1,
	mpmd0:1,
	mpbt:1,
	depol:1,
	brgctl:1,
	rdairq:1,
	iren:1;
}CONTROL1;

typedef struct {
	volatile REG data;// Tx and Rx point to same location => (char*) 0x00;
	STATUS0 status0;	
	CONTROL0 control0;
	CONTROL1 control1; 	
	STATUS1 status1;
	volatile REG addr_cmp;
	volatile REG baudh;
	volatile REG baudl;
}*UART;
//end uart

//i2c
//i2c status reister
typedef struct {
	volatile unsigned char	
	tdre:1,
	rdrf:1,
	ack:1,
	tenbit:1,
	rd:1,
	tas:1,
	dss:1,
	ncki:1;
}I2CSTAT;
//i2c control register
typedef struct {
	volatile unsigned char	
	ien:1,
	start:1,
	stop:1,
	birq:1,
	txi:1,
	nak:1,
	flush:1,
	filten:1;
}I2CCTL;
//i2c diagnostic state register
typedef struct {
	volatile unsigned char	
	sclin:1,
	sdain:1,
	stpcnt:1,
	txrxstate:5;
}I2CDST;
//i2c diagnostic control register
typedef struct {
	volatile unsigned char	
	reserved:7,
	diag:1;
}I2CDIAG;

typedef struct {
	volatile REG data;
	I2CSTAT status;
	I2CCTL control;
	volatile REG baud_h;
	volatile REG baud_l;
	I2CDST diag_state;
	I2CDIAG diag_ctl;
}*I2C;

//spi
//spi status register
typedef struct{
	volatile unsigned char	
	irq:1,
	ovr:1,
	col:1,
	abt:1,
	reserved:2,
	txst:1,
	slas:1;
}SPISTAT;
//spi mode register
typedef struct{
	volatile unsigned char	
	reserved:2,
	diag:1,
	numbits:3,
	ssio:1,
	ssiv:1;
}SPIMODE;
//spi diagnostic state register
typedef struct{
	volatile unsigned char	
	scken:1,
	tcken:1,
	spistate:6;
}SPIDST;

typedef struct {
	volatile REG data;
	volatile REG control;
	SPISTAT status;
	SPIMODE mode;
	SPIDST diag_state;
	volatile unsigned char reserved;
	volatile REG baud_hi;
	volatile REG baud_l;
}*SPI;
//end spi

//dma
//dmax control register
typedef struct {
	volatile unsigned char	
	den:1,
	dle:1,
	ddir:1,
	irqen:1,
	wsel:1,
	rss:3;
}DMAxCTL;

typedef struct {
	volatile unsigned char	
	endh:4,
	starth:4;
}DMAxH;

typedef struct {
	DMAxCTL control;
	volatile REG ioaddr;
	DMAxH high;
	volatile REG startaddr;
	volatile REG endaddr;
}*DMA;
//end dma

//dma_adc
//DMAA_CTL: DAEN IRQEN Reserved[1:0] ADC_IN[3:0]
typedef struct {
	volatile unsigned char
	daen:1,
	irqen:1,
	reserved:2,
	adcin:4;//1011 channel 0 to 11 updated
}DMAA_CTL;

//DMA_ADC Status Register (DMAA_STAT)
//CADC[3:0] Reserved IRQA IRQ1 IRQ0
typedef struct {
	volatile unsigned char
	cadc:4,
	reserved:1,
	irqa:1,
	irq1:1,
	irq0:1;
}DMAA_STAT;

typedef struct {
	volatile REG addr;
	DMAA_CTL control;
	DMAA_STAT status;
}*DMA_ADC;
//end dma_adc

//irq
//irq0 enable high register
//T2ENH T1ENH T0ENH U0RENH U0TENH I2CENH SPIENH ADCENH
typedef struct {
	volatile unsigned char 	
	t2enh:1,
	t1enh:1,
	t0enh:1,
	u0renh:1,
	u0tenh:1,
	i2cenh:1,
	spienh:1,
	adcenh:1;
}IRQ0ENH;

//enable low register
//T2ENL T1ENL T0ENL U0RENL U0TENL I2CENL SPIENL ADCENL
typedef struct {
	volatile unsigned char 
	t2enl:1,
	t1enl:1,
	t0enl:1,
	u0renl:1,
	u0tenl:1,
	i2cenl:1,
	spienl:1,
	adcenl:1;		
}IRQ0ENL;

//irq1 enable high register
//PAD7ENH PAD6ENH PAD5ENH PAD4ENH PAD3ENH PAD2ENH PAD1ENH PAD0ENH
typedef struct {
	volatile unsigned char 
	pad7venh:1,
	pad6cenh:1,
	pad5enh:1,
	pad4enh:1,
	pad3enh:1,
	pad2enh:1,
	pad1enh:1,
	pad0enh:1;			
}IRQ1ENH;

//irq1 enable low register
//PAD7ENL PAD6ENL PAD5ENL PAD4ENL PAD3ENL PAD2ENL PAD1ENL PAD0ENL
typedef struct {
	volatile unsigned char 
	pad7venl:1,
	pad6cenl:1,
	pad5enl:1,
	pad4enl:1,
	pad3enl:1,
	pad2enl:1,
	pad1enl:1,
	pad0enl:1;			
}IRQ1ENL;

//irq2 enable high register
//T3ENH U1RENH U1TENH DMAENH C3ENH C2ENH C1ENH C0ENH
typedef struct {
	volatile unsigned char 
	t3enh:1,
	u1renh:1,
	u1tenh:1,
	dmaenh:1,
	c3enh:1,
	c2enh:1,
	c1enh:1,
	c0enh:1;
}IRQ2ENH;

//irq2 enable low register
//T3ENL U1RENL U1TENL DMAENL C3ENL C2ENL C1ENL C0ENL
typedef struct {
	volatile unsigned char 
	t3enl:1,
	u1renl:1,
	u1tenl:1,
	dmaenl:1,
	c3enl:1,
	c2enl:1,
	c1enl:1,
	c0enl:1;			
}IRQ2ENL;

//T2I T1I T0I U0RXI U0TXI I2CI SPII ADCI
typedef struct {
	volatile unsigned char 
	t2i:1,
	t1i:1,
	t0i:1,
	u0rxi:1,
	u0txi:1,
	i2ci:1,
	spii:1,
	adci:1;
}IRQ0;

//PAD7I PAD6I PAD5I PAD4I PAD3I PAD2I PAD1I PAD0I
typedef struct {
	volatile unsigned char 
	pad7i:1,
	pad6i:1,
	pad5i:1,
	pad4i:1,
	pad3i:1,
	pad2i:1,
	pad1i:1,
	pad0i:1;
}IRQ1;

//T3I U1RXI U1TXI DMAI PC3I PC2I PC1I PC0I
typedef struct {
	volatile unsigned char 
	t3i:1,
	u1rxi:1,
	u1txi:1,
	dmai:1,
	pc3i:1,
	pc2i:1,
	pc1i:1,
	pc0i:1;
}IRQ2;

typedef union {
	IRQ2 irq2;
	volatile REG irqtwo;
}IRQ2E;
//interrupt controller
typedef struct {
	IRQ0 irq0;
	IRQ0ENH irq0enh;
	IRQ0ENL irq0enl;
	IRQ1 irq1;
	IRQ1ENH irq1enh;
	IRQ1ENL irq1enl;
	IRQ2E irq2e;
	IRQ2ENH irq2enh;
	IRQ2ENL irq2enl;
	volatile REG reserved0;
	volatile REG reserved1;
	volatile REG reserved2;
	volatile REG reserved3;
	volatile REG irqes;
	volatile REG irqss;
	volatile REG irqctl;
}*INTERRUPT_CONTROLLER;

//timers
typedef struct {
	volatile unsigned char
	tmodehi:1,
	ticonfig:2,
	reserved:1,
	pwmd:3,
	incap:1;
}TCTL0;

typedef struct {
	volatile unsigned char
	ten:1,
	tpol:1,
	pres:3,
	tmode:3;
}TCTL1;

typedef struct {
	volatile REG th;//rststat; reset status as well as timer control
	volatile REG tl;
	volatile REG trh;
	volatile REG trl;
	volatile REG pwmh;
	volatile REG pwml;
	TCTL0 tctl0;
	TCTL1 tctl1;
}*TIMER;

//watchdog timer
typedef struct {
	volatile REG wdctl;//rststat; reset status as well as timer control
	volatile REG wdtu;
	volatile REG wdth;
	volatile REG wdtl;
}*WATCHDOG_TIMER;

//Flash Memory Controller
typedef struct{
	volatile REG fctl;//fstat; flash control as well as flash status same address
	volatile REG fps;//fprot; flash page select as well as flash sector protect same address
	volatile REG ffreqh;
	volatile REG ffreql;
}*FLASH_MEMORY_CONTROLLER;
//eZ8 CPU
typedef struct{
	volatile unsigned char 
	tram:1,
	reserved:2,
	vbo:1,
	temp:1,
	adc_p:1,// adc conflicts with adc address definition, rename to adc_p ;-)
	comp:1,
	reserved1:1;
}*POWER_CONTROLLER;

//eZ8 CPU
typedef struct {
	volatile REG flags;
	volatile REG rp;//register pointer
	volatile REG sph;//stack pointer high byte
	volatile REG spl;//stack pointer low byte
}*CPU;


/*
instances
*/

//timers
TIMER timer0; 
TIMER timer1;
TIMER timer2;
TIMER timer3;
//timer holder
TIMER timer;
//uart
UART uart0;
UART uart1;
//uart holder for switching
UART uart;
//i2c
I2C i2c0;

//spi
SPI spi0;

//adc
ADC adc0;

//dma
DMA dma0;
DMA dma1;
DMA_ADC dmaadc;

INTERRUPT_CONTROLLER interrupt_c;

GPIO gpio;

FLASH_MEMORY_CONTROLLER flash_mc;

CPU cpu;

#endif 
