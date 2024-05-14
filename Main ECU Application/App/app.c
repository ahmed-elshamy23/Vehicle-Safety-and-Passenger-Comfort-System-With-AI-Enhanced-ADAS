#include "app.h"
#include "../Common/std_types.h"
#include "RCC_interface.h"
#include "DIO_interface.h"
#include "USART_interface.h"
#include "TIM2_interface.h"
#include "TIM3_interface.h"
#include "DC_interface.h"
#include "SERVO_interface.h"
#include "SERVO_config.h"
#include "ULTRASONIC_interface.h"

#include "../../Middlewares/Third_Party/FreeRTOS/Source/include/FreeRTOS.h"
#include "../../Middlewares/Third_Party/FreeRTOS/Source/include/task.h"

static f32 distance = 4.0f;
static s8 speed = INITIAL_SPEED;
static volatile u8 data = EMPTY_DATA, angle = INITIAL_ANGLE, angle_temp = INITIAL_ANGLE;

void appInit()
{
    RCC_voidInitSysClock();
    RCC_voidEnablePeripheralClock(APB2_BUS, DIOA_RCC);
    RCC_voidEnablePeripheralClock(APB2_BUS, DIOB_RCC);
    RCC_voidEnablePeripheralClock(APB2_BUS, USART1_RCC);
    RCC_voidEnablePeripheralClock(APB2_BUS, TIM1_RCC);
    RCC_voidEnablePeripheralClock(APB1_BUS, TIM2_RCC);
    RCC_voidEnablePeripheralClock(APB1_BUS, TIM3_RCC);

    MDIO_voidSetPinDirection(DIOA, PIN10, INPUT_FLOATING);

    USART_voidInit();
    DC_voidInit();
    SERVO_voidInit();
    ULTRASONIC_voidInit();

    SERVO_voidSetAngle(SERVO_STEERING, INITIAL_ANGLE);
    //    TIM3_voidDelay(5.0f);
}

void applyDriverProfile()
{
    u8 driver;
    do
    {
        driver = USART_u8ReceiveData();
        if (driver == DRIVER_1)
        {
            SERVO_voidSetAngle(SERVO_RIGHT_MIRROR, 20);
            SERVO_voidSetAngle(SERVO_LEFT_MIRROR, 20);
            SERVO_voidSetAngle(SERVO_CHAIR, 20);
            TIM2_voidStart();
            return;
        }
        else if (driver == DRIVER_2)
        {
            SERVO_voidSetAngle(SERVO_RIGHT_MIRROR, 40);
            SERVO_voidSetAngle(SERVO_LEFT_MIRROR, 40);
            SERVO_voidSetAngle(SERVO_CHAIR, 40);
            TIM2_voidStart();
            return;
        }
        else if (driver == DRIVER_3)
        {
            SERVO_voidSetAngle(SERVO_RIGHT_MIRROR, 60);
            SERVO_voidSetAngle(SERVO_LEFT_MIRROR, 60);
            SERVO_voidSetAngle(SERVO_CHAIR, 60);
            TIM2_voidStart();
            return;
        }
    } while (driver == EMPTY_DATA);
    //    TIM2_voidStart();
}

void getDistance()
{
    TickType_t xLastWakeTime;
    const TickType_t xFrequency = 200;
    xLastWakeTime = xTaskGetTickCount();
    while (1)
    {
        distance = ULTRASONIC_f32GetDistance();
        vTaskDelayUntil(&xLastWakeTime, xFrequency);
    }
}

void updateSpeedAndDirection()
{
    TickType_t xLastWakeTime;
    const TickType_t xFrequency = 100;
    xLastWakeTime = xTaskGetTickCount();
    while (1)
    {
        // processing distance and changing speed
        if (distance <= ACC_THRESHOLD)
            speed -= 10;
        else if (distance <= AEB_THRESHOLD)
            speed = 0;
        else
            speed += 5;

        // keeping speed in the range [0, MAX_SPEED]
        if (speed > MAX_SPEED)
            speed = MAX_SPEED;
        else if (speed < 0)
            speed = 0;

        // applying speed changes
        if (speed)
        {
            DC_voidStart();
            DC_voidSetSpeed(speed);
        }
        else
            DC_voidStop();

        // adjusting steering angle
        if (angle_temp != angle)
        {
            angle = angle_temp;
            SERVO_voidSetAngle(SERVO_STEERING, angle);
        }

        vTaskDelayUntil(&xLastWakeTime, xFrequency);
    }
}

void receiveUartFrame()
{
    TickType_t xLastWakeTime;
    const TickType_t xFrequency = 100;
    xLastWakeTime = xTaskGetTickCount();
    while (1)
    {
        data = USART_u8ReceiveData();
        if (data != EMPTY_DATA)
        {
            if (data == DRIVER_ASLEEP)
            {
                DC_voidStop();
                vTaskEndScheduler();
            }
            else if (data >= 32 && data <= 122)
                angle_temp = data + 13;
        }
        vTaskDelayUntil(&xLastWakeTime, xFrequency);
    }
}

void steeringControl()
{
    TickType_t xLastWakeTime;
    const TickType_t xFrequency = 300;
    xLastWakeTime = xTaskGetTickCount();
    while (1)
    {
        if (angle_temp != angle)
        {
            SERVO_voidSetAngle(SERVO_STEERING, angle);
            angle = angle_temp;
        }
        vTaskDelayUntil(&xLastWakeTime, xFrequency);
    }
}
