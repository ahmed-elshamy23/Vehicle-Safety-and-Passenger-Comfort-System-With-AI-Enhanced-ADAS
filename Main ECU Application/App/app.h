#ifndef APP_H
#define APP_H

#define ACC_THRESHOLD 5.0f
#define AEB_THRESHOLD 2.0f

#define INITIAL_SPEED 0.1f

#define DRIVER_1 1
#define DRIVER_2 2
#define DRIVER_3 3

#define DRIVER_ASLEEP 0xEE

void appInit();

void applyDriverProfile();

void getDistance();

void updateSpeedAndDirection();

void checkReedSwitch();

void receiveUartFrame();

#endif