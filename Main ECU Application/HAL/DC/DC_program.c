#include "DC_interface.h"
#include "DC_config.h"
#include "../../MCAL/TIM1/TIM1_interface.h"
#include "../../MCAL/TIM1/TIM1_private.h"
#include "../../MCAL/DIO/DIO_interface.h"
#include "../../MCAL/RCC/RCC_interface.h"
#include "../../MCAL/RCC/RCC_private.h"

void DC_voidInit(u8 port, u8 in1Pin, u8 in2Pin, u8 in3Pin, u8 in4Pin, u8 pwmChannel)
{
    RCC_voidEnablePeripheralClock(APB2_BUS, TIM1_RCC);
    switch (port)
    {
    case DIOA:
        RCC_voidEnablePeripheralClock(APB2_BUS, DIOA_RCC);
        break;
    case DIOB:
        RCC_voidEnablePeripheralClock(APB2_BUS, DIOB_RCC);
        break;
    case DIOC:
        RCC_voidEnablePeripheralClock(APB2_BUS, DIOC_RCC);
        break;
    }
    MDIO_voidSetPinDirection(port, in1Pin, OUTPUT_SPEED_2MHZ_PP);
    MDIO_voidSetPinDirection(port, in2Pin, OUTPUT_SPEED_2MHZ_PP);
    MDIO_voidSetPinDirection(port, in3Pin, OUTPUT_SPEED_2MHZ_PP);
    MDIO_voidSetPinDirection(port, in4Pin, OUTPUT_SPEED_2MHZ_PP);
    /* PWM Pins (alternate function) to be completed
    MDIO_voidSetPinDirection(DC_PORT, DC_ENA_PIN, OUTPUT_SPEED_2MHZ_PP);
    MDIO_voidSetPinDirection(DC_PORT, DC_ENB_PIN, OUTPUT_SPEED_2MHZ_PP);
    */
    TIM1_voidInit();
}

void DC_voidSetSpeed(u8 pwmChannel, u8 speed)
{
    TIM1_voidGeneratePwm(pwmChannel, speed / 100.0f);
}