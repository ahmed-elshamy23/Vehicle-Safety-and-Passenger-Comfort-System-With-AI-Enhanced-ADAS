#ifndef SWITCH_INTERFACE_H
#define SWITCH_INTERFACE_H

#include "../Common/std_types.h"
#include "DIO_interface.h"

#define PULLUP_RESISTOR 0
#define PULLDOWN_RESISTOR 1

void SWITCH_voidInit(u8 portNumber, u8 pinNumber, u8 resistorState);

u8 SWITCH_u8SwitchIsOn(u8 portNumber, u8 pinNumber);

#endif
