#include "TIM1_interface.h"
#include "TIM1_config.h"
#include "TIM1_private.h"
#include "../../Common/std_types.h"
#include "../../Common/bit_math.h"

void TIM1_voidInit()
{
    TIM1_PSC |= TIM1_PRESCALER - 1;
    TIM1_CR1 |= TIM1_CR1_PWM_MASK;
    TIM1_CCER |= TIM1_CCER_PWM_MASK;
    TIM1_BDTR |= TIM1_BDTR_PWM_MASK;
    TIM1_CCMR1 |= TIM1_CCMR1_PWM_MASK;
    TIM1_CCMR2 |= TIM1_CCMR2_PWM_MASK;
    TIM1_ARR |= MASK_16_BITS;
}

void TIM1_voidStart()
{
    SET_BIT(TIM1_CR1, ENABLE_BIT);
}

void TIM1_voidStop()
{
    CLR_BIT(TIM1_CR1, ENABLE_BIT);
}

void TIM1_voidSetTimerValue(u16 value)
{
    TIM1_CNT |= value;
}

u16 TIM1_u16GetTimerValue()
{
    return TIM1_CNT & MASK_16_BITS;
}

void TIM1_voidGeneratePwm(u8 channel, f32 dutyCycle)
{
    u16 compareValue = TIM1_MAX_VALUE * (1 - dutyCycle) - 1;
    switch (channel)
    {
    case PWM_CHANNEL_1:
        TIM1_CCR1 = compareValue;
        break;
    case PWM_CHANNEL_2:
        TIM1_CCR2 = compareValue;
        break;
    case PWM_CHANNEL_3:
        TIM1_CCR3 = compareValue;
        break;
    case PWM_CHANNEL_4:
        TIM1_CCR4 = compareValue;
    }
}