#ifndef TIM3_INTERFACE_H
#define TIM3_INTERFACE_H

#include "../../Common/std_types.h"

#define MASK_16_BITS 0xFFFF
#define TIM3_CR1_NORMAL_MASK 0x0080
#define TIM3_DIER_NORMAL_MASK 0x0001

#define CLOCK 36000000UL

void TIM3_voidInit();

void TIM3_voidStart();

void TIM3_voidStop();

void TIM3_voidSetTimerValue(u16 value);

u16 TIM3_u16GetTimerValue();

void TIM3_voidDelay(f32 delayTime);

#endif