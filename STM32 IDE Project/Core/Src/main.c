#include "TIM2_interface.h"
#include "TIM2_private.h"
#include "TIM3_interface.h"
#include "DIO_interface.h"
#include "DIO_private.h"
#include "RCC_interface.h"
#include "USART_interface.h"

u8 data;

int main(void)
{
  RCC_voidInitSysClock();

  USART_voidInit();

  MDIO_voidSetPinDirection(DIOA, PIN9, OUTPUT_SPEED_50MHZ_AFPP);
  MDIO_voidSetPinDirection(DIOA, PIN10, OUTPUT_SPEED_50MHZ_AFPP);

  RCC_voidEnablePeripheralClock(APB1_BUS, TIM2_RCC);
  RCC_voidEnablePeripheralClock(APB1_BUS, TIM3_RCC);
  RCC_voidEnablePeripheralClock(APB2_BUS, USART1_RCC);

  while (1)
  {
    data = USART_u8ReceiveData();
  }
}
