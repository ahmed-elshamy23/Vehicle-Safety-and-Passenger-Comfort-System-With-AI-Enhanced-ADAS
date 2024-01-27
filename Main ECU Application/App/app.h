#ifndef APP_H
#define APP_H

#define ACC_THRESHOLD 5.0f
#define AEB_THRESHOLD 2.0f

#define DRIVER_1 1
#define DRIVER_2 2
#define DRIVER_3 3

void appInit();

void applyDriverProfile();

void getDistance();

void updateSpeedAndDirection();

void receiveUartFrame();

#endif