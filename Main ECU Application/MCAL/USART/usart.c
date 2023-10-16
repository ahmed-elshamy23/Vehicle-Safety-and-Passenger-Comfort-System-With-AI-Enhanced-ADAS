#include "usart.h"
#include "usart_reg.h"
#include "../common/bit_math.h"

void usart_init()
{
    USART_CR1 = USART_CR1_MASK;
    USART_BRR = USART_BAUD_9600_MASK;
    USART_RX_ENABLE();
}

u8 usart_receiveData()
{
    if (GET_BIT(USART_SR, RXNE_BIT))
        return USART_DR << 24;
    else
        return EMPTY_DATA;
}