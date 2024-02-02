#ifndef TIM1_INTERFACE_H
#define TIM1_INTERFACE_H

#include "../Common/std_types.h"

#define MASK_16_BITS 0xFFFF
#define TIM1_CR1_PWM_MASK 0b0011100000
#define TIM1_CCER_PWM_MASK 0b1001
#define TIM1_BDTR_PWM_MASK 0b10000000
#define TIM1_CCMR1_PWM_MASK 0b01111000

void TIM1_voidInit();

void TIM1_voidStart();

void TIM1_voidStop();

void TIM1_voidSetTimerValue(u16 value);

u16 TIM1_u16GetTimerValue();

void TIM1_voidGeneratePwm(u8 channel, f32 dutyCycle);

#endif
