#ifndef TIM3_INTERFACE_H
#define TIM3_INTERFACE_H

#include "../../Common/std_types.h"

void TIM3_voidInit();

void TIM3_voidStart();

void TIM3_voidStop();

void TIM3_voidSetTimerValue(u16 value);

u16 TIM3_u16GetTimerValue();

void TIM3_voidDelay(f32 delayTime);

#endif