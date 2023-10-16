#ifndef USART_H
#define USART_H

#include "../common/std_types.h"

#define EMPTY_DATA 0xFF

void usart_init();

u8 usart_receiveData();

#endif