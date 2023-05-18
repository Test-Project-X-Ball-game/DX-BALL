#include "interrupt.h"
/* Global variables to hold the address of the call back function in the application 
static volatile void (*g_callBackPtr)(void) = NULL_PTR;
*/
void INTERRUPT_Init(uint8 port_num, uint8 pin_num,INT_confi status){
	if(port_num >= NUM_OF_PORTS)
	{
		/* Do Nothing */
	}
	else
	{
		//GPIO_Init(port_num,pin_num,PIN_INPUT,GPIO,NON,ENABLE);
		/* Read the port value as required */
		switch(port_num)
		{
		case PORTA_ID:
			if(status == LEVEL){
				SET_BIT(GPIO_PORTA_IS_R,pin_num);  //detect edge =>0  //detect level => 1
			}else CLEAR_BIT(GPIO_PORTA_IS_R,pin_num);  //detect edge =>0  //detect level => 1
			
			CLEAR_BIT(GPIO_PORTA_IBE_R,pin_num);  //Interrupt generation is controlled by the GPIO Interrupt Event(GPIOIEV) =>0  //both edges =>1
			if(status == FALLING){
				CLEAR_BIT(GPIO_PORTA_IEV_R,pin_num);  //falling edge =>0 //rising edge =>1
			}else SET_BIT(GPIO_PORTA_IEV_R,pin_num);  //falling edge =>0 //rising edge =>1
			
			SET_BIT(GPIO_PORTA_ICR_R,pin_num);  //clear flag
			SET_BIT(GPIO_PORTA_IM_R,pin_num);  //enable interrupt to Interrupt controller(arm bit)
			SET_BIT(NVIC_EN0_R,INT_GPIOA-16);   //enable module interrupt for all port A
			
			NVIC_PRI0_R = (NVIC_PRI0_R & 0xFFFFFF00)|0x00000000; // (g) priority 0
			break;
		case PORTB_ID:
			CLEAR_BIT(GPIO_PORTB_IS_R,pin_num);  //detect edge =>0  //detect level => 1
			CLEAR_BIT(GPIO_PORTB_IBE_R,pin_num);  //Interrupt generation is controlled by the GPIO Interrupt Event(GPIOIEV) =>0  //both edges =>1
			SET_BIT(GPIO_PORTB_IEV_R,pin_num);  //falling edge =>0 //rising edge =>1
			SET_BIT(GPIO_PORTB_ICR_R,pin_num);  //clear flag
			SET_BIT(GPIO_PORTB_IM_R,pin_num);  //enable interrupt to Interrupt controller(arm bit)
			SET_BIT(NVIC_EN0_R,INT_GPIOB-16);   //enable module interrupt for all port B
			NVIC_PRI0_R = (NVIC_PRI0_R & 0xFFFF00FF)|0x00000000; // (g) priority 0
			break;
		case PORTC_ID:
			CLEAR_BIT(GPIO_PORTC_IS_R,pin_num);  //detect edge =>0  //detect level => 1
			CLEAR_BIT(GPIO_PORTC_IBE_R,pin_num);  //Interrupt generation is controlled by the GPIO Interrupt Event(GPIOIEV) =>0  //both edges =>1
			SET_BIT(GPIO_PORTC_IEV_R,pin_num);  //falling edge =>0 //rising edge =>1
			SET_BIT(GPIO_PORTC_ICR_R,pin_num);  //clear flag
			SET_BIT(GPIO_PORTC_IM_R,pin_num);  //enable interrupt to Interrupt controller(arm bit)
			SET_BIT(NVIC_EN0_R,INT_GPIOC-16);   //enable module interrupt for all port C
			NVIC_PRI0_R = (NVIC_PRI0_R & 0xFF00FFFF)|0x00000000; // (g) priority 0
			break;
		case PORTD_ID:
			CLEAR_BIT(GPIO_PORTD_IS_R,pin_num);  //detect edge =>0  //detect level => 1
			CLEAR_BIT(GPIO_PORTD_IBE_R,pin_num);  //Interrupt generation is controlled by the GPIO Interrupt Event(GPIOIEV) =>0  //both edges =>1
			SET_BIT(GPIO_PORTD_IEV_R,pin_num);  //falling edge =>0 //rising edge =>1
			SET_BIT(GPIO_PORTD_ICR_R,pin_num);  //clear flag
			SET_BIT(GPIO_PORTD_IM_R,pin_num);  //enable interrupt to Interrupt controller(arm bit)
			SET_BIT(NVIC_EN0_R,INT_GPIOD-16);   //enable module interrupt for all port D
			NVIC_PRI0_R = (NVIC_PRI0_R & 0x00FFFFFF)|0x00000000; // (g) priority 0
			break;
		case PORTE_ID:
			CLEAR_BIT(GPIO_PORTE_IS_R,pin_num);  //detect edge =>0  //detect level => 1
			CLEAR_BIT(GPIO_PORTE_IBE_R,pin_num);  //Interrupt generation is controlled by the GPIO Interrupt Event(GPIOIEV) =>0  //both edges =>1
			SET_BIT(GPIO_PORTE_IEV_R,pin_num);  //falling edge =>0 //rising edge =>1
			SET_BIT(GPIO_PORTE_ICR_R,pin_num);  //clear flag
			SET_BIT(GPIO_PORTE_IM_R,pin_num);  //enable interrupt to Interrupt controller(arm bit)
			SET_BIT(NVIC_EN0_R,INT_GPIOE-16);   //enable module interrupt for all port E
			NVIC_PRI1_R = (NVIC_PRI1_R & 0xFFFFFF00)|0x00000000; // (g) priority 0
			break;
		case PORTF_ID:
			CLEAR_BIT(GPIO_PORTF_IS_R,pin_num);  //detect edge =>0  //detect level => 1
			CLEAR_BIT(GPIO_PORTF_IBE_R,pin_num);  //Interrupt generation is controlled by the GPIO Interrupt Event(GPIOIEV) =>0  //both edges =>1
			SET_BIT(GPIO_PORTF_IEV_R,pin_num);  //falling edge =>0 //rising edge =>1
			SET_BIT(GPIO_PORTF_ICR_R,pin_num);  //clear flag()
			SET_BIT(GPIO_PORTF_IM_R,pin_num);  //enable interrupt to Interrupt controller(arm bit)
			SET_BIT(NVIC_EN0_R,INT_GPIOF-16);   //enable module interrupt for all port F
			NVIC_PRI7_R = (NVIC_PRI7_R&0xFF00FFFF)|0x00000000; // (g) priority 5
			break;
		}
		//EnableInterrupts();           // (i) Clears the I bit
	}
	
}

void INTERRUPT_Deinit(uint8 port_num){
	if(port_num >= NUM_OF_PORTS)
	{
		/* Do Nothing */
	}
	else
	{
		GPIO_Deinit(port_num);
	}
}

/*set call back
void INTERRUPT_setCallBack(void(*a_ptr)(void)){
	g_callBackPtr = a_ptr;
}
*/
void GPIOPortA_Handler(void){
		uint8 i=0;
		for(i=0;i<=7;i++){
			if(GPIO_PORTA_RIS_R & (1<<i)){
				SET_BIT(GPIO_PORTA_ICR_R,i);      // acknowledge (clear flag)
				//if(g_callBackPtr!=NULL_PTR){(*g_callBackPtr)();}
				if(i==2){
					LED_On(PORTF_ID,PIN1_ID);  // LED is green
					LED_Off(PORTF_ID,PIN2_ID);
				}
				if(i==3){
					LED_On(PORTF_ID,PIN2_ID);  // LED is green
					LED_Off(PORTF_ID,PIN1_ID);
				}
				break;
			}
		}
}
/*
void GPIOPortB_Handler(void){
		uint8 i=0;
		for(i=0;i<=7;i++){
			if(GPIO_PORTB_RIS_R & (1<<i)){
				SET_BIT(GPIO_PORTB_ICR_R,i);      // acknowledge (clear flag)
				//if(g_callBackPtr!=NULL_PTR){(*g_callBackPtr)();}
				if(i==3){
					LED_On(PORTB_ID,PIN0_ID);  // LED is green
					LED_On(PORTB_ID,PIN2_ID);
					LED_Off(PORTB_ID,PIN1_ID);
				}
				if(i==4){
					LED_On(PORTB_ID,PIN1_ID);  // LED is green
					LED_Off(PORTB_ID,PIN0_ID);
					LED_Off(PORTB_ID,PIN2_ID);
				}
				break;
			}
		}
}
*/
void GPIOPortC_Handler(void){
		
}

void GPIOPortD_Handler(void){
		
}

void GPIOPortE_Handler(void){
		
}

void GPIOPortF_Handler(void){
		/*if(g_callBackPtr!=NULL_PTR){
		(*g_callBackPtr)();
		}*/
		
}
