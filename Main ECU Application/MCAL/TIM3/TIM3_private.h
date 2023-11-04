#ifndef TIM3_PRIVATE_H
#define TIM3_PRIVATE_H
#include "../../Common/std_types.h"

#define TIM3_CR1 *((volatile u32 *)(0x40000400))
#define TIM3_CR2 *((volatile u32 *)(0x40000404))
#define TIM3_SMCR *((volatile u32 *)(0x40000408))
#define TIM3_DIER *((volatile u32 *)(0x4000040C))
#define TIM3_SR *((volatile u32 *)(0x40000410))
#define TIM3_EGR *((volatile u32 *)(0x40000414))
#define TIM3_CCMR1 *((volatile u32 *)(0x40000418))
#define TIM3_CCMR2 *((volatile u32 *)(0x4000041C))
#define TIM3_CCER *((volatile u32 *)(0x40000420))
#define TIM3_CNT *((volatile u32 *)(0x40000424))
#define TIM3_PSC *((volatile u32 *)(0x40000428))
#define TIM3_ARR *((volatile u32 *)(0x4000042C))
#define TIM3_RCR *((volatile u32 *)(0x40000430))
#define TIM3_CCR1 *((volatile u32 *)(0x40000434))
#define TIM3_CCR2 *((volatile u32 *)(0x40000438))
#define TIM3_CCR3 *((volatile u32 *)(0x4000043C))
#define TIM3_CCR4 *((volatile u32 *)(0x40000440))
#define TIM3_BDTR *((volatile u32 *)(0x40000444))

#define ENABLE_BIT 0

#endif