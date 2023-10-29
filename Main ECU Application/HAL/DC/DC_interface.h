#ifndef DC_INTERFACE_H
#define DC_INTERFACE_H

#include "../../Common/std_types.h"

void DC_voidInit(u8 port, u8 in1Pin, u8 in2Pin, u8 in3Pin, u8 in4Pin, u8 pwmChannel);

void DC_voidSetSpeed(u8 pwmChannel, u8 speed);

#endif