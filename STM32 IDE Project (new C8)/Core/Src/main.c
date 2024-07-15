#include "app.h"
#include "../../Middlewares/Third_Party/FreeRTOS/Source/include/FreeRTOS.h"
#include "../../Middlewares/Third_Party/FreeRTOS/Source/include/task.h"
#include "DC_interface.h"

int main()
{
    appInit();
    applyDriverProfile();
//    TIM2_voidStart();
    DC_voidSetSpeed(INITIAL_SPEED);
    DC_voidStart();

    xTaskCreate(getDistance, "Measuring Distance", configMINIMAL_STACK_SIZE, NULL, 4, NULL);
    xTaskCreate(updateSpeedAndDirection, "Managing AEB and ACC", configMINIMAL_STACK_SIZE, NULL, 3, NULL);
    xTaskCreate(receiveUartFrame, "Receiving Frames from ESP32", configMINIMAL_STACK_SIZE, NULL, 2, NULL);
//    xTaskCreate(steeringControl, "Direction Control", configMINIMAL_STACK_SIZE, NULL, 1, NULL);

    vTaskStartScheduler();
    while (1)
        ;
}
