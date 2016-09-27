################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../USBHost/mbed-rtos/rtx/TARGET_CORTEX_M/HAL_CM.c \
../USBHost/mbed-rtos/rtx/TARGET_CORTEX_M/RTX_Conf_CM.c \
../USBHost/mbed-rtos/rtx/TARGET_CORTEX_M/rt_CMSIS.c \
../USBHost/mbed-rtos/rtx/TARGET_CORTEX_M/rt_Event.c \
../USBHost/mbed-rtos/rtx/TARGET_CORTEX_M/rt_List.c \
../USBHost/mbed-rtos/rtx/TARGET_CORTEX_M/rt_Mailbox.c \
../USBHost/mbed-rtos/rtx/TARGET_CORTEX_M/rt_MemBox.c \
../USBHost/mbed-rtos/rtx/TARGET_CORTEX_M/rt_Mutex.c \
../USBHost/mbed-rtos/rtx/TARGET_CORTEX_M/rt_Robin.c \
../USBHost/mbed-rtos/rtx/TARGET_CORTEX_M/rt_Semaphore.c \
../USBHost/mbed-rtos/rtx/TARGET_CORTEX_M/rt_System.c \
../USBHost/mbed-rtos/rtx/TARGET_CORTEX_M/rt_Task.c \
../USBHost/mbed-rtos/rtx/TARGET_CORTEX_M/rt_Time.c 

OBJS += \
./USBHost/mbed-rtos/rtx/TARGET_CORTEX_M/HAL_CM.o \
./USBHost/mbed-rtos/rtx/TARGET_CORTEX_M/RTX_Conf_CM.o \
./USBHost/mbed-rtos/rtx/TARGET_CORTEX_M/rt_CMSIS.o \
./USBHost/mbed-rtos/rtx/TARGET_CORTEX_M/rt_Event.o \
./USBHost/mbed-rtos/rtx/TARGET_CORTEX_M/rt_List.o \
./USBHost/mbed-rtos/rtx/TARGET_CORTEX_M/rt_Mailbox.o \
./USBHost/mbed-rtos/rtx/TARGET_CORTEX_M/rt_MemBox.o \
./USBHost/mbed-rtos/rtx/TARGET_CORTEX_M/rt_Mutex.o \
./USBHost/mbed-rtos/rtx/TARGET_CORTEX_M/rt_Robin.o \
./USBHost/mbed-rtos/rtx/TARGET_CORTEX_M/rt_Semaphore.o \
./USBHost/mbed-rtos/rtx/TARGET_CORTEX_M/rt_System.o \
./USBHost/mbed-rtos/rtx/TARGET_CORTEX_M/rt_Task.o \
./USBHost/mbed-rtos/rtx/TARGET_CORTEX_M/rt_Time.o 

C_DEPS += \
./USBHost/mbed-rtos/rtx/TARGET_CORTEX_M/HAL_CM.d \
./USBHost/mbed-rtos/rtx/TARGET_CORTEX_M/RTX_Conf_CM.d \
./USBHost/mbed-rtos/rtx/TARGET_CORTEX_M/rt_CMSIS.d \
./USBHost/mbed-rtos/rtx/TARGET_CORTEX_M/rt_Event.d \
./USBHost/mbed-rtos/rtx/TARGET_CORTEX_M/rt_List.d \
./USBHost/mbed-rtos/rtx/TARGET_CORTEX_M/rt_Mailbox.d \
./USBHost/mbed-rtos/rtx/TARGET_CORTEX_M/rt_MemBox.d \
./USBHost/mbed-rtos/rtx/TARGET_CORTEX_M/rt_Mutex.d \
./USBHost/mbed-rtos/rtx/TARGET_CORTEX_M/rt_Robin.d \
./USBHost/mbed-rtos/rtx/TARGET_CORTEX_M/rt_Semaphore.d \
./USBHost/mbed-rtos/rtx/TARGET_CORTEX_M/rt_System.d \
./USBHost/mbed-rtos/rtx/TARGET_CORTEX_M/rt_Task.d \
./USBHost/mbed-rtos/rtx/TARGET_CORTEX_M/rt_Time.d 


# Each subdirectory must supply rules for building sources it contributes
USBHost/mbed-rtos/rtx/TARGET_CORTEX_M/%.o: ../USBHost/mbed-rtos/rtx/TARGET_CORTEX_M/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__NEWLIB__ -D__CODE_RED -DCPP_USE_HEAP -DTARGET_LPC1768 -DTARGET_M3 -DTARGET_CORTEX_M -DTARGET_NXP -DTARGET_LPC176X -DTARGET_MBED_LPC1768 -DTOOLCHAIN_GCC_CR -DTOOLCHAIN_GCC -D__CORTEX_M3 -DARM_MATH_CM3 -DMBED_BUILD_TIMESTAMP=1438622512.88 -D__MBED__=1 -I"/home/andrea/workspace.private/CMSIS/Robot5" -I"/home/andrea/workspace.private/CMSIS/Robot5/mbed" -I"/home/andrea/workspace.private/CMSIS/Robot5/mbed/TARGET_LPC1768" -I"/home/andrea/workspace.private/CMSIS/Robot5/mbed/TARGET_LPC1768/TOOLCHAIN_GCC_CR" -I"/home/andrea/workspace.private/CMSIS/Robot5/mbed/TARGET_LPC1768/TARGET_NXP" -I"/home/andrea/workspace.private/CMSIS/Robot5/mbed/TARGET_LPC1768/TARGET_NXP/TARGET_LPC176X" -I"/home/andrea/workspace.private/CMSIS/Robot5/mbed/TARGET_LPC1768/TARGET_NXP/TARGET_LPC176X/TARGET_MBED_LPC1768" -I"/home/andrea/workspace.private/CMSIS/Robot5/USBHostXpad" -I"/home/andrea/workspace.private/CMSIS/Robot5/USBHost" -I"/home/andrea/workspace.private/CMSIS/Robot5/USBHost/FATFileSystem" -I"/home/andrea/workspace.private/CMSIS/Robot5/USBHost/FATFileSystem/ChaN" -I"/home/andrea/workspace.private/CMSIS/Robot5/USBHost/USBHostMSD" -I"/home/andrea/workspace.private/CMSIS/Robot5/USBHost/USBHost3GModule" -I"/home/andrea/workspace.private/CMSIS/Robot5/USBHost/USBHostHID" -I"/home/andrea/workspace.private/CMSIS/Robot5/USBHost/mbed-rtos" -I"/home/andrea/workspace.private/CMSIS/Robot5/USBHost/mbed-rtos/rtx" -I"/home/andrea/workspace.private/CMSIS/Robot5/USBHost/mbed-rtos/rtx/TARGET_CORTEX_M" -I"/home/andrea/workspace.private/CMSIS/Robot5/USBHost/mbed-rtos/rtx/TARGET_CORTEX_M/TARGET_M3" -I"/home/andrea/workspace.private/CMSIS/Robot5/USBHost/mbed-rtos/rtx/TARGET_CORTEX_M/TARGET_M3/TOOLCHAIN_GCC" -I"/home/andrea/workspace.private/CMSIS/Robot5/USBHost/mbed-rtos/rtos" -I"/home/andrea/workspace.private/CMSIS/Robot5/USBHost/USBHostHub" -I"/home/andrea/workspace.private/CMSIS/Robot5/USBHost/USBHost" -I"/home/andrea/workspace.private/CMSIS/Robot5/USBHost/USBHostMIDI" -I"/home/andrea/workspace.private/CMSIS/Robot5/USBHost/USBHostSerial" -O0 -g3 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -fno-exceptions -fno-rtti -mcpu=cortex-m3 -mthumb -D__NEWLIB__ -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


