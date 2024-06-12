################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/exti.c \
../Src/main.c \
../Src/my_tasks.c \
../Src/syscalls.c \
../Src/sysmem.c 

OBJS += \
./Src/exti.o \
./Src/main.o \
./Src/my_tasks.o \
./Src/syscalls.o \
./Src/sysmem.o 

C_DEPS += \
./Src/exti.d \
./Src/main.d \
./Src/my_tasks.d \
./Src/syscalls.d \
./Src/sysmem.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su Src/%.cyclo: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"C:/Users/chandanar/Desktop/GitHub/PersonalProjects/FreeRTOS_with_BareMetal/workspace_stm32_freeRTOS_baremetal/002_led_interrupt_toggle_addr/FreeRTOS/Source" -I"C:/Users/chandanar/Desktop/GitHub/PersonalProjects/FreeRTOS_with_BareMetal/workspace_stm32_freeRTOS_baremetal/002_led_interrupt_toggle_addr/FreeRTOS/Source/include" -I"C:/Users/chandanar/Desktop/GitHub/PersonalProjects/FreeRTOS_with_BareMetal/workspace_stm32_freeRTOS_baremetal/002_led_interrupt_toggle_addr/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"C:/Users/chandanar/Desktop/GitHub/PersonalProjects/FreeRTOS_with_BareMetal/workspace_stm32_freeRTOS_baremetal/chip_headers/CMSIS/Include" -I"C:/Users/chandanar/Desktop/GitHub/PersonalProjects/FreeRTOS_with_BareMetal/workspace_stm32_freeRTOS_baremetal/chip_headers/CMSIS/Device/ST/STM32F4xx/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/exti.cyclo ./Src/exti.d ./Src/exti.o ./Src/exti.su ./Src/main.cyclo ./Src/main.d ./Src/main.o ./Src/main.su ./Src/my_tasks.cyclo ./Src/my_tasks.d ./Src/my_tasks.o ./Src/my_tasks.su ./Src/syscalls.cyclo ./Src/syscalls.d ./Src/syscalls.o ./Src/syscalls.su ./Src/sysmem.cyclo ./Src/sysmem.d ./Src/sysmem.o ./Src/sysmem.su

.PHONY: clean-Src

