################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: rgbLPC810_2.axf

dependents:
	-cd C:/nxp/work/CMSIS_CORE_LPC8xx/Debug && $(MAKE) clean all
	-cd C:/nxp/work/lpc800_driver_lib/Debug && $(MAKE) clean all

# Tool invocations
rgbLPC810_2.axf: $(OBJS) $(USER_OBJS) C:/nxp/work/CMSIS_CORE_LPC8xx/Debug/libCMSIS_CORE_LPC8xx.a C:/nxp/work/lpc800_driver_lib/Debug/liblpc800_driver_lib.a
	@echo 'Building target: $@'
	@echo 'Invoking: MCU Linker'
	arm-none-eabi-gcc -nostdlib -L"C:\nxp\work\CMSIS_CORE_LPC8xx\Debug" -L"C:\nxp\work\lpc800_driver_lib\Debug" -Xlinker -Map="rgbLPC810_2.map" -Xlinker --gc-sections -mcpu=cortex-m0 -mthumb -T "UART_Debug.ld" -o "rgbLPC810_2.axf" $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '
	$(MAKE) --no-print-directory post-build

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) rgbLPC810_2.axf
	-@echo ' '

post-build:
	-@echo 'Performing post-build steps'
	-arm-none-eabi-size "rgbLPC810_2.axf";arm-none-eabi-objcopy -O ihex "rgbLPC810_2.axf" "rgbLPC810_2.hex"
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY: post-build
C:/nxp/work/CMSIS_CORE_LPC8xx/Debug/libCMSIS_CORE_LPC8xx.a:
C:/nxp/work/lpc800_driver_lib/Debug/liblpc800_driver_lib.a:

-include ../makefile.targets
