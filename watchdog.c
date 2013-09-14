#include "watchdog.h"

void construct_watchdog(void){
	ez8.watchdog = (WATCHDOG_TIMER)watchdog0;
}

void init_watchdog(void){
	//unlock wdt
	ez8.watchdog->wdctl.byte_reg=0x55;
	ez8.watchdog->wdctl.byte_reg=0xAA;
	//reload value =300ms, call WDT() in main to reload before this timeout
	ez8.watchdog->wdtu.byte_reg=0x00;
	ez8.watchdog->wdth.byte_reg=0x01;
	ez8.watchdog->wdtl.byte_reg=0x2C;
}