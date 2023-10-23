#ifndef TIM1_INTERFACE_H
#define TIM1_INTERFACE_H

#include "../../Common/std_types.h"

void TIM1_voidInit();

void TIM1_voidStart();

void TIM1_voidStop();

void TIM1_voidSetTimerValue(u16 value);

u16 TIM1_u16GetTimerValue();

void TIM1_voidGeneratePwm(u8 channel, f32 dutyCycle);

#endif