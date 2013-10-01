#ifndef uart_h
#define uart_h
#include "ez8_64k.h"
#include "defines.h"
#include "delay.h"
#include "devices.h"
#include "relays.h"

/*****************************
####@@ configurations  @@####
******************************/

//uart recieve interrupt vectors recheck**
#ifndef uart0_rx
#define  uart0_rx 6
#endif
#ifndef uart1_rx
#define  uart1_rx 20
#endif
// uart recieve interrupts
#define UART0_R_INTERRUPTS 3  
#define UART1_R_INTERRUPTS 3 
//(1 low priority, 2 nominal, 3 high, comment to disable)

//uart transmit interrupts
//#define UART0_T_INTERRUPTS 1 
//(1 low priority, 2 medium, 3 high, comment to disable)

//variables
char *receive_buffer;
char x;
extern double temp1, temp2, light, humidity, pressure, soil;
unsigned int BRG0;

//UaRT configurations 
#define BAUDRATE 9600
#define	bits 8
#define stpbits one
#define	parity none


intrinsic void SET_VECTOR(int vect,void (*hndlr)(void));

//uart device construct
void construct_uart(void);
//intialization
void init_uart(char devnum);
void switch_uart(char devnum);
//link layer
//void send(char *s_buffer);
//void receive(char *r_buffer);
void send(char devnum, char data);
void send2(char devnum, char *data, char length);
void sendint(char devnum, int data);
void receive(char devnum);

char read(char devnum);//link single byte test function 

void ISR_Receive(void);
void ISR_Transmit(void);

extern void uart0_config(void);
extern void uart1_config(void);
extern void clear_recieve_int(char devnum);
extern void config_uart_int(char devnum);
#endif 
