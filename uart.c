#include "uart.h"

#ifdef UART0_R_INTERRUPTS
#pragma interrupt // interupt service routine for receive 
void  ISR_U0_Receive(void) {  
    receive(0);
	clear_recieve_int(0);
}
#endif


#ifdef UART0_T_INTERRUPTS
#pragma interrupt // interupt service routine for transmit 
void  ISR_U0_Transmit(void) {  
    ;
}
#endif


#ifdef UART1_R_INTERRUPTS
#pragma interrupt // interupt service routine for receive 
void  ISR_U1_Receive(void) {  
    receive(1);
	clear_recieve_int(1);
}
#endif


#ifdef UART1_T_INTERRUPTS
#pragma interrupt // interupt service routine for transmit 
void  ISR_U1_Transmit(void) {  
    ;
}
#endif

void construct_uart(void){
	uart0=(UART)uart00;
	uart1=(UART)uart01;
}

void init_uart(char devnum){
	switch(devnum){
		case 0:
			uart = uart0;
			uart->control0.ten=OFF;
			uart->control0.ren=OFF;
			uart0_config();
			#ifdef UART0_R_INTERRUPTS 
			SET_VECTOR(uart0_rx, ISR_U0_Receive); //defining ISR for receive
			#endif
			#ifdef UART0_T_INTERRUPTS
			SET_VECTOR(uart0_tx, ISR_U0_Transmit);
			#endif
		break;
		case 1:
			uart = uart1;
			uart->control0.ten=OFF;
			uart->control0.ren=OFF;
			uart1_config();
			#ifdef UART1_R_INTERRUPTS 
			SET_VECTOR(uart1_rx, ISR_U1_Receive); //defining ISR for receive
			#endif
			#ifdef UART1_T_INTERRUPTS
			SET_VECTOR(uart1_tx, ISR_U1_Transmit);
			#endif
		break;
	}
	BRG0 = ez8_freq/BAUDRATE;
	BRG0 = BRG0/16;	
	//write the baudrate in the registers
	uart->baudh.byte_reg = (unsigned int)((BRG0 & 0xFF00)>>8);
	uart->baudl.byte_reg = (unsigned int)((BRG0 & 0x00FF) & 0x00FF);	
	//configure UART interrupts
	config_uart_int(devnum);
	//clear UART recieve interrupt
	clear_recieve_int(devnum);
	//transmission # of stop bits
	uart->control0.stopbits=stpbits;
	
	#ifdef UART_MULTIPROCESSOR
	//TBD - to be done**
	#else
	uart->control1.mpen=OFF;// disable multiprosessor mode
	#endif
	
	//parity
	if(parity==none){
		uart->control0.pen=0;
	}
	else{
		uart->control0.pen=1;
		if(parity==even){
			uart->control0.psel=0;
		}
		else{
			uart->control0.psel=1;
		}
	}
	

	
	uart->control0.ten=ON;				//transmitter enable
	uart->control0.ren=ON;	
}

void switch_uart(char devnum){
	switch(devnum){
		case 0:
			uart = uart0;
		break;
		case 1:
			uart = uart1;
		break;
		}
	//return uart;
}

//link layer
//void send(char *s_buffer){
void send(char devnum, char data){
	switch_uart(devnum);
	//uart->control0.ren=OFF;//disable receiver
	//uart->control0.ten=ON;//reenable transmitter
	if(uart->status0.tdre){//check if data register is empty
		uart->data.byte_reg = data;//write a byte to the data register
	}else{
		delay_ms(2);//wait for transmission
		uart->data.byte_reg = data;
		}
}
void send2(char devnum, char *data, char length){
	switch_uart(devnum);
	while(length>0){
		if(uart->status0.tdre){//check if data register is empty
			uart->data.byte_reg = *data;//write a byte to the data register
			//uart0->data.byte_reg = data;
		}else{
			delay_ms(2);//wait for transmission
			uart->data.byte_reg = *data;
			//uart0->data.byte_reg = data;
			}
			length=length-1;
	}
}

void sendint(char devnum, int data){
	char byte1 = (char)(data >> 8);
	char byte2 = (char)(data&0x00FF);
	send(devnum,byte1);
	send(devnum, byte2);
}

//void receive(char *r_buffer){
void receive(char devnum){
	char retval;
	switch_uart(devnum);
	x = uart->data.byte_reg;
	//subtract 0x60 on computer side
 	switch(x-0x70){
		case 0:
			send(devnum, (char)light);
		break;
		case 1:
			send(devnum, (char)temp1);
		break;
		case 2:
			send(devnum, (char)soil);
		break;
		case 3:
			send(devnum, (char)humidity);
		break;
		case 4:
			send(devnum,(char)pressure);
		break;
		case 5:
			send(devnum, (char)temp2);
		break;
		case 6:
			toggle_relay(1);
		break;
		case 7:
			toggle_relay(2);
		break;
		case 8:
			toggle_relay(3);
		break;
	}
}

char read(char devnum){
	switch_uart(devnum);
	return uart->data.byte_reg;
}


