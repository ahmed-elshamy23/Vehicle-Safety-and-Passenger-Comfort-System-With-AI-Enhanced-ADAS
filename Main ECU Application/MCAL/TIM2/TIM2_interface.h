#ifndef TIM2_INTERFACE_H
#define TIM2_INTERFACE_H

#include "TIM2_private.h"
#include "TIM2_config.h"
#include "../../Common/bit_math.h"

/******************************************************************************
 *									TIMERS	                				  *
 *******************************************************************************/
#define TIMER2 0
#define TIMER3 1
#define TIMER4 2
#define TIMER5 3
#define COUNTER_EN_BIT 0
#define COUNTER_DISABLE_BIT 0
#define PWM_CHANNEL_1 1
#define PWM_CHANNEL_2 2
#define PWM_CHANNEL_3 3
#define PWM_CHANNEL_4 4

/******************************************************************************
 *									MASKED VALUE	                				  *
 *******************************************************************************/
#define TIM2_CR1_PWM_MASK 0xC0
#define TIM2_CCMR1_PWM_MASK 0x7878
#define TIM2_CCMR2_PWM_MASK 0x7878
#define TIM2_CCER_PWM_MASK 0x1111

/******************************************************************************
 *									PINS for channel	                 				  *
 *******************************************************************************/
// PORTA   PIN0
// PORTA   PIN1
// PORTA   PIN2
// PORTA   PIN3

/******************************************************************************
 *									APIS	                				  *
 *******************************************************************************/
void TIM2_voidInit();

void TIM2_voidStart();

void TIM2_voidStop();

void TIM2_voidSetTimerValue(u16 value);

u16 TIM2_u16GetTimerValue();

void TIM2_voidGeneratePwm(u8 channel, f32 dutyCycle);

#endif