################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../FreeRTOS/Source/portable/GCC/ARM_CM4F/port.c 

OBJS += \
./FreeRTOS/Source/portable/GCC/ARM_CM4F/port.o 

C_DEPS += \
./FreeRTOS/Source/portable/GCC/ARM_CM4F/port.d 


# Each subdirectory must supply rules for building sources it contributes
FreeRTOS/Source/portable/GCC/ARM_CM4F/%.o FreeRTOS/Source/portable/GCC/ARM_CM4F/%.su FreeRTOS/Source/portable/GCC/ARM_CM4F/%.cyclo: ../FreeRTOS/Source/portable/GCC/ARM_CM4F/%.c FreeRTOS/Source/portable/GCC/ARM_CM4F/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m4 -std=gnu11 -g3 -DDEBUG -DSTM32 -DSTM32F4 -DSTM32F407VGTx -c -I../Inc -I"C:/Users/chandanar/Desktop/GitHub/PersonalProjects/FreeRTOS_with_BareMetal/workspace_stm32_freeRTOS_baremetal/002_led_interrupt_toggle_addr/FreeRTOS/Source" -I"C:/Users/chandanar/Desktop/GitHub/PersonalProjects/FreeRTOS_with_BareMetal/workspace_stm32_freeRTOS_baremetal/002_led_interrupt_toggle_addr/FreeRTOS/Source/include" -I"C:/Users/chandanar/Desktop/GitHub/PersonalProjects/FreeRTOS_with_BareMetal/workspace_stm32_freeRTOS_baremetal/002_led_interrupt_toggle_addr/FreeRTOS/Source/portable/GCC/ARM_CM4F" -I"C:/Users/chandanar/Desktop/GitHub/PersonalProjects/FreeRTOS_with_BareMetal/workspace_stm32_freeRTOS_baremetal/chip_headers/CMSIS/Include" -I"C:/Users/chandanar/Desktop/GitHub/PersonalProjects/FreeRTOS_with_BareMetal/workspace_stm32_freeRTOS_baremetal/chip_headers/CMSIS/Device/ST/STM32F4xx/Include" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv4-sp-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-FreeRTOS-2f-Source-2f-portable-2f-GCC-2f-ARM_CM4F

clean-FreeRTOS-2f-Source-2f-portable-2f-GCC-2f-ARM_CM4F:
	-$(RM) ./FreeRTOS/Source/portable/GCC/ARM_CM4F/port.cyclo ./FreeRTOS/Source/portable/GCC/ARM_CM4F/port.d ./FreeRTOS/Source/portable/GCC/ARM_CM4F/port.o ./FreeRTOS/Source/portable/GCC/ARM_CM4F/port.su

.PHONY: clean-FreeRTOS-2f-Source-2f-portable-2f-GCC-2f-ARM_CM4F

