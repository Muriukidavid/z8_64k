#ifndef gpio_h
#define gpio_h
#include "ez8_64k.h"
#include "defines.h"
#include "devices.h"

void construct_gpio(void);
void uart0_config(void);
void uart1_config(void);
void adc_config(void);
void config_lcd(void);
void btn_config(void);
void timer_config(void);
void relay_config(void);

//lcd pin toggle prototypes
void SCK(void);
void CLR_SCK(void);
void DAT(void);
void CLR_DAT(void);
void DC(void);
void CLR_DC(void);
void CE(void);	
void CLR_CE(void);
void RES(void);
void CLR_RES(void);

//relay functions
void relay1_toggle(void);
void relay2_toggle(void);
void relay3_toggle(void);

extern void send(char devnum, char data);
#endif 