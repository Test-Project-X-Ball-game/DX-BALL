#include "led.h"

void LED_Init(uint8 port_num, uint8 pin_num){
	GPIO_Init(port_num,pin_num,PIN_OUTPUT,GPIO,NON,ENABLE);
}

void LED_On(uint8 port_num, uint8 pin_num){
	GPIO_writePin(port_num,pin_num,LOGIC_HIGH);
}

void LED_Off(uint8 port_num, uint8 pin_num){
	GPIO_writePin(port_num,pin_num,LOGIC_LOW);
}
