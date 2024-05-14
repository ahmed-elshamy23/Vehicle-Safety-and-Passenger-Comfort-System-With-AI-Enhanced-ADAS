#ifndef TIM1_PRIVATE_H
#define TIM1_PRIVATE_H

#include "../Common/std_types.h"

#define TIM1_CR1 *((volatile u32 *)(0x40012C00))
#define TIM1_CR2 *((volatile u32 *)(0x40012C04))
#define TIM1_SMCR *((volatile u32 *)(0x40012C08))
#define TIM1_SR *((volatile u32 *)(0x40012C10))
#define TIM1_EGR *((volatile u32 *)(0x40012C14))
#define TIM1_CCMR1 *((volatile u32 *)(0x40012C18))
#define TIM1_CCMR2 *((volatile u32 *)(0x40012C1C))
#define TIM1_CCER *((volatile u32 *)(0x40012C20))
#define TIM1_CNT *((volatile u32 *)(0x40012C24))
#define TIM1_PSC *((volatile u32 *)(0x40012C28))
#define TIM1_ARR *((volatile u32 *)(0x40012C2C))
#define TIM1_RCR *((volatile u32 *)(0x40012C30))
#define TIM1_CCR1 *((volatile u32 *)(0x40012C34))
#define TIM1_CCR2 *((volatile u32 *)(0x40012C38))
#define TIM1_CCR3 *((volatile u32 *)(0x40012C3C))
#define TIM1_CCR4 *((volatile u32 *)(0x40012C40))
#define TIM1_BDTR *((volatile u32 *)(0x40012C44))

#define ENABLE_BIT 0

#define PWM_CHANNEL_1 1
#define PWM_CHANNEL_2 2
#define PWM_CHANNEL_3 3
#define PWM_CHANNEL_4 4

#define TIM1_MAX_VALUE 65536

#endif
