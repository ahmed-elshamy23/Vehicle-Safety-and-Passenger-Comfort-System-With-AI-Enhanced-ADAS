#include "USART_interface.h"
#include "USART_private.h"
#include "../../Common/bit_math.h"

void USART_voidInit()
{
    USART_CR1 = USART_CR1_MASK;
    USART_BRR = USART_BAUD_9600_MASK;
    USART_RX_ENABLE();
}

u8 USART_u8ReceiveData()
{
    if (GET_BIT(USART_SR, RXNE_BIT))
        return USART_DR & 0xFF;
    else
        return EMPTY_DATA;
}