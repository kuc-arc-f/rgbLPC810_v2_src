################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../src/cr_startup_lpc8xx.c \
../src/crp.c \
../src/main.c \
../src/mrt.c \
../src/system_LPC8xx.c \
../src/uart.c 

OBJS += \
./src/cr_startup_lpc8xx.o \
./src/crp.o \
./src/main.o \
./src/mrt.o \
./src/system_LPC8xx.o \
./src/uart.o 

C_DEPS += \
./src/cr_startup_lpc8xx.d \
./src/crp.d \
./src/main.d \
./src/mrt.d \
./src/system_LPC8xx.d \
./src/uart.d 


# Each subdirectory must supply rules for building sources it contributes
src/cr_startup_lpc8xx.o: ../src/cr_startup_lpc8xx.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DDEBUG -D__CODE_RED -D__USE_CMSIS=CMSIS_CORE_LPC8xx -D__LPC8XX__ -I"C:\nxp\work\lpc800_driver_lib" -I"C:\nxp\work\CMSIS_CORE_LPC8xx" -I"C:\nxp\work\CMSIS_CORE_LPC8xx\inc" -I"C:\nxp\work\lpc800_driver_lib\inc" -Os -g1 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m0 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"src/cr_startup_lpc8xx.d" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: MCU C Compiler'
	arm-none-eabi-gcc -D__REDLIB__ -DDEBUG -D__CODE_RED -D__USE_CMSIS=CMSIS_CORE_LPC8xx -D__LPC8XX__ -I"C:\nxp\work\lpc800_driver_lib" -I"C:\nxp\work\CMSIS_CORE_LPC8xx" -I"C:\nxp\work\CMSIS_CORE_LPC8xx\inc" -I"C:\nxp\work\lpc800_driver_lib\inc" -O2 -g1 -Wall -c -fmessage-length=0 -fno-builtin -ffunction-sections -fdata-sections -mcpu=cortex-m0 -mthumb -D__REDLIB__ -specs=redlib.specs -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


