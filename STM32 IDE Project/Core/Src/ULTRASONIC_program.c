#include "ULTRASONIC_config.h"
#include "ULTRASONIC_interface.h"
#include "../Src/TIM3_interface.h"
#include "../Src/DIO_interface.h"
#include "../Src/RCC_interface.h"
#include "../Src/RCC_private.h"

void ULTRASONIC_voidInit()
{
    RCC_voidEnablePeripheralClock(APB1_BUS, TIM3_RCC);
    RCC_voidEnablePeripheralClock(APB2_BUS, ULTRASONIC_PORT_RCC);
    TIM3_voidInit();
    MDIO_voidSetPinDirection(ULTRASONIC_PORT, ULTRASONIC_TRIG, OUTPUT_SPEED_2MHZ_PP);
    MDIO_voidSetPinDirection(ULTRASONIC_PORT, ULTRASONIC_ECHO, INPUT_PULLUP_PULLDOWN);
    MDIO_voidSetPinValue(ULTRASONIC_PORT, ULTRASONIC_ECHO, DIO_LOW);
}

f32 ULTRASONIC_f32GetDistance()
{
    MDIO_voidSetPinValue(ULTRASONIC_PORT, ULTRASONIC_TRIG, DIO_HIGH);
    TIM3_voidDelay(0.000015f);
    MDIO_voidSetPinValue(ULTRASONIC_PORT, ULTRASONIC_TRIG, DIO_LOW);
    while (!MDIO_u8GetPinValue(ULTRASONIC_PORT, ULTRASONIC_ECHO))
        ;
    TIM3_voidSetTimerValue(0);
    TIM3_voidStart();
    while (MDIO_u8GetPinValue(ULTRASONIC_PORT, ULTRASONIC_ECHO))
        if (TIM3_u16GetTimerValue() > 11764)
            break;
    TIM3_voidStop();
    return 340.0f * TIM3_u16GetTimerValue() * 0.000001f;
}
