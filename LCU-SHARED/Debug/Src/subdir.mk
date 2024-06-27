################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (10.3-2021.10)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/syscalls.c \
../Src/sysmem.c 

OBJS += \
./Src/syscalls.o \
./Src/sysmem.o 

C_DEPS += \
./Src/syscalls.d \
./Src/sysmem.d 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DNucleo=8000000UL -DBoard=25000000UL -DHSE_VALUE=Board -DUSE_HAL_DRIVER -DSTM32H723xx -DDATA_IN_D2_SRAM -c -I"D:/hyperloop/ST-LIB" -I"D:/hyperloop/ST-LIB/Inc" -I"D:/hyperloop/ST-LIB/Inc/HALAL/Models" -I"D:/hyperloop/ST-LIB/Inc/HALAL/Services" -I"D:/hyperloop/ST-LIB/Inc/ST-LIB_LOW" -I"D:/hyperloop/ST-LIB/Inc/ST-LIB_HIGH" -I"D:/hyperloop/ST-LIB/Inc/HALAL/Services/Communication" -I"D:/hyperloop/ST-LIB/Inc/HALAL/Services/Communication/Ethernet" -I"D:/hyperloop/ST-LIB/Inc/HALAL/Services/Communication/Ethernet/UDP" -I"D:/hyperloop/ST-LIB/Inc/HALAL/Services/Communication/Ethernet/TCP" -I../Inc -I"D:/hyperloop/LCU-H9/LCU-SHARED/Inc" -I../Src -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/syscalls.d ./Src/syscalls.o ./Src/syscalls.su ./Src/sysmem.d ./Src/sysmem.o ./Src/sysmem.su

.PHONY: clean-Src

