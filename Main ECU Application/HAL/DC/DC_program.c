#include "DC_interface.h"
#include "DC_config.h"
#include "../../MCAL/TIM1/TIM1_interface.h"
#include "../../MCAL/TIM1/TIM1_private.h"
#include "../../MCAL/DIO/DIO_interface.h"
#include "../../MCAL/RCC/RCC_interface.h"
#include "../../MCAL/RCC/RCC_private.h"

void DC_voidInit()
{
    RCC_voidEnablePeripheralClock(APB2_BUS, TIM1_RCC);
    RCC_voidEnablePeripheralClock(APB2_BUS, DC_PORT_RCC);

    MDIO_voidSetPinDirection(DC_PORT, DC_FRONT_IN1_PIN, OUTPUT_SPEED_2MHZ_PP);
    MDIO_voidSetPinDirection(DC_PORT, DC_FRONT_IN2_PIN, OUTPUT_SPEED_2MHZ_PP);
    MDIO_voidSetPinDirection(DC_PORT, DC_FRONT_IN3_PIN, OUTPUT_SPEED_2MHZ_PP);
    MDIO_voidSetPinDirection(DC_PORT, DC_FRONT_IN4_PIN, OUTPUT_SPEED_2MHZ_PP);

    MDIO_voidSetPinDirection(DC_PORT, DC_REAR_IN1_PIN, OUTPUT_SPEED_2MHZ_PP);
    MDIO_voidSetPinDirection(DC_PORT, DC_REAR_IN2_PIN, OUTPUT_SPEED_2MHZ_PP);
    MDIO_voidSetPinDirection(DC_PORT, DC_REAR_IN3_PIN, OUTPUT_SPEED_2MHZ_PP);
    MDIO_voidSetPinDirection(DC_PORT, DC_REAR_IN4_PIN, OUTPUT_SPEED_2MHZ_PP);

    MDIO_voidSetPinDirection(DC_PORT, PIN8, OUTPUT_SPEED_50MHZ_AFPP);
    MDIO_voidSetPinDirection(DC_PORT, PIN9, OUTPUT_SPEED_50MHZ_AFPP);
    MDIO_voidSetPinDirection(DC_PORT, PIN10, OUTPUT_SPEED_50MHZ_AFPP);
    MDIO_voidSetPinDirection(DC_PORT, PIN11, OUTPUT_SPEED_50MHZ_AFPP);

    TIM1_voidInit();
}

void DC_voidSetSpeed(u8 frontRightSpeed, u8 frontLeftSpeed, u8 rearRightSpeed, u8 rearLeftSpeed)
{
    TIM1_voidGeneratePwm(PWM_CHANNEL_1, frontRightSpeed / 100.0f);
    TIM1_voidGeneratePwm(PWM_CHANNEL_2, frontLeftSpeed / 100.0f);
    TIM1_voidGeneratePwm(PWM_CHANNEL_3, rearRightSpeed / 100.0f);
    TIM1_voidGeneratePwm(PWM_CHANNEL_4, rearLeftSpeed / 100.0f);
    TIM1_voidStart();
}

void DC_voidStart(u8 motorNumber)
{
    switch (motorNumber)
    {
    case DC_FRONT_RIGHT_MOTOR:
        MDIO_voidSetPinValue(DC_PORT, DC_FRONT_IN1_PIN, DIO_HIGH);
        MDIO_voidSetPinValue(DC_PORT, DC_FRONT_IN2_PIN, DIO_LOW);
        break;
    case DC_FRONT_LEFT_MOTOR:
        MDIO_voidSetPinValue(DC_PORT, DC_FRONT_IN3_PIN, DIO_HIGH);
        MDIO_voidSetPinValue(DC_PORT, DC_FRONT_IN4_PIN, DIO_LOW);
        break;
    case DC_REAR_RIGHT_MOTOR:
        MDIO_voidSetPinValue(DC_PORT, DC_REAR_IN1_PIN, DIO_HIGH);
        MDIO_voidSetPinValue(DC_PORT, DC_REAR_IN2_PIN, DIO_LOW);
        break;
    case DC_REAR_LEFT_MOTOR:
        MDIO_voidSetPinValue(DC_PORT, DC_REAR_IN3_PIN, DIO_HIGH);
        MDIO_voidSetPinValue(DC_PORT, DC_REAR_IN4_PIN, DIO_LOW);
        break;
    }
}

void DC_voidStop(u8 motorNumber)
{
    switch (motorNumber)
    {
    case DC_FRONT_RIGHT_MOTOR:
        MDIO_voidSetPinValue(DC_PORT, DC_FRONT_IN1_PIN, DIO_LOW);
        MDIO_voidSetPinValue(DC_PORT, DC_FRONT_IN2_PIN, DIO_LOW);
        break;
    case DC_FRONT_LEFT_MOTOR:
        MDIO_voidSetPinValue(DC_PORT, DC_FRONT_IN3_PIN, DIO_LOW);
        MDIO_voidSetPinValue(DC_PORT, DC_FRONT_IN4_PIN, DIO_LOW);
        break;
    case DC_REAR_RIGHT_MOTOR:
        MDIO_voidSetPinValue(DC_PORT, DC_REAR_IN1_PIN, DIO_LOW);
        MDIO_voidSetPinValue(DC_PORT, DC_REAR_IN2_PIN, DIO_LOW);
        break;
    case DC_REAR_LEFT_MOTOR:
        MDIO_voidSetPinValue(DC_PORT, DC_REAR_IN3_PIN, DIO_LOW);
        MDIO_voidSetPinValue(DC_PORT, DC_REAR_IN4_PIN, DIO_LOW);
        break;
    }
}