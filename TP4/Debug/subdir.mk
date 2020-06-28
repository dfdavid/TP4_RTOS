################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../cr_startup_lpc17.c \
../main.c 

OBJS += \
./cr_startup_lpc17.o \
./main.o 

C_DEPS += \
./cr_startup_lpc17.d \
./main.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -DDEBUG -D__USE_CMSIS=CMSISv1p30_LPC17xx -D__CODE_RED -D__NEWLIB__ -I"/home/sampaxx/Escritorio/Sistemas Operativos II/TP4_RTOS/FreeRTOS_Library/demo_code" -I"/home/sampaxx/Escritorio/Sistemas Operativos II/TP4_RTOS/CMSISv1p30_LPC17xx/inc" -I"/home/sampaxx/Escritorio/Sistemas Operativos II/TP4_RTOS/FreeRTOS_Library/include" -I"/home/sampaxx/Escritorio/Sistemas Operativos II/TP4_RTOS/FreeRTOS_Library/portable" -O1 -g3 -fsigned-char -c -fmessage-length=0 -fno-builtin -ffunction-sections -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m3 -mthumb -D__NEWLIB__ -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


