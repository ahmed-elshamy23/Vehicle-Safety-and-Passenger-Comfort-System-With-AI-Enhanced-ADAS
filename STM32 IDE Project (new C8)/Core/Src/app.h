#ifndef APP_H
#define APP_H

#define ACC_THRESHOLD 1.0f
#define AEB_THRESHOLD 0.25f

#define INITIAL_ANGLE 90
#define INITIAL_SPEED 30
#define MAX_SPEED 15

#define DRIVER_1 123
#define DRIVER_2 124
#define DRIVER_3 125

#define DRIVER_ASLEEP 126

void appInit();

void applyDriverProfile();

void getDistance();

void updateSpeedAndDirection();

void receiveUartFrame();

void steeringControl();

#endif
