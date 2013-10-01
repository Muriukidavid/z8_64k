#ifndef relays
#define relays

#include "gpio.h"

void init_relays(void);
void toggle_relay(char devnum);
#endif 