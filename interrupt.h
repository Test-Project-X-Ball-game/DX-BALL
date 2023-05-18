/******************************************************************************
 *
 * Module: GPIO
 *
 * File Name: gpio.h
 *
 * Description: Header file for the ARM GPIO driver
 *
 * Author: Bassant Amr
 *
 *******************************************************************************/

#ifndef INTERRUPT_H_
#define INTERRUPT_H_

#include "gpio.h"
#include "common_macros.h"
#include "tm4c123gh6pm.h"
#include "led.h"

typedef enum {
 LEVEL,FALLING,RISING
}INT_confi;

void INTERRUPT_Init(uint8 port_num, uint8 pin_num,INT_confi status);

void INTERRUPT_Deinit(uint8 port_num);

//void INTERRUPT_setCallBack(void(*a_ptr)(void));


#endif /* INTERRUPT_H_ */
