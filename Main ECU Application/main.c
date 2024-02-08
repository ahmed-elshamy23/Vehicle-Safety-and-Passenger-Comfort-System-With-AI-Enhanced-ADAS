#include "App/app.h"
#include "Services/FreeRTOS.h"
#include "Services/task.h"

void main()
{
    appInit();
    applyDriverProfile();
    DC_voidSetSpeed(INITIAL_SPEED);
    DC_voidStart();

    xTaskCreate(getDistance, "Measuring Distance", configMINIMAL_STACK_SIZE, NULL, 3, NULL);
    xTaskCreate(updateSpeedAndDirection, "Managing AEB and ACC", configMINIMAL_STACK_SIZE, NULL, 2, NULL);
    xTaskCreate(receiveUartFrame, "Receiving Frames from ESP32", configMINIMAL_STACK_SIZE, NULL, 1, NULL);

    vTaskStartScheduler();
    while (1)
        ;
}