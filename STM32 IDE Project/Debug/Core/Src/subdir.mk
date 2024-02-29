################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/DC_program.c \
../Core/Src/DIO_program.c \
../Core/Src/LED_program.c \
../Core/Src/RCC_program.c \
../Core/Src/SERVO_program.c \
../Core/Src/TIM1_program.c \
../Core/Src/TIM2_program.c \
../Core/Src/TIM3_program.c \
../Core/Src/ULTRASONIC_program.c \
../Core/Src/USART_program.c \
../Core/Src/app.c \
../Core/Src/freertos.c \
../Core/Src/main.c \
../Core/Src/stm32f1xx_hal_msp.c \
../Core/Src/stm32f1xx_it.c \
../Core/Src/syscalls.c \
../Core/Src/system_stm32f1xx.c 

OBJS += \
./Core/Src/DC_program.o \
./Core/Src/DIO_program.o \
./Core/Src/LED_program.o \
./Core/Src/RCC_program.o \
./Core/Src/SERVO_program.o \
./Core/Src/TIM1_program.o \
./Core/Src/TIM2_program.o \
./Core/Src/TIM3_program.o \
./Core/Src/ULTRASONIC_program.o \
./Core/Src/USART_program.o \
./Core/Src/app.o \
./Core/Src/freertos.o \
./Core/Src/main.o \
./Core/Src/stm32f1xx_hal_msp.o \
./Core/Src/stm32f1xx_it.o \
./Core/Src/syscalls.o \
./Core/Src/system_stm32f1xx.o 

C_DEPS += \
./Core/Src/DC_program.d \
./Core/Src/DIO_program.d \
./Core/Src/LED_program.d \
./Core/Src/RCC_program.d \
./Core/Src/SERVO_program.d \
./Core/Src/TIM1_program.d \
./Core/Src/TIM2_program.d \
./Core/Src/TIM3_program.d \
./Core/Src/ULTRASONIC_program.d \
./Core/Src/USART_program.d \
./Core/Src/app.d \
./Core/Src/freertos.d \
./Core/Src/main.d \
./Core/Src/stm32f1xx_hal_msp.d \
./Core/Src/stm32f1xx_it.d \
./Core/Src/syscalls.d \
./Core/Src/system_stm32f1xx.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/%.o Core/Src/%.su Core/Src/%.cyclo: ../Core/Src/%.c Core/Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103x6 -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I../Middlewares/Third_Party/FreeRTOS/Source/include -I../Middlewares/Third_Party/FreeRTOS/Source/CMSIS_RTOS -I../Middlewares/Third_Party/FreeRTOS/Source/portable/GCC/ARM_CM3 -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Src

clean-Core-2f-Src:
	-$(RM) ./Core/Src/DC_program.cyclo ./Core/Src/DC_program.d ./Core/Src/DC_program.o ./Core/Src/DC_program.su ./Core/Src/DIO_program.cyclo ./Core/Src/DIO_program.d ./Core/Src/DIO_program.o ./Core/Src/DIO_program.su ./Core/Src/LED_program.cyclo ./Core/Src/LED_program.d ./Core/Src/LED_program.o ./Core/Src/LED_program.su ./Core/Src/RCC_program.cyclo ./Core/Src/RCC_program.d ./Core/Src/RCC_program.o ./Core/Src/RCC_program.su ./Core/Src/SERVO_program.cyclo ./Core/Src/SERVO_program.d ./Core/Src/SERVO_program.o ./Core/Src/SERVO_program.su ./Core/Src/TIM1_program.cyclo ./Core/Src/TIM1_program.d ./Core/Src/TIM1_program.o ./Core/Src/TIM1_program.su ./Core/Src/TIM2_program.cyclo ./Core/Src/TIM2_program.d ./Core/Src/TIM2_program.o ./Core/Src/TIM2_program.su ./Core/Src/TIM3_program.cyclo ./Core/Src/TIM3_program.d ./Core/Src/TIM3_program.o ./Core/Src/TIM3_program.su ./Core/Src/ULTRASONIC_program.cyclo ./Core/Src/ULTRASONIC_program.d ./Core/Src/ULTRASONIC_program.o ./Core/Src/ULTRASONIC_program.su ./Core/Src/USART_program.cyclo ./Core/Src/USART_program.d ./Core/Src/USART_program.o ./Core/Src/USART_program.su ./Core/Src/app.cyclo ./Core/Src/app.d ./Core/Src/app.o ./Core/Src/app.su ./Core/Src/freertos.cyclo ./Core/Src/freertos.d ./Core/Src/freertos.o ./Core/Src/freertos.su ./Core/Src/main.cyclo ./Core/Src/main.d ./Core/Src/main.o ./Core/Src/main.su ./Core/Src/stm32f1xx_hal_msp.cyclo ./Core/Src/stm32f1xx_hal_msp.d ./Core/Src/stm32f1xx_hal_msp.o ./Core/Src/stm32f1xx_hal_msp.su ./Core/Src/stm32f1xx_it.cyclo ./Core/Src/stm32f1xx_it.d ./Core/Src/stm32f1xx_it.o ./Core/Src/stm32f1xx_it.su ./Core/Src/syscalls.cyclo ./Core/Src/syscalls.d ./Core/Src/syscalls.o ./Core/Src/syscalls.su ./Core/Src/system_stm32f1xx.cyclo ./Core/Src/system_stm32f1xx.d ./Core/Src/system_stm32f1xx.o ./Core/Src/system_stm32f1xx.su

.PHONY: clean-Core-2f-Src

