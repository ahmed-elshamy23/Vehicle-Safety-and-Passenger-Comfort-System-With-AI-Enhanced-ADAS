#ifndef TIM2_INTERFACE_H
#define TIM2_INTERFACE_H

#include "../../Common/std_types.h"

void TIM2_voidInit();

void TIM2_voidStart();

void TIM2_voidStop();

void TIM2_voidSetTimerValue(u16 value);

u16 TIM2_u16GetTimerValue();

void TIM2_voidDelay(f32 delayTime);

#endif