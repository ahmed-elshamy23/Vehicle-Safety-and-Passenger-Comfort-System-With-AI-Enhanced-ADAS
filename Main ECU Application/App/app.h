#ifndef APP_H
#define APP_H

#define ACC_THRESHOLD 2.5f
#define AEB_THRESHOLD 0.8f

#define INITIAL_SPEED 10
#define MAX_SPEED 50

#define DRIVER_1 1
#define DRIVER_2 2
#define DRIVER_3 3

#define DRIVER_ASLEEP 0xEE

void appInit();

void applyDriverProfile();

void getDistance();

void updateSpeedAndDirection();

void receiveUartFrame();

#endif