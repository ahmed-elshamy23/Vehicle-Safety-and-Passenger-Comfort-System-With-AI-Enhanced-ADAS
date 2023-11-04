#ifndef SERVO_INTERFACE_H
#define SERVO_INTERFACE_H

#include "../../Common/std_types.h"

void SERVO_voidInit();

void SERVO_voidSetAngle(u8 servoNumber, u16 angle);

#endif