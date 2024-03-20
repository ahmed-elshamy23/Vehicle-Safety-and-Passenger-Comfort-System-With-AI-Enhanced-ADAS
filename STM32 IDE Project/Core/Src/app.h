#ifndef APP_H
#define APP_H

#define ACC_THRESHOLD 1.0f
#define AEB_THRESHOLD 0.5f

#define INITIAL_ANGLE 90
#define INITIAL_SPEED 30
#define MAX_SPEED 60

#define DRIVER_1 191
#define DRIVER_2 192
#define DRIVER_3 193

#define DRIVER_ASLEEP 200

void appInit();

void applyDriverProfile();

void getDistance();

void updateSpeedAndDirection();

void receiveUartFrame();

#endif
