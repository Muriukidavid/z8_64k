#include "buttons.h"

void init_buttons(void){
	btn_config();
	SET_VECTOR(P0AD,btn0_pressed);
	SET_VECTOR(P1AD,btn1_pressed);
	SET_VECTOR(P2AD,btn2_pressed);
	SET_VECTOR(P3AD,btn3_pressed);
}
