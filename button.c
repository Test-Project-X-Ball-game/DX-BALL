

#include "button.h"

void BUTTON_Init(uint8 port_num, uint8 pin_num,choose_confi status){
	GPIO_Init(port_num,pin_num,PIN_INPUT,GPIO,NON,ENABLE);
	if(status==INT) INTERRUPT_Init(port_num,pin_num,RISING);
}

uint8 BUTTON_isPressed(uint8 port_num, uint8 pin_num){
	return GPIO_readPin(port_num,pin_num);
}
