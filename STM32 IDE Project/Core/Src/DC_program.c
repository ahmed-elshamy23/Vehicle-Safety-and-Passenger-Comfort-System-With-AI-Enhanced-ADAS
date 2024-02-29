#include "DC_interface.h"
#include "DC_config.h"
#include "../Src/TIM1_interface.h"
#include "../Src/TIM1_private.h"
#include "../Src/DIO_interface.h"
#include "../Src/RCC_interface.h"
#include "../Src/RCC_private.h"

void DC_voidInit()
{
    RCC_voidEnablePeripheralClock(APB2_BUS, TIM1_RCC);
    RCC_voidEnablePeripheralClock(APB2_BUS, DIOA_RCC);
    RCC_voidEnablePeripheralClock(APB2_BUS, DC_PORT_RCC);

    MDIO_voidSetPinDirection(DC_PORT, DC_IN1_PIN, OUTPUT_SPEED_2MHZ_PP);
    MDIO_voidSetPinDirection(DC_PORT, DC_IN2_PIN, OUTPUT_SPEED_2MHZ_PP);

    MDIO_voidSetPinDirection(DIOA, PIN8, OUTPUT_SPEED_50MHZ_AFPP);

    TIM1_voidInit();
}

void DC_voidSetSpeed(u8 speed)
{
    TIM1_voidGeneratePwm(PWM_CHANNEL_1, speed / 100.0f);
    TIM1_voidStart();
}

void DC_voidStart()
{
    MDIO_voidSetPinValue(DC_PORT, DC_IN1_PIN, DIO_HIGH);
    MDIO_voidSetPinValue(DC_PORT, DC_IN2_PIN, DIO_LOW);
}

void DC_voidStop()
{
    MDIO_voidSetPinValue(DC_PORT, DC_IN1_PIN, DIO_LOW);
    MDIO_voidSetPinValue(DC_PORT, DC_IN2_PIN, DIO_LOW);
}