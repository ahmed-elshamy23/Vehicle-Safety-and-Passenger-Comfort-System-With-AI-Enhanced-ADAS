#include "SWITCH_interface.h"
#include "../../MCAL/DIO/DIO_interface.h"
#include "../../MCAL/DIO/DIO_private.h"
#include "../../MCAL/RCC/RCC_interface.h"
#include "../../MCAL/RCC/RCC_private.h"

void SWITCH_voidInit(u8 portNumber, u8 pinNumber, u8 resistorState)
{
    switch (portNumber)
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
    MDIO_voidSetPinDirection(portNumber, pinNumber, INPUT_PULLUP_PULLDOWN);
    switch (resistorState)
    {
    case PULLDOWN_RESISTOR:
        MDIO_voidSetPinValue(portNumber, pinNumber, DIO_LOW);
        break;
    case PULLUP_RESISTOR:
        MDIO_voidSetPinValue(portNumber, pinNumber, DIO_HIGH);
        break;
    }
}

u8 SWITCH_u8SwitchIsOn(u8 portNumber, u8 pinNumber)
{
    if (MDIO_u8GetPinValue(portNumber, pinNumber) == DIO_HIGH)
        return 1;
    return 0;
}