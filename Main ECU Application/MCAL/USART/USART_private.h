#ifndef USART_PRIVATE_H
#define USART_PRIVATE_H

#define USART_SR *((volatile u32 *)(0x40003800))
#define USART_DR *((volatile u32 *)(0x40003804))
#define USART_BRR *((volatile u32 *)(0x40003808))
#define USART_CR1 *((volatile u32 *)(0x4000380C))

#define USART_CR1_MASK ((u32)0b10010000100000)
#define USART_BAUD_9600_MASK ((u32)0b111010100110)
#define USART_RX_ENABLE() (USART_CR1 |= 0b100)

#define RXNE_BIT 5

#endif