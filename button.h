
#ifndef BUTTON_H_
#define BUTTON_H_

#include "gpio.h"
#include "interrupt.h"


typedef enum{
	gpio,INT
}choose_confi;


void BUTTON_Init(uint8 port_num, uint8 pin_num,choose_confi status);

uint8 BUTTON_isPressed(uint8 port_num, uint8 pin_num);

#endif /* BUTTON_H_ */
