#include "relays.h"
void init_relays(void){
	relay_config();
}

void toggle_relay(char devnum){
	switch(devnum){
		case 1: 
			relay1_toggle();
		break;
		case 2:
			relay2_toggle();
		break;
		case 3:
			relay3_toggle();
		break;
		}
	
}