#include "main.h"

//test variables
double temp1, temp2, light, humidity, pressure, soil;
int main(){
	DI();//disable interrupts or hell breaks loose during hardware config
	construct_system();//bind device addresses
	init_system();//init devices
		//clear all interrupts
	clearall_interrupts();
	EI();//enable interrupts: we have UART_recieve
	
	//set the lcd contrast
	//lcd_contrast(0x42);
	lcd_contrast(0x32);
	//clear the lcd
	clearram();
	//show boot up message
	show_bootup();
	//clear boot message
	clearram();
	//screen layout
	screen_layout();
	send(1, 225);
	send(1, 255);
	send(1, 2);
	while(1)
	{
		get_temperature1();
		get_temperature2();
		get_light();
		get_pressure();
		get_humidity();
		get_soilwetness();
		display();
		delay_ms(800);		
	}
	return 0;
}

//construct device before initializing
void construct_system(){
	construct_gpio();
	construct_interrupts();
	construct_uart();
	construct_adc();
}

//board bring-up
void init_system(){
	init_uart(0);//configure uart, check uart.h
	init_uart(1);//configure uart, check uart.h
	init_adc();//initialize ADC, check adc.h
	init_lcd();//init lcd
	init_relays();//init toggle relays
}

void show_bootup(void){
	cursorxy(2,2);
	putstr((unsigned char*)"UON Physics");
	cursorxy(3,1);
	putstr((unsigned char*)"ASK SHOW 2013");
	cursorxy(4,3);
	putstr((unsigned char*)"e-FARMING");
	cursorxy(6,3);
	putstr((unsigned char*)"Version 3.2");
	delay_ms(2000);
}


void screen_layout(void){
	cursorxy(1,2);
	putstr((unsigned char*)"e-FARMING");
	cursorxy(2,1);
	putstr((unsigned char*)"L:");
	
	cursorxy(3,1);
	putstr((unsigned char*)"T1:");	
	
	cursorxy(4,1);
	putstr((unsigned char*)"T2:");
	
	cursorxy(2,8);
	putstr((unsigned char*)"H:");
	cursorxy(3,8);
	putstr((unsigned char*)"P:");	
	cursorxy(4,8);
	putstr((unsigned char*)"W:");
}

void display(void){	
	clear(2,4,2);
	clear(3,4,2);
	clear(4,4,2);
	clear(2,11,3);
	clear(3,11,2);
	clear(4,11,4);
	cursorxy(2,4);//set cursor
	//putint(light,3);//print data from adc
	putint(light,2);
	//cursorxy(2,7);
	putstr((unsigned char*)"%");
	cursorxy(2,11);
	putint(humidity,3);
	putstr((unsigned char*)"%");
	cursorxy(3,4);//set cursor
	putint(temp1,2);//print data from adc
	putstr((unsigned char*)"^");
	cursorxy(3,11);
	putint(pressure,2);
	putstr((unsigned char*)"kP");
	cursorxy(4,4);//set cursor
	putint(temp2,2);//print data from adc
	putstr((unsigned char*)"^");
	cursorxy(4,11);
	if(soil<30)
		putstr((unsigned char*)"Wet");
	else if(soil>70)
		putstr((unsigned char*)"Dry");
	else
		putstr((unsigned char*)"Mid");
	
}

void get_temperature1(void) {
	unsigned long int data=0;
	data = store_adc_value[1];
	data = data * 2100;
	temp1 = (double)data/1024;
	temp1 = temp1/10;
	temp1 = (temp1-32)*5;
	temp1 = temp1/9;
}

void get_temperature2(void) {
	unsigned long int data=0;
	data = store_adc_value[9];
	data = data * 2100;
	temp2 = (double)data/1024;
	temp2 = temp2*26;
	temp2 = temp2/1000;
	//temp2 = (temp1-32)*5;
	//temp2 = temp1/9;
}

void get_light(void){
	unsigned long int data=0;
	data = store_adc_value[0];
	data = data * 2100;
	light = (double)data/1024;
	light = light/21;
	if(light>95)
		light=0;
	else
		light = 100-light;
}

void get_pressure(void){
	unsigned long int data=0;
	data = store_adc_value[4];
	data = data * 2100;
	pressure = (double)data/1024;
	pressure = pressure*40;
	pressure = pressure/2100;	
}

void get_humidity(void){
	unsigned long int data=0;
	data = store_adc_value[8];
	data = data * 2100;
	humidity = (double)data/1024;
	humidity = humidity*50;
	humidity = humidity/2020;
	if(humidity>95)
		humidity=100;
	//else
	//	humidity = 100-humidity;
}

void get_soilwetness(void){
	unsigned long int data=0;
	data = store_adc_value[3];
	data = data * 2100;
	soil = (double)data/1024;
	soil = soil/21;
}

