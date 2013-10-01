#include "delay.h"

void delay_ms(unsigned int secs)
{
	while(secs>0){
		delay_us(999);
		secs=secs-1;
	}
}
