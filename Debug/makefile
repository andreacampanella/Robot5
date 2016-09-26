################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include mbed/TARGET_LPC1768/TOOLCHAIN_GCC_CR/subdir.mk
-include USBHostXpad/subdir.mk
-include USBHost/mbed-rtos/rtx/TARGET_CORTEX_M/TARGET_M3/TOOLCHAIN_GCC/subdir.mk
-include USBHost/mbed-rtos/rtx/TARGET_CORTEX_M/subdir.mk
-include USBHost/mbed-rtos/rtos/subdir.mk
-include USBHost/USBHostSerial/subdir.mk
-include USBHost/USBHostMSD/subdir.mk
-include USBHost/USBHostMIDI/subdir.mk
-include USBHost/USBHostHub/subdir.mk
-include USBHost/USBHostHID/subdir.mk
-include USBHost/USBHost3GModule/subdir.mk
-include USBHost/USBHost/subdir.mk
-include USBHost/FATFileSystem/ChaN/subdir.mk
-include USBHost/FATFileSystem/subdir.mk
-include Servo/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: Robot5.axf

# Tool invocations
Robot5.axf: $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: MCU C++ Linker'
	arm-none-eabi-c++ -nostdlib -L"/home/andrea/workspace.private/CMSIS/Robot5" -L"/home/andrea/workspace.private/CMSIS/Robot5/Servo" -L"/home/andrea/workspace.private/CMSIS/Robot5/mbed" -L"/home/andrea/workspace.private/CMSIS/Robot5/mbed/TARGET_LPC1768" -L"/home/andrea/workspace.private/CMSIS/Robot5/mbed/TARGET_LPC1768/TOOLCHAIN_GCC_CR" -L"/home/andrea/workspace.private/CMSIS/Robot5/mbed/TARGET_LPC1768/TARGET_NXP" -L"/home/andrea/workspace.private/CMSIS/Robot5/mbed/TARGET_LPC1768/TARGET_NXP/TARGET_LPC176X" -L"/home/andrea/workspace.private/CMSIS/Robot5/mbed/TARGET_LPC1768/TARGET_NXP/TARGET_LPC176X/TARGET_MBED_LPC1768" -L"/home/andrea/workspace.private/CMSIS/Robot5/USBHostXpad" -L"/home/andrea/workspace.private/CMSIS/Robot5/USBHost" -L"/home/andrea/workspace.private/CMSIS/Robot5/USBHost/FATFileSystem" -L"/home/andrea/workspace.private/CMSIS/Robot5/USBHost/FATFileSystem/ChaN" -L"/home/andrea/workspace.private/CMSIS/Robot5/USBHost/USBHostMSD" -L"/home/andrea/workspace.private/CMSIS/Robot5/USBHost/USBHost3GModule" -L"/home/andrea/workspace.private/CMSIS/Robot5/USBHost/USBHostHID" -L"/home/andrea/workspace.private/CMSIS/Robot5/USBHost/mbed-rtos" -L"/home/andrea/workspace.private/CMSIS/Robot5/USBHost/mbed-rtos/rtx" -L"/home/andrea/workspace.private/CMSIS/Robot5/USBHost/mbed-rtos/rtx/TARGET_CORTEX_M" -L"/home/andrea/workspace.private/CMSIS/Robot5/USBHost/mbed-rtos/rtx/TARGET_CORTEX_M/TARGET_M3" -L"/home/andrea/workspace.private/CMSIS/Robot5/USBHost/mbed-rtos/rtx/TARGET_CORTEX_M/TARGET_M3/TOOLCHAIN_GCC" -L"/home/andrea/workspace.private/CMSIS/Robot5/USBHost/mbed-rtos/rtos" -L"/home/andrea/workspace.private/CMSIS/Robot5/USBHost/USBHostHub" -L"/home/andrea/workspace.private/CMSIS/Robot5/USBHost/USBHost" -L"/home/andrea/workspace.private/CMSIS/Robot5/USBHost/USBHostMIDI" -L"/home/andrea/workspace.private/CMSIS/Robot5/USBHost/USBHostSerial" -Xlinker -Map="Robot5.map" -Xlinker --gc-sections -mcpu=cortex-m3 -mthumb -T "/home/andrea/workspace.private/CMSIS/Robot5/mbed/TARGET_LPC1768/TOOLCHAIN_GCC_CR/LPC1768.ld" -o "Robot5.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(CC_DEPS)$(C++_DEPS)$(EXECUTABLES)$(C_UPPER_DEPS)$(CXX_DEPS)$(OBJS)$(CPP_DEPS)$(C_DEPS) Robot5.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "Robot5.axf"; arm-none-eabi-objcopy -O binary "Robot5.axf" "Robot5.bin" ; # checksum -p LPC1768 -d "Robot5.bin";
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build

-include ../makefile.targets
