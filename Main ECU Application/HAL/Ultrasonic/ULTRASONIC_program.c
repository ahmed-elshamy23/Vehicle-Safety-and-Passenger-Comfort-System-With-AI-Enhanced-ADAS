#include "ULTRASONIC_config.h"
#include "ULTRASONIC_interface.h"
#include "../../MCAL/TIM1/TIM1_interface.h"
#include "../../MCAL/DIO/DIO_interface.h"
#include "../../MCAL/RCC/RCC_interface.h"
#include "../../MCAL/RCC/RCC_private.h"

void ULTRASONIC_voidInit()
{
    RCC_voidEnablePeripheralClock(APB2_BUS, TIM1_RCC);
    RCC_voidEnablePeripheralClock(APB2_BUS, ULTRASONIC_PORT_RCC);
    TIM1_voidInit();
    MDIO_voidSetPinDirection(ULTRASONIC_PORT, ULTRASONIC_TRIG, OUTPUT_SPEED_2MHZ_PP);
    MDIO_voidSetPinDirection(ULTRASONIC_PORT, ULTRASONIC_ECHO, INPUT_PULLUP_PULLDOWN);
}

f32 ULTRASONIC_f32GetDistance()
{
    MDIO_voidSetPinValue(ULTRASONIC_PORT, ULTRASONIC_TRIG, DIO_HIGH);
    TIM1_voidDelay(0.0000012f);
    MDIO_voidSetPinValue(ULTRASONIC_PORT, ULTRASONIC_TRIG, DIO_LOW);
    while (!MDIO_u8GetPinValue(ULTRASONIC_PORT, ULTRASONIC_ECHO))
        ;
    TIM1_voidSetTimerValue(0);
    TIM1_voidStart();
    while (MDIO_u8GetPinValue(ULTRASONIC_PORT, ULTRASONIC_ECHO))
        ;
    TIM1_voidStop();
    return 340.0f * TIM1_u16GetTimerValue() * 0.000001f;
}