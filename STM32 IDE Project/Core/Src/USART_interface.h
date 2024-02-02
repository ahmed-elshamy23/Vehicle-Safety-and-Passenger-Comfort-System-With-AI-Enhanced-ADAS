#ifndef USART_INTERFACE_H
#define USART_INTERFACE_H

#include "../Common/std_types.h"

#define EMPTY_DATA 0xFF

void USART_voidInit();

u8 USART_u8ReceiveData();

#endif
