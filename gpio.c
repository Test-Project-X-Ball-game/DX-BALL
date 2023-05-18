 /******************************************************************************
 *
 * Module: GPIO
 *
 * File Name: gpio.c
 *
 * Description: Source file for the ARM GPIO driver
 *
 * Author: Bassant Amr
 *
 *******************************************************************************/

#include "gpio.h"
#include "common_macros.h" /* To use the macros like SET_BIT */
#include "tm4c123gh6pm.h" /* To use the IO Ports Registers */

/*
 * Description :
 * Setup the direction of the required pin input/output.
 * If the input port number or pin number are not correct, The function will not handle the request.
 */
void GPIO_Init(uint8 port_num, uint8 pin_num, GPIO_PinDirectionType Direction,GPIO_PinMODE1 mode1,GPIO_PINCONNECTIONS connection,GPIO_DIGITAL isDigital)
{
	/*
	 * Check if the input port number is greater than NUM_OF_PINS_PER_PORT value.
	 * Or if the input pin number is greater than NUM_OF_PINS_PER_PORT value.
	 * In this case the input is not valid port/pin number
	 */
	if((pin_num >= NUM_OF_PINS_PER_PORT) || (port_num >= NUM_OF_PORTS))
	{
		/* Do Nothing */
	}
	else
	{
		SET_BIT(SYSCTL_RCGC2_R,port_num); //enable clock
		/* Setup the pin direction as required */
		switch(port_num)
		{
		case PORTA_ID:
			/**/
			CLEAR_BIT(GPIO_PORTA_PCTL_R,(pin_num*4));
			CLEAR_BIT(GPIO_PORTA_PCTL_R,(pin_num*4+1));
			CLEAR_BIT(GPIO_PORTA_PCTL_R,(pin_num*4+2));
			CLEAR_BIT(GPIO_PORTA_PCTL_R,(pin_num*4+3));
			/*unlock port*/
			GPIO_PORTA_LOCK_R = 0x4C4F434B;
			/*direction input/output*/
			if(Direction==PIN_INPUT){
				CLEAR_BIT(GPIO_PORTA_DIR_R,pin_num);
			}else{
				SET_BIT(GPIO_PORTA_DIR_R,pin_num);
			}
			/*mode1 gpio/alternate function*/
			if(mode1==GPIO){
				CLEAR_BIT(GPIO_PORTA_AFSEL_R,pin_num);
			}
			else{
				SET_BIT(GPIO_PORTA_AFSEL_R,pin_num);
			}
			/*set connection pull up/pull down*/
			if(connection==PULLUP){
				SET_BIT(GPIO_PORTA_PUR_R,pin_num);  //enable pull up
				CLEAR_BIT(GPIO_PORTA_PDR_R,pin_num); //disable pull down
			}
			else if(connection==PULLDOWN){
				SET_BIT(GPIO_PORTA_PDR_R,pin_num);  //enable pull down
				CLEAR_BIT(GPIO_PORTA_PUR_R,pin_num);  //disable pull up
			}else{
				CLEAR_BIT(GPIO_PORTA_PDR_R,pin_num); //disable pull down
				CLEAR_BIT(GPIO_PORTA_PUR_R,pin_num);  //disable pull up
			}
			/*enable or disable digital function*/
			if(isDigital==DISABLE){
				CLEAR_BIT(GPIO_PORTA_DEN_R,pin_num);  //disable pull up
			}else{
				SET_BIT(GPIO_PORTA_DEN_R,pin_num);  //enable pull up
				GPIO_PORTA_AMSEL_R = 0x00;
			}
			SET_BIT(GPIO_PORTA_CR_R,pin_num);  //commit (enable write to GPIODEN,GPIOPUR,GPIOPDR)
			break;
		case PORTB_ID:
			/**/
			CLEAR_BIT(GPIO_PORTB_PCTL_R,(pin_num*4));
			CLEAR_BIT(GPIO_PORTB_PCTL_R,(pin_num*4+1));
			CLEAR_BIT(GPIO_PORTB_PCTL_R,(pin_num*4+2));
			CLEAR_BIT(GPIO_PORTB_PCTL_R,(pin_num*4+3));
			/*unlock port*/
			GPIO_PORTB_LOCK_R = 0x4C4F434B;
			/*direction input/output*/
			if(Direction==PIN_INPUT){
				CLEAR_BIT(GPIO_PORTB_DIR_R,pin_num);
			}else{
				SET_BIT(GPIO_PORTB_DIR_R,pin_num);
			}
			/*mode1 gpio/alternate function*/
			if(mode1==GPIO){
				CLEAR_BIT(GPIO_PORTB_AFSEL_R,pin_num);
			}
			else{
				SET_BIT(GPIO_PORTB_AFSEL_R,pin_num);
			}
			/*set connection pull up/pull down*/
			if(connection==PULLUP){
				SET_BIT(GPIO_PORTB_PUR_R,pin_num);  //enable pull up
				CLEAR_BIT(GPIO_PORTB_PDR_R,pin_num); //disable pull down
			}
			else if(connection==PULLDOWN){
				SET_BIT(GPIO_PORTB_PDR_R,pin_num);  //enable pull down
				CLEAR_BIT(GPIO_PORTB_PUR_R,pin_num);  //disable pull up
			}else{
				CLEAR_BIT(GPIO_PORTB_PDR_R,pin_num); //disable pull down
				CLEAR_BIT(GPIO_PORTB_PUR_R,pin_num);  //disable pull up
			}
			/*enable or disable digital function*/
			if(isDigital==DISABLE){
				CLEAR_BIT(GPIO_PORTB_DEN_R,pin_num);  //disable digital function
			}else{
				SET_BIT(GPIO_PORTB_DEN_R,pin_num);  //enable digital function
				GPIO_PORTB_AMSEL_R = 0x00;
			}
			SET_BIT(GPIO_PORTB_CR_R,pin_num);  //commit (enable write to GPIODEN,GPIOPUR,GPIOPDR)
			break;
		case PORTC_ID:
			/**/
			CLEAR_BIT(GPIO_PORTC_PCTL_R,(pin_num*4));
			CLEAR_BIT(GPIO_PORTC_PCTL_R,(pin_num*4+1));
			CLEAR_BIT(GPIO_PORTC_PCTL_R,(pin_num*4+2));
			CLEAR_BIT(GPIO_PORTC_PCTL_R,(pin_num*4+3));
			/*unlock port*/
			GPIO_PORTC_LOCK_R = 0x4C4F434B;
			/*direction input/output*/
			if(Direction==PIN_INPUT){
				CLEAR_BIT(GPIO_PORTC_DIR_R,pin_num);
			}else{
				SET_BIT(GPIO_PORTC_DIR_R,pin_num);
			}
			/*mode1 gpio/alternate function*/
			if(mode1==GPIO){
				CLEAR_BIT(GPIO_PORTC_AFSEL_R,pin_num);
			}
			else{
				SET_BIT(GPIO_PORTC_AFSEL_R,pin_num);
			}
			/*set connection pull up/pull down*/
			if(connection==PULLUP){
				SET_BIT(GPIO_PORTC_PUR_R,pin_num);  //enable pull up
				CLEAR_BIT(GPIO_PORTC_PDR_R,pin_num); //disable pull down
			}
			else if(connection==PULLDOWN){
				SET_BIT(GPIO_PORTC_PDR_R,pin_num);  //enable pull down
				CLEAR_BIT(GPIO_PORTC_PUR_R,pin_num);  //disable pull up
			}else{
				CLEAR_BIT(GPIO_PORTC_PDR_R,pin_num); //disable pull down
				CLEAR_BIT(GPIO_PORTC_PUR_R,pin_num);  //disable pull up
			}
			/*enable or disable digital function*/
			if(isDigital==DISABLE){
				CLEAR_BIT(GPIO_PORTC_DEN_R,pin_num);  //disable pull up
			}else{
				SET_BIT(GPIO_PORTC_DEN_R,pin_num);  //enable pull up
				GPIO_PORTC_AMSEL_R = 0x00;
			}
			SET_BIT(GPIO_PORTC_CR_R,pin_num);  //commit (enable write to GPIODEN,GPIOPUR,GPIOPDR)
			break;
		case PORTD_ID:
			/**/
			CLEAR_BIT(GPIO_PORTD_PCTL_R,(pin_num*4));
			CLEAR_BIT(GPIO_PORTD_PCTL_R,(pin_num*4+1));
			CLEAR_BIT(GPIO_PORTD_PCTL_R,(pin_num*4+2));
			CLEAR_BIT(GPIO_PORTD_PCTL_R,(pin_num*4+3));
			/*unlock port*/
			GPIO_PORTD_LOCK_R = 0x4C4F434B;
			/*direction input/output*/
			if(Direction==PIN_INPUT){
				CLEAR_BIT(GPIO_PORTD_DIR_R,pin_num);
			}else{
				SET_BIT(GPIO_PORTD_DIR_R,pin_num);
			}
			/*mode1 gpio/alternate function*/
			if(mode1==GPIO){
				CLEAR_BIT(GPIO_PORTD_AFSEL_R,pin_num);
			}
			else{
				SET_BIT(GPIO_PORTD_AFSEL_R,pin_num);
			}
			/*set connection pull up/pull down*/
			if(connection==PULLUP){
				SET_BIT(GPIO_PORTD_PUR_R,pin_num);  //enable pull up
				CLEAR_BIT(GPIO_PORTD_PDR_R,pin_num); //disable pull down
			}
			else if(connection==PULLDOWN){
				SET_BIT(GPIO_PORTD_PDR_R,pin_num);  //enable pull down
				CLEAR_BIT(GPIO_PORTD_PUR_R,pin_num);  //disable pull up
			}else{
				CLEAR_BIT(GPIO_PORTD_PDR_R,pin_num); //disable pull down
				CLEAR_BIT(GPIO_PORTD_PUR_R,pin_num);  //disable pull up
			}
			/*enable or disable digital function*/
			if(isDigital==DISABLE){
				CLEAR_BIT(GPIO_PORTD_DEN_R,pin_num);  //disable pull up
			}else{
				SET_BIT(GPIO_PORTD_DEN_R,pin_num);  //enable pull up
				GPIO_PORTD_AMSEL_R = 0x00;
			}
			SET_BIT(GPIO_PORTD_CR_R,pin_num);  //commit (enable write to GPIODEN,GPIOPUR,GPIOPDR)
			break;
		case PORTE_ID:
			/**/
			CLEAR_BIT(GPIO_PORTE_PCTL_R,(pin_num*4));
			CLEAR_BIT(GPIO_PORTE_PCTL_R,(pin_num*4+1));
			CLEAR_BIT(GPIO_PORTE_PCTL_R,(pin_num*4+2));
			CLEAR_BIT(GPIO_PORTE_PCTL_R,(pin_num*4+3));
			/*unlock port*/
			GPIO_PORTE_LOCK_R = 0x4C4F434B;
			/*direction input/output*/
			if(Direction==PIN_INPUT){
				CLEAR_BIT(GPIO_PORTE_DIR_R,pin_num);
			}else{
				SET_BIT(GPIO_PORTE_DIR_R,pin_num);
			}
			/*mode1 gpio/alternate function*/
			if(mode1==GPIO){
				CLEAR_BIT(GPIO_PORTE_AFSEL_R,pin_num);
			}
			else{
				SET_BIT(GPIO_PORTE_AFSEL_R,pin_num);
			}
			/*set connection pull up/pull down*/
			if(connection==PULLUP){
				SET_BIT(GPIO_PORTE_PUR_R,pin_num);  //enable pull up
				CLEAR_BIT(GPIO_PORTE_PDR_R,pin_num); //disable pull down
			}
			else if(connection==PULLDOWN){
				SET_BIT(GPIO_PORTE_PDR_R,pin_num);  //enable pull down
				CLEAR_BIT(GPIO_PORTE_PUR_R,pin_num);  //disable pull up
			}else{
				CLEAR_BIT(GPIO_PORTE_PDR_R,pin_num); //disable pull down
				CLEAR_BIT(GPIO_PORTE_PUR_R,pin_num);  //disable pull up
			}
			/*enable or disable digital function*/
			if(isDigital==DISABLE){
				CLEAR_BIT(GPIO_PORTE_DEN_R,pin_num);  //disable pull up
			}else{
				SET_BIT(GPIO_PORTE_DEN_R,pin_num);  //enable pull up
				GPIO_PORTE_AMSEL_R = 0x00;
			}
			SET_BIT(GPIO_PORTE_CR_R,pin_num);  //commit (enable write to GPIODEN,GPIOPUR,GPIOPDR)
			break;
		case PORTF_ID:
			/**/
			CLEAR_BIT(GPIO_PORTF_PCTL_R,(pin_num*4));
			CLEAR_BIT(GPIO_PORTF_PCTL_R,(pin_num*4+1));
			CLEAR_BIT(GPIO_PORTF_PCTL_R,(pin_num*4+2));
			CLEAR_BIT(GPIO_PORTF_PCTL_R,(pin_num*4+3));
			/*unlock port*/
			GPIO_PORTF_LOCK_R = 0x4C4F434B;
			/*direction input/output*/
			if(Direction==PIN_INPUT){
				CLEAR_BIT(GPIO_PORTF_DIR_R,pin_num);
			}else{
				SET_BIT(GPIO_PORTF_DIR_R,pin_num);
			}
			/*mode1 gpio/alternate function*/
			if(mode1==GPIO){
				CLEAR_BIT(GPIO_PORTF_AFSEL_R,pin_num);
			}
			else{
				SET_BIT(GPIO_PORTF_AFSEL_R,pin_num);
			}
			/*set connection pull up/pull down*/
			if(connection==PULLUP){
				SET_BIT(GPIO_PORTF_PUR_R,pin_num);  //enable pull up
				CLEAR_BIT(GPIO_PORTF_PDR_R,pin_num); //disable pull down
			}
			else if(connection==PULLDOWN){
				SET_BIT(GPIO_PORTF_PDR_R,pin_num);  //enable pull down
				CLEAR_BIT(GPIO_PORTF_PUR_R,pin_num);  //disable pull up
			}else{
				CLEAR_BIT(GPIO_PORTF_PDR_R,pin_num); //disable pull down
				CLEAR_BIT(GPIO_PORTF_PUR_R,pin_num);  //disable pull up
			}
			/*enable or disable digital function*/
			if(isDigital==DISABLE){
				CLEAR_BIT(GPIO_PORTF_DEN_R,pin_num);  //disable pull up
			}else{
				SET_BIT(GPIO_PORTF_DEN_R,pin_num);  //enable pull up
				GPIO_PORTF_AMSEL_R = 0x00;
			}
			SET_BIT(GPIO_PORTF_CR_R,pin_num);  //commit (enable write to GPIODEN,GPIOPUR,GPIOPDR)
		}
	}
}


void GPIO_Deinit(uint8 port_num){
	if((port_num >= NUM_OF_PORTS))
	{
		/* Do Nothing */
	}
	else{
		CLEAR_BIT(SYSCTL_RCGC2_R,port_num); //enable clock
	}
}

/*
 * Description :
 * Write the value Logic High or Logic Low on the required pin.
 * If the input port number or pin number are not correct, The function will not handle the request.
 * If the pin is input, this function will enable/disable the internal pull-up resistor.
 */
void GPIO_writePin(uint8 port_num, uint8 pin_num, uint8 value){
	/*
	 * Check if the input port number is greater than NUM_OF_PINS_PER_PORT value.
	 * Or if the input pin number is greater than NUM_OF_PINS_PER_PORT value.
	 * In this case the input is not valid port/pin number
	 */
	if((pin_num >= NUM_OF_PINS_PER_PORT) || (port_num >= NUM_OF_PORTS))
	{
		/* Do Nothing */
	}
	else{
		switch(port_num){
			case PORTA_ID:
				if(value==LOGIC_HIGH){
					SET_BIT(GPIO_PORTA_DATA_R,pin_num);
				}else{
					CLEAR_BIT(GPIO_PORTA_DATA_R,pin_num);
				}
				break;
			case PORTB_ID:
				if(value==LOGIC_HIGH){
					SET_BIT(GPIO_PORTB_DATA_R,pin_num);
				}else{
					CLEAR_BIT(GPIO_PORTB_DATA_R,pin_num);
				}
				break;
			case PORTC_ID:
				if(value==LOGIC_HIGH){
					SET_BIT(GPIO_PORTC_DATA_R,pin_num);
				}else{
					CLEAR_BIT(GPIO_PORTC_DATA_R,pin_num);
				}
				break;
			case PORTD_ID:
				if(value==LOGIC_HIGH){
					SET_BIT(GPIO_PORTD_DATA_R,pin_num);
				}else{
					CLEAR_BIT(GPIO_PORTD_DATA_R,pin_num);
				}
				break;
			case PORTE_ID:
				if(value==LOGIC_HIGH){
					SET_BIT(GPIO_PORTE_DATA_R,pin_num);
				}else{
					CLEAR_BIT(GPIO_PORTE_DATA_R,pin_num);
				}
				break;
			case PORTF_ID:
				if(value==LOGIC_HIGH){
					SET_BIT(GPIO_PORTF_DATA_R,pin_num);
				}else{
					CLEAR_BIT(GPIO_PORTF_DATA_R,pin_num);
				}
				break;
		}
	}
}

/*
 * Description :
 * Read and return the value for the required pin, it should be Logic High or Logic Low.
 * If the input port number or pin number are not correct, The function will return Logic Low.
 */
uint8 GPIO_readPin(uint8 port_num, uint8 pin_num){
	/*
	 * Check if the input port number is greater than NUM_OF_PINS_PER_PORT value.
	 * Or if the input pin number is greater than NUM_OF_PINS_PER_PORT value.
	 * In this case the input is not valid port/pin number
	 */
	uint8 value = LOGIC_LOW;
	if((pin_num >= NUM_OF_PINS_PER_PORT) || (port_num >= NUM_OF_PORTS))
	{
		/* Do Nothing */
	}
	else{
		switch(port_num){
			case PORTA_ID:
				value = GET_BIT(GPIO_PORTA_DATA_R,pin_num);
				break;
			case PORTB_ID:
				value = GET_BIT(GPIO_PORTB_DATA_R,pin_num);
				break;
			case PORTC_ID:
				value = GET_BIT(GPIO_PORTC_DATA_R,pin_num);
				break;
			case PORTD_ID:
				value = GET_BIT(GPIO_PORTD_DATA_R,pin_num);
				break;
			case PORTE_ID:
				value = GET_BIT(GPIO_PORTE_DATA_R,pin_num);
				break;
			case PORTF_ID:
				value = GET_BIT(GPIO_PORTF_DATA_R,pin_num);
				break;
		}
	}
	return value;
}


 
 
 
 /*
 * Description :
 * Write the value on the required port.
 * If any pin in the port is output pin the value will be written.
 * If any pin in the port is input pin this will activate/deactivate the internal pull-up resistor.
 * If the input port number is not correct, The function will not handle the request.
 */
void GPIO_writePort(uint8 port_num, uint8 value)
{
	/*
	 * Check if the input number is greater than NUM_OF_PORTS value.
	 * In this case the input is not valid port number
	 */
	
	switch(port_num){
		case PORTA_ID:
			GPIO_PORTA_DATA_R = value;
			break;
		case PORTB_ID:
			GPIO_PORTB_DATA_R = value;
			break;
		case PORTC_ID:
			GPIO_PORTC_DATA_R = value;
			break;
		case PORTD_ID:
			GPIO_PORTD_DATA_R = value;
			break;
		case PORTE_ID:
			GPIO_PORTE_DATA_R = value;
			break;
		case PORTF_ID:
			GPIO_PORTF_DATA_R = value;
			break;
	}
	
}

/*
 * Description :
 * Read and return the value of the required port.
 * If the input port number is not correct, The function will return ZERO value.
 */
uint8 GPIO_readPort(uint8 port_num)
{
	uint8 value = LOGIC_LOW;

	/*
	 * Check if the input number is greater than NUM_OF_PORTS value.
	 * In this case the input is not valid port number
	 */
	if(port_num >= NUM_OF_PORTS)
	{
		/* Do Nothing */
	}
	else
	{
		/* Read the port value as required */
		switch(port_num)
		{
		case PORTA_ID:
			value = GPIO_PORTA_DATA_R;
			break;
		case PORTB_ID:
			value = GPIO_PORTB_DATA_R;
			break;
		case PORTC_ID:
			value = GPIO_PORTC_DATA_R;
			break;
		case PORTD_ID:
			value = GPIO_PORTD_DATA_R;
			break;
		case PORTE_ID:
			value = GPIO_PORTE_DATA_R;
			break;
		case PORTF_ID:
			value = GPIO_PORTF_DATA_R;
			break;
		}
	}

	return value;
}
