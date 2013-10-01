#ifndef main_h
#define main_h
#include "ez8_64k.h"
#include "interrupts.h"
#include "uart.h"
#include "gpio.h"
#include "adc.h"
#include "lcd.h"
#include "buttons.h"
//#include "timer.h"

//unsigned int RAM_location;
unsigned char data_available = 0x00;
unsigned int far store_adc_value[12];
//enumerate inputs
enum adc_inputs {ana0=0,ana1,ana2, ana3,ana4,ana5,ana6,ana7,ana8,ana9,ana10,ana11};
/******** functions **********/
void construct_system();
void init_system();
void show_bootup(void);
void screen_layout(void);
void display(void);
void get_temperature1(void);
void get_temperature2(void);
void get_pressure(void);
void get_light(void);
void get_soilwetness(void);
void get_humidity(void);
#endif 
