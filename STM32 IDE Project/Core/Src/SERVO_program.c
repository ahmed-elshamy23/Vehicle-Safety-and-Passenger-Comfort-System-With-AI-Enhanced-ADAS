#include "SERVO_interface.h"
#include "SERVO_config.h"
#include "../Src/TIM2_interface.h"
#include "../Src/TIM2_private.h"
#include "../Src/DIO_interface.h"
#include "../Src/RCC_interface.h"
#include "../Src/RCC_private.h"

void SERVO_voidInit()
{
    RCC_voidEnablePeripheralClock(APB1_BUS, TIM2_RCC);
    RCC_voidEnablePeripheralClock(APB2_BUS, SERVO_PORT_RCC);

    MDIO_voidSetPinDirection(SERVO_PORT, PIN0, OUTPUT_SPEED_50MHZ_AFPP);
    MDIO_voidSetPinDirection(SERVO_PORT, PIN1, OUTPUT_SPEED_50MHZ_AFPP);
    MDIO_voidSetPinDirection(SERVO_PORT, PIN2, OUTPUT_SPEED_50MHZ_AFPP);
    MDIO_voidSetPinDirection(SERVO_PORT, PIN3, OUTPUT_SPEED_50MHZ_AFPP);

    TIM2_voidInit();
}

void SERVO_voidSetAngle(u8 servoNumber, u16 angle)
{
    TIM2_voidGeneratePwm(servoNumber, (1.0f / 3600) * angle + 0.05f);
}
