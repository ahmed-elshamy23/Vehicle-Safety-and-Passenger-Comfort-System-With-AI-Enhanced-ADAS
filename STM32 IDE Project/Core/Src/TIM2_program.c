#include "TIM2_interface.h"
#include "stm32f1xx_hal_tim.h"

TIM_HandleTypeDef htim22;
TIM_ClockConfigTypeDef sClockSourceConfig2 = {0};
TIM_MasterConfigTypeDef sMasterConfig2 = {0};
TIM_OC_InitTypeDef sConfigOC2 = {0};
TIM_BreakDeadTimeConfigTypeDef sBreakDeadTimeConfig2 = {0};

void TIM2_voidInit()
{
	TIM_ClockConfigTypeDef sClockSourceConfig = {0};
	TIM_MasterConfigTypeDef sMasterConfig = {0};
	htim22.Instance = TIM2;
	htim22.Init.Prescaler = 16;
	htim22.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim22.Init.Period = 45000;
	htim22.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim22.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_ENABLE;
	HAL_TIM_Base_Init(&htim22);
	sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	HAL_TIM_ConfigClockSource(&htim22, &sClockSourceConfig);
	HAL_TIM_PWM_Init(&htim22);
	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	HAL_TIMEx_MasterConfigSynchronization(&htim22, &sMasterConfig);
	sConfigOC2.OCMode = TIM_OCMODE_PWM2;
	sConfigOC2.Pulse = 0;
	sConfigOC2.OCPolarity = TIM_OCPOLARITY_HIGH;
	sConfigOC2.OCFastMode = TIM_OCFAST_DISABLE;
	HAL_TIM_PWM_ConfigChannel(&htim22, &sConfigOC2, TIM_CHANNEL_1);
	HAL_TIM_PWM_ConfigChannel(&htim22, &sConfigOC2, TIM_CHANNEL_2);
	HAL_TIM_PWM_ConfigChannel(&htim22, &sConfigOC2, TIM_CHANNEL_3);
	HAL_TIM_PWM_ConfigChannel(&htim22, &sConfigOC2, TIM_CHANNEL_4);
	HAL_TIM_MspPostInit(&htim22);
}

void TIM2_voidStart()
{
	HAL_TIM_PWM_Start(&htim22, TIM_CHANNEL_1);
	HAL_TIM_PWM_Start(&htim22, TIM_CHANNEL_2);
	HAL_TIM_PWM_Start(&htim22, TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim22, TIM_CHANNEL_4);
}

void TIM2_voidStop()
{
	HAL_TIM_PWM_Stop(&htim22, TIM_CHANNEL_1);
	HAL_TIM_PWM_Stop(&htim22, TIM_CHANNEL_2);
	HAL_TIM_PWM_Stop(&htim22, TIM_CHANNEL_3);
	HAL_TIM_PWM_Stop(&htim22, TIM_CHANNEL_4);
}

void TIM2_voidSetTimerValue(u16 value)
{
	TIMER_2->TIM_CNT &= 0x0000;
	TIMER_2->TIM_CNT = value;
}

u16 TIM2_u16GetTimerValue()
{
	return TIMER_2->TIM_CNT;
}

void TIM2_voidGeneratePwm(u8 channel, f32 dutyCycle)
{
	u16 compareValue = 45000 * (1 - dutyCycle) - 1;
	sConfigOC2.Pulse = compareValue;
	switch (channel)
	{
	case PWM_CHANNEL_1:
		HAL_TIM_PWM_ConfigChannel(&htim22, &sConfigOC2, TIM_CHANNEL_1);
		break;
	case PWM_CHANNEL_2:
		HAL_TIM_PWM_ConfigChannel(&htim22, &sConfigOC2, TIM_CHANNEL_2);
		break;
	case PWM_CHANNEL_3:
		HAL_TIM_PWM_ConfigChannel(&htim22, &sConfigOC2, TIM_CHANNEL_3);
		break;
	case PWM_CHANNEL_4:
		HAL_TIM_PWM_ConfigChannel(&htim22, &sConfigOC2, TIM_CHANNEL_4);
		break;
	}
}
