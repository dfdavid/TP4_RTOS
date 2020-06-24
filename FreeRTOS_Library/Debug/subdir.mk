################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../SEGGER_RTT.c \
../list.c \
../queue.c \
../tasks.c \
../trcKernelPort.c \
../trcSnapshotRecorder.c \
../trcStreamingPort.c \
../trcStreamingRecorder.c 

OBJS += \
./SEGGER_RTT.o \
./list.o \
./queue.o \
./tasks.o \
./trcKernelPort.o \
./trcSnapshotRecorder.o \
./trcStreamingPort.o \
./trcStreamingRecorder.o 

C_DEPS += \
./SEGGER_RTT.d \
./list.d \
./queue.d \
./tasks.d \
./trcKernelPort.d \
./trcSnapshotRecorder.d \
./trcStreamingPort.d \
./trcStreamingRecorder.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__NEWLIB__ -I"C:\Users\pc\Documents\MCUXpressoIDE_11.1.1_3241\workspace\FreeRTOS_Library\include" -I"C:\Users\pc\Documents\MCUXpressoIDE_11.1.1_3241\workspace\CMSISv1p30_LPC17xx\inc" -I"C:\Users\pc\Documents\MCUXpressoIDE_11.1.1_3241\workspace\FreeRTOS_Library\portable" -I"C:\Users\pc\Documents\MCUXpressoIDE_11.1.1_3241\workspace\FreeRTOS_Library\demo_code" -O1 -g3 -Wall -c -fmessage-length=0 -fmacro-prefix-map="../$(@D)/"=. -mcpu=cortex-m3 -mthumb -D__NEWLIB__ -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


