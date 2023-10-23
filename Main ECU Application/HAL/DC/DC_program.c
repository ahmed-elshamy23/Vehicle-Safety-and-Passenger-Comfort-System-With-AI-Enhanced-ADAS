#include "DC_interface.h"
#include "DC_config.h"
#include "../../MCAL/TIM2/TIM2_interface.h"
#include "../../MCAL/DIO/DIO_interface.h"
#include "../../MCAL/RCC/RCC_interface.h"
#include "../../MCAL/RCC/RCC_private.h"

void DC_voidInit()
{
    RCC_voidEnablePeripheralClock(APB1_BUS, TIM2_RCC);
    RCC_voidEnablePeripheralClock(APB2_BUS, DC_PORT_RCC);
    MDIO_voidSetPinDirection(DC_PORT, DC_IN1_PIN, OUTPUT_SPEED_2MHZ_PP);
    MDIO_voidSetPinDirection(DC_PORT, DC_IN2_PIN, OUTPUT_SPEED_2MHZ_PP);
    MDIO_voidSetPinDirection(DC_PORT, DC_IN3_PIN, OUTPUT_SPEED_2MHZ_PP);
    MDIO_voidSetPinDirection(DC_PORT, DC_IN4_PIN, OUTPUT_SPEED_2MHZ_PP);
    /* PWM Pins (alternate function) to be completed
    MDIO_voidSetPinDirection(DC_PORT, DC_ENA_PIN, OUTPUT_SPEED_2MHZ_PP);
    MDIO_voidSetPinDirection(DC_PORT, DC_ENB_PIN, OUTPUT_SPEED_2MHZ_PP);
    */
}

void DC_voidSetSpeed(u8 speed);