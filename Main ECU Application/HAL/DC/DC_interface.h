#ifndef DC_INTERFACE_H
#define DC_INTERFACE_H

#include "../../Common/std_types.h"

void DC_voidInit();

void DC_voidSetSpeed(u8 pwmChannel, u8 speed);

void DC_voidStart(u8 motorNumber);

void DC_voidStop(u8 motorNumber);

#endif