################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (11.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Core/Src/Services/heap_1.c \
../Core/Src/Services/list.c \
../Core/Src/Services/port.c \
../Core/Src/Services/queue.c \
../Core/Src/Services/stream_buffer.c \
../Core/Src/Services/tasks.c \
../Core/Src/Services/timers.c 

OBJS += \
./Core/Src/Services/heap_1.o \
./Core/Src/Services/list.o \
./Core/Src/Services/port.o \
./Core/Src/Services/queue.o \
./Core/Src/Services/stream_buffer.o \
./Core/Src/Services/tasks.o \
./Core/Src/Services/timers.o 

C_DEPS += \
./Core/Src/Services/heap_1.d \
./Core/Src/Services/list.d \
./Core/Src/Services/port.d \
./Core/Src/Services/queue.d \
./Core/Src/Services/stream_buffer.d \
./Core/Src/Services/tasks.d \
./Core/Src/Services/timers.d 


# Each subdirectory must supply rules for building sources it contributes
Core/Src/Services/%.o Core/Src/Services/%.su Core/Src/Services/%.cyclo: ../Core/Src/Services/%.c Core/Src/Services/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_HAL_DRIVER -DSTM32F103x6 -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc/Legacy -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Core-2f-Src-2f-Services

clean-Core-2f-Src-2f-Services:
	-$(RM) ./Core/Src/Services/heap_1.cyclo ./Core/Src/Services/heap_1.d ./Core/Src/Services/heap_1.o ./Core/Src/Services/heap_1.su ./Core/Src/Services/list.cyclo ./Core/Src/Services/list.d ./Core/Src/Services/list.o ./Core/Src/Services/list.su ./Core/Src/Services/port.cyclo ./Core/Src/Services/port.d ./Core/Src/Services/port.o ./Core/Src/Services/port.su ./Core/Src/Services/queue.cyclo ./Core/Src/Services/queue.d ./Core/Src/Services/queue.o ./Core/Src/Services/queue.su ./Core/Src/Services/stream_buffer.cyclo ./Core/Src/Services/stream_buffer.d ./Core/Src/Services/stream_buffer.o ./Core/Src/Services/stream_buffer.su ./Core/Src/Services/tasks.cyclo ./Core/Src/Services/tasks.d ./Core/Src/Services/tasks.o ./Core/Src/Services/tasks.su ./Core/Src/Services/timers.cyclo ./Core/Src/Services/timers.d ./Core/Src/Services/timers.o ./Core/Src/Services/timers.su

.PHONY: clean-Core-2f-Src-2f-Services

