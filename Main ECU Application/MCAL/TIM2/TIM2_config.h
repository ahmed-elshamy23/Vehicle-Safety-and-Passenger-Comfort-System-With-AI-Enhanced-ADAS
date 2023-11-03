#ifndef TIM2_CONFIG_H
#define TIM2_CONFIG_H

#define  SELECTED_TIMER    TIMER2
/********************* SELECT PRESCALER ********************/
#define PRESCALER      36
//in register of prescaler f=(f"sys"/ prescaler+1) prescaler=36-1=35
/******************************************************************************
  *									PINS for channels	                				  *
  *******************************************************************************/
  /*MDIO_voidSetPinDirection(DIOA, PIN0, OUTPUT_SPEED_2MHZ_AFPP);
	MDIO_voidSetPinDirection(DIOA, PIN1, OUTPUT_SPEED_2MHZ_AFPP);
	MDIO_voidSetPinDirection(DIOA, PIN2, OUTPUT_SPEED_2MHZ_AFPP);
	MDIO_voidSetPinDirection(DIOA, PIN3, OUTPUT_SPEED_2MHZ_AFPP);
*/

#endif