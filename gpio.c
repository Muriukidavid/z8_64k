#include "gpio.h"

void construct_gpio(){
	//gpio bindings
	gpio.portA= (PORT)porta;//uatr0
	gpio.portB= (PORT)portb;//adc, PB0->ana0, PB1->ana1
	gpio.portG= (PORT)portg;//lcd output lines PG0:PG4 
}

void init_gpio(void){
	//initialize ports... assumption: all registers are initially zero-filled

	//initialize port A for uart and pwm.
	gpio.portA->addr.byte_reg = 0x02;		//select alternate(AF) function for portA
	gpio.portA->control.bit_reg.bit4 = ON;	
	gpio.portA->control.bit_reg.bit5 = ON;//set PA4 and PA5 as AF (UART Rx and Tx respectively)	
	gpio.portA->control.bit_reg.bit1 = ON; //set PA1 as PWM out
	gpio.portA->control.bit_reg.bit0 = ON; //set PA0 as PWM complementary output
	
	//initialize port G for LCD
	gpio.portG->addr.byte_reg = 0x01;	//select data direction
	gpio.portG->control.byte_reg = 0x00;	//all outputs
	gpio.portG->output.byte_reg = 0x00;	//initialize all outputs to low
	
	//initialize port B for ADC
	gpio.portB->addr.byte_reg = 0x07;		//select alternate function set 1(ASF1) for portB
	gpio.portB->control.byte_reg =0x00; //reset all PortB pins
	gpio.portB->control.bit_reg.bit0 = ON;	//select PB0 as ASF1 = ADC input
	gpio.portB->control.bit_reg.bit1 = ON;	//select PB1 as ASF1 = ADC input
}


//LCD pin toggle functions
/* 
Modify it to fit your schematic
change the port and bit part accordigly
e.g you can use portA and pin0(PA0)like so:
gpio.portA->output.bit_reg.bit0=ON;
*/
//SCK = PG4 ON
void SCK(void) { 
	gpio.portG->output.bit_reg.bit4=ON;
}
//CLR_SCK = PG4 OFF
void CLR_SCK(void) { 
	gpio.portG->output.bit_reg.bit4=OFF;
}

//DAT = PG2 ON
void DAT(void) {
	gpio.portG->output.bit_reg.bit3=ON;
}
//CLR_DAT = PG2 OFF
void CLR_DAT(void) {
	gpio.portG->output.bit_reg.bit3=OFF;
}

//DC = PG2 ON
void DC(void) {
	gpio.portG->output.bit_reg.bit2=ON;
}
//CLR_DC = PG2 OFF
void CLR_DC(void) {
	gpio.portG->output.bit_reg.bit2=OFF;
}

//CE = PG1 ON
void CE(void) {
	gpio.portG->output.bit_reg.bit1=ON;
}
//CLR_CE = PG1 OFF	
void CLR_CE(void) {
	gpio.portG->output.bit_reg.bit1=OFF;
}
//RES = PG0 ON	
void RES(void) { 
	gpio.portG->output.bit_reg.bit0=ON; 
}
//CLR_RES = PG0 OFF
void CLR_RES(void) { 
	gpio.portG->output.bit_reg.bit0=OFF; 
}