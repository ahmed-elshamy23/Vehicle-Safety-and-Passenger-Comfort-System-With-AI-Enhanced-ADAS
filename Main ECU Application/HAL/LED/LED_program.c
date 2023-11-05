#include "../../Common/std_types.h"
#include "../../MCAL/DIO/DIO_interface.h"
#include "../../MCAL/DIO/DIO_private.h"
#include "LED_interface.h"

void LED_voidInit(u8 portNumber, u8 pinNumber)
{
    MDIO_voidSetPinDirection(portNumber, pinNumber, OUTPUT_SPEED_2MHZ_PP);
    MDIO_voidSetPinValue(portNumber, pinNumber, DIO_LOW);
}

void LED_voidState(u8 portNumber, u8 pinNumber, u8 value)
{
    switch (value)
    {
    case ON:
        MDIO_voidSetPinValue(portNumber, pinNumber, DIO_HIGH);
        break;
    case OFF:
        MDIO_voidSetPinValue(portNumber, pinNumber, DIO_LOW);
        break;
    }
}