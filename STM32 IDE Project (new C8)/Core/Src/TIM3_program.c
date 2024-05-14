#include "TIM3_interface.h"
#include "TIM3_config.h"
#include "TIM3_private.h"
#include "stm32f1xx_hal_tim.h"
#include "../common/std_types.h"
#include "../common/bit_math.h"

TIM_HandleTypeDef htim33;
TIM_ClockConfigTypeDef sClockSourceConfig3 = {0};
TIM_MasterConfigTypeDef sMasterConfig3 = {0};

void TIM3_voidInit()
{
    htim33.Instance = TIM3;
    htim33.Init.Prescaler = 72;
    htim33.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim33.Init.Period = 65535;
    htim33.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim33.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    HAL_TIM_Base_Init(&htim33);
    sClockSourceConfig3.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
    HAL_TIM_ConfigClockSource(&htim33, &sClockSourceConfig3);
    sMasterConfig3.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig3.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    HAL_TIMEx_MasterConfigSynchronization(&htim33, &sMasterConfig3);
}

void TIM3_voidStart()
{
    HAL_TIM_Base_Start(&htim33);
}

void TIM3_voidStop()
{
    HAL_TIM_Base_Stop(&htim33);
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
