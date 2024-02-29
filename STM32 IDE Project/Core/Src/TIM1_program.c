#include "TIM1_interface.h"
#include "TIM1_private.h"
#include "stm32f1xx_hal_tim.h"
#include "../Common/std_types.h"
#include "../Common/bit_math.h"

TIM_HandleTypeDef htim11;
TIM_ClockConfigTypeDef sClockSourceConfig = {0};
TIM_MasterConfigTypeDef sMasterConfig = {0};
TIM_OC_InitTypeDef sConfigOC = {0};
TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig = {0};

void TIM1_voidInit()
{
    htim11.Instance = TIM1;
    htim11.Init.Prescaler = 16;
    htim11.Init.CounterMode = TIM_COUNTERMODE_CENTERALIGNED1;
    htim11.Init.Period = 45000;
    htim11.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    htim11.Init.RepetitionCounter = 0;
    htim11.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
    HAL_TIM_Base_Init(&htim11);
    sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
    HAL_TIM_ConfigClockSource(&htim11, &sClockSourceConfig);
    HAL_TIM_PWM_Init(&htim11);
    sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
    sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
    HAL_TIMEx_MasterConfigSynchronization(&htim11, &sMasterConfig);
    sConfigOC.OCMode = TIM_OCMODE_PWM2;
    sConfigOC.Pulse = 0;
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
    sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
    sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
    HAL_TIM_PWM_ConfigChannel(&htim11, &sConfigOC, TIM_CHANNEL_1);
    sBreakDeadTimeConfig.OffStateRunMode = TIM_OSSR_DISABLE;
    sBreakDeadTimeConfig.OffStateIDLEMode = TIM_OSSI_DISABLE;
    sBreakDeadTimeConfig.LockLevel = TIM_LOCKLEVEL_OFF;
    sBreakDeadTimeConfig.DeadTime = 0;
    sBreakDeadTimeConfig.BreakState = TIM_BREAK_DISABLE;
    sBreakDeadTimeConfig.BreakPolarity = TIM_BREAKPOLARITY_HIGH;
    sBreakDeadTimeConfig.AutomaticOutput = TIM_AUTOMATICOUTPUT_DISABLE;
    HAL_TIMEx_ConfigBreakDeadTime(&htim11, &sBreakDeadTimeConfig);
    HAL_TIM_MspPostInit(&htim11);
}

void TIM1_voidStart()
{
    HAL_TIM_PWM_Start(&htim11, TIM_CHANNEL_1);
}

void TIM1_voidStop()
{
    HAL_TIM_PWM_Stop(&htim11, TIM_CHANNEL_1);
}

void TIM1_voidSetTimerValue(u16 value)
{
    TIM1_CNT = value;
}

u16 TIM1_u16GetTimerValue()
{
    return TIM1_CNT & MASK_16_BITS;
}

void TIM1_voidGeneratePwm(u8 channel, f32 dutyCycle)
{
    u16 compareValue = 45000 * (1 - dutyCycle) - 1;
    switch (channel)
    {
    case PWM_CHANNEL_1:
        sConfigOC.Pulse = compareValue;
        HAL_TIM_PWM_ConfigChannel(&htim11, &sConfigOC, TIM_CHANNEL_1);
        break;
    }
}
