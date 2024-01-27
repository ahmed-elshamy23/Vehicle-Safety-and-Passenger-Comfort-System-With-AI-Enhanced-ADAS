#include "app.h"
#include "../Common/std_types.h"
#include "../MCAL/RCC/RCC_interface.h"
#include "../MCAL/DIO/DIO_interface.h"
#include "../MCAL/USART/USART_interface.h"
#include "../MCAL/TIM2/TIM2_interface.h"
#include "../HAL/DC/DC_interface.h"
#include "../HAL/LED/LED_interface.h"
#include "../HAL/Switch/SWITCH_interface.h"
#include "../HAL/Servo/SERVO_interface.h"
#include "../HAL/Servo/SERVO_config.h"
#include "../HAL/Ultrasonic/ULTRASONIC_interface.h"

#include "../Services/FreeRTOS.h"
#include "../Services/task.h"

static f32 distance = 40.0f, speed = INITIAL_SPEED;

void appInit()
{
    RCC_voidEnablePeripheralClock(APB2_BUS, DIOA_RCC);
    RCC_voidEnablePeripheralClock(APB2_BUS, DIOB_RCC);
    RCC_voidEnablePeripheralClock(APB2_BUS, USART1_RCC);
    RCC_voidEnablePeripheralClock(APB2_BUS, TIM1_RCC);
    RCC_voidEnablePeripheralClock(APB1_BUS, TIM2_RCC);
    RCC_voidEnablePeripheralClock(APB1_BUS, TIM3_RCC);

    MDIO_voidSetPinDirection(DIOA, PIN9, OUTPUT_SPEED_50MHZ_PP);
    MDIO_voidSetPinDirection(DIOA, PIN10, INPUT_FLOATING);

    USART_voidInit();
    DC_voidInit();
    LED_voidInit(DIOA, PIN6);
    SERVO_voidInit();
    SWITCH_voidInit(DIOB, PIN8, PULLDOWN_RESISTOR);
    ULTRASONIC_voidInit();
}

void applyDriverProfile()
{
    u8 driver = USART_u8ReceiveData();
    if (driver == DRIVER_1)
    {
        SERVO_voidSetAngle(SERVO_RIGHT_MIRROR, 20);
        SERVO_voidSetAngle(SERVO_LEFT_MIRROR, 20);
        SERVO_voidSetAngle(SERVO_CHAIR, 20);
    }
    else if (driver == DRIVER_2)
    {
        SERVO_voidSetAngle(SERVO_RIGHT_MIRROR, 40);
        SERVO_voidSetAngle(SERVO_LEFT_MIRROR, 40);
        SERVO_voidSetAngle(SERVO_CHAIR, 40);
    }
    else
    {
        SERVO_voidSetAngle(SERVO_RIGHT_MIRROR, 60);
        SERVO_voidSetAngle(SERVO_LEFT_MIRROR, 60);
        SERVO_voidSetAngle(SERVO_CHAIR, 60);
    }
    TIM2_voidStart();
}

void getDistance()
{
    TickType_t xLastWakeTime;
    const TickType_t xFrequency = 10;
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
    const TickType_t xFrequency = 10;
    xLastWakeTime = xTaskGetTickCount();
    while (1)
    {
        if (distance <= ACC_THRESHOLD)
            speed -= 0.2f;
        else if (distance <= AEB_THRESHOLD)
            speed = 0.0f;
        else
            speed += 0.1f;
        if (speed > 1.0f)
            speed = 1.0f;
        else if (speed < 0.0f)
            speed = 0.0f;
        if (speed)
        {
            DC_voidStart();
            DC_voidSetSpeed(speed);
        }
        else
            DC_voidStop();

        // direction controls to be added

        vTaskDelayUntil(&xLastWakeTime, xFrequency);
    }
}

void checkReedSwitch()
{
    TickType_t xLastWakeTime;
    const TickType_t xFrequency = 10;
    xLastWakeTime = xTaskGetTickCount();
    while (1)
    {
        if (SWITCH_u8SwitchIsOn(DIOB, PIN8))
        {
            LED_voidState(DIOA, PIN6, DIO_HIGH);
            DC_voidStop();
            vTaskEndScheduler();
        }
        vTaskDelayUntil(&xLastWakeTime, xFrequency);
    }
}

void receiveUartFrame()
{
    u8 data = EMPTY_DATA;
    TickType_t xLastWakeTime;
    const TickType_t xFrequency = 10;
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
        }

        // direction controls to be received

        vTaskDelayUntil(&xLastWakeTime, xFrequency);
    }
}