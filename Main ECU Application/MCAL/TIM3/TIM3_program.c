#include "TIM3_interface.h"
#include "TIM3_config.h"
#include "TIM3_private.h"
#include "../../common/std_types.h"
#include "../../common/bit_math.h"

void TIM3_voidInit()
{
    TIM3_PSC |= TIM3_PRESCALER - 1;
    TIM3_CR1 |= TIM3_CR1_NORMAL_MASK;
    TIM3_ARR |= MASK_16_BITS;
    TIM3_DIER |= TIM3_DIER_NORMAL_MASK; // set UIE Update interrupt enable
}

void TIM3_voidStart()
{
    SET_BIT(TIM3_CR1, ENABLE_BIT);
}

void TIM3_voidStop()
{
    CLR_BIT(TIM3_CR1, ENABLE_BIT);
}

void TIM3_voidSetTimerValue(u16 value)
{
    TIM3_CNT = value;
}

u16 TIM3_u16GetTimerValue()
{
    return TIM3_CNT & MASK_16_BITS;
}

void TIM3_voidDelay(f32 delayTime)
{
    f32 tickTime = TIM3_PRESCALER / (f32)CLOCK;
    f32 overflowTime = 65536 * tickTime;
    if (delayTime >= overflowTime)
    {
        u32 numOfOverflows = delayTime / overflowTime, n = 0;
        f32 fraction = delayTime - numOfOverflows * overflowTime;
        TIM3_voidSetTimerValue(0);
        while (n < numOfOverflows)
        {
            TIM3_voidStart();
            while (!GET_BIT(TIM3_SR, 0))
                ;
            TIM3_voidStop();
            CLR_BIT(TIM3_SR, 0);
            n++;
        }
        if (fraction)
        {
            TIM3_voidSetTimerValue(65536 - 65536 * (fraction / 10));
            TIM3_voidStart();
            while (!GET_BIT(TIM3_SR, 0))
                ;
            TIM3_voidStop();
            CLR_BIT(TIM3_SR, 0);
        }
    }
    else
    {
        TIM3_voidSetTimerValue((overflowTime - delayTime) / tickTime);
        TIM3_voidStart();
        while (!GET_BIT(TIM3_SR, 0))
            ;
        TIM3_voidStop();
        CLR_BIT(TIM3_SR, 0);
    }
}