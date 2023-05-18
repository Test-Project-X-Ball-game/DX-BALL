
#ifndef LED_H_
#define LED_H_
#include "gpio.h"

void LED_Init(uint8 port_num, uint8 pin_num);

void LED_On(uint8 port_num, uint8 pin_num);

void LED_Off(uint8 port_num, uint8 pin_num);

#endif /* LED_H_ */
