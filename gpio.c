#include "gpio.h"

void construct_gpio(){
	//gpio bindings
	gpio.portA= (PORT)porta;//uatr0
	gpio.portB= (PORT)portb;//adc, PB0->ana0, PB1->ana1
	gpio.portC= (PORT)portc;//Port C
	gpio.portD= (PORT)portd;//Port D
	gpio.portE= (PORT)porte;//Port E
	gpio.portF= (PORT)portf;//Port F
	gpio.portG= (PORT)portg;//lcd output lines PG0:PG4 
	gpio.portH= (PORT)porth;//adc, Port H(PH0, PH1)
}

void adc_config(void){
	gpio.portB->addr.byte_reg = 0x02; //select alternate function set for portB
	gpio.portB->control.byte_reg = 0xff; //select all Port B pins as inputs
	
	gpio.portH->addr.byte_reg = 0x02; 
	gpio.portH->control.byte_reg =0xff; //select all Port H pins as inputs
}

void uart0_config(void){
	gpio.portA->addr.byte_reg = 0x02; //select alternate(ASF0) function for portA
	gpio.portA->control.byte_reg=0x00;
	gpio.portA->control.bit_reg.bit4 = ON;	
	gpio.portA->control.bit_reg.bit5 = ON; //set PA4 and PA5 as UART0 Rx and Tx respectively
}


void uart1_config(void){
	gpio.portD->addr.byte_reg = 0x02; //select alternate function for port D
	gpio.portD->control.byte_reg=0x00;
	gpio.portD->control.bit_reg.bit4=ON;
	gpio.portD->control.bit_reg.bit5=ON; //select PD4 and PD5 as UART1 Rx and Tx respectively 
}

void btn_config(void){
	gpio.portA->addr.byte_reg = 0x01; //select data direction function for port A
	gpio.portA->control.bit_reg.bit3 = ON; //set PA3 as button input
	gpio.portA->control.bit_reg.bit2 = ON; //set PA2 as button input
	gpio.portA->control.bit_reg.bit1 = ON; //set PA1 as button input
	gpio.portA->control.bit_reg.bit0 = ON; //set PA0 as button input
}

void timer_config(void){
	gpio.portC->addr.byte_reg = 0x02; //select alternate function for port C
	gpio.portC->control.bit_reg.bit1 = ON; //set PC1 as PWM out
	gpio.portC->control.bit_reg.bit7 = ON; //set PC7 as PWM complementary output
}

void relay_config(void){
	gpio.portF->addr.byte_reg = 0x01;
	gpio.portF->control.byte_reg = 0x00;
	gpio.portF->output.byte_reg = 0x00;
}

void config_lcd(void){
	gpio.portG->addr.byte_reg = 0x01; //select data direction
	gpio.portG->control.byte_reg = 0x00; //all outputs
	gpio.portG->output.byte_reg = 0x00; //initialize all outputs to low
}

//relay functions
//modify to match pinout
void relay1_toggle(void){
	char st = gpio.portF->output.bit_reg.bit0;
	if(st){
		gpio.portF->output.bit_reg.bit0 = OFF;
		send(1,0x02);
	}else{
		gpio.portF->output.bit_reg.bit0 = ON;
		send(1,0x01);
	}
}

void relay2_toggle(void){
	char st = gpio.portF->output.bit_reg.bit1;
	if(st){
		gpio.portF->output.bit_reg.bit1 = OFF;
		send(1,0x02);
	}
	else{
		gpio.portF->output.bit_reg.bit1 = ON;
		send(1,0x01);
	}
}

void relay3_toggle(void){
	char st = gpio.portF->output.bit_reg.bit2;
	if(st){
		gpio.portF->output.bit_reg.bit2 = OFF;
		send(1,0x02);
	}else{
		gpio.portF->output.bit_reg.bit2 = ON;
		send(1,0x01);
	}
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