#ifndef DC_INTERFACE_H
#define DC_INTERFACE_H

#include "../../Common/std_types.h"

void DC_voidInit();

void DC_voidSetSpeed(u8 frontRightSpeed, u8 frontLeftSpeed, u8 rearRightSpeed, u8 rearLeftSpeed);

void DC_voidStart(u8 motorNumber);

void DC_voidStop(u8 motorNumber);

#endif