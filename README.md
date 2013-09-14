minimum zilog z8 64k 80-pin board bring up C code. very general with a few peripheral devices: ADC, PWM, UART and an LCD. Does not use the Zilog ez8.h file, for the lazy programmer. I cannot stand cryptic names for registers and devices, and i tend to not remember things i dont have to, so...  here we are.

This is how we use structs in C, just like classes/Objects in C++ or java, but to bundle a bunch of registers into a device and map-out the micro. Its kinda nice start code for any zilog embedded project. 
