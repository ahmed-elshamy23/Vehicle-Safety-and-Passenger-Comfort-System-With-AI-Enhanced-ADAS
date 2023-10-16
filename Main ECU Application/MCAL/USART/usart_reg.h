#ifndef USART_REG_H
#define USART_REG_H

#define USART_SR *((volatile u32 *)(0x40013800))
#define USART_DR *((volatile u32 *)(0x40013804))
#define USART_BRR *((volatile u32 *)(0x40013808))
#define USART_CR1 *((volatile u32 *)(0x4001380C))

#define USART_CR1_MASK ((u32)0b10010000100000)
#define USART_BAUD_9600_MASK ((u32)0b111010100110)
#define USART_RX_ENABLE() (USART_CR1 |= 0b100)

#define RXNE_BIT 5

#endif