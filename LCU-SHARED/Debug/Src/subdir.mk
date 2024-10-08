################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (12.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Src/syscalls.c \
../Src/sysmem.c 

C_DEPS += \
./Src/syscalls.d \
./Src/sysmem.d 

OBJS += \
./Src/syscalls.o \
./Src/sysmem.o 


# Each subdirectory must supply rules for building sources it contributes
Src/%.o Src/%.su Src/%.cyclo: ../Src/%.c Src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DNucleo=8000000UL -DBoard=25000000UL -DHSE_VALUE=Board -DUSE_HAL_DRIVER -DSTM32H723xx -DDATA_IN_D2_SRAM -c -I"/opt/ST-LIB" -I"/opt/ST-LIB/Inc" -I"/opt/ST-LIB/Inc/HALAL/Models" -I"/opt/ST-LIB/Inc/HALAL/Services" -I"/opt/ST-LIB/Inc/ST-LIB_LOW" -I"/opt/ST-LIB/Inc/ST-LIB_HIGH" -I"/opt/ST-LIB/Inc/HALAL/Services/Communication" -I"/opt/ST-LIB/Inc/HALAL/Services/Communication/Ethernet" -I"/opt/ST-LIB/Inc/HALAL/Services/Communication/Ethernet/UDP" -I"/opt/ST-LIB/Inc/HALAL/Services/Communication/Ethernet/TCP" -I../Inc -I"/home/hyper/hyper/LCU/LCU-SHARED/Inc" -I../Src -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Src

clean-Src:
	-$(RM) ./Src/syscalls.cyclo ./Src/syscalls.d ./Src/syscalls.o ./Src/syscalls.su ./Src/sysmem.cyclo ./Src/sysmem.d ./Src/sysmem.o ./Src/sysmem.su

.PHONY: clean-Src

