#ifndef LED_INTERFACE_H
#define LED_INTERFACE_H

#include "../../Common/std_types.h"

#define ON 0
#define OFF 1

void LED_voidInit(u8 portNumber, u8 pinNumber);

void LED_voidState(u8 portNumber, u8 pinNumber, u8 value);

#endif