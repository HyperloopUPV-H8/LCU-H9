################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: good
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Drivers/CMSIS/Device/ST/STM32H7xx/Source/Templates/system_stm32h7xx.c 

OBJS += \
./Drivers/CMSIS/Device/ST/STM32H7xx/Source/Templates/system_stm32h7xx.o 

C_DEPS += \
./Drivers/CMSIS/Device/ST/STM32H7xx/Source/Templates/system_stm32h7xx.d 


# Each subdirectory must supply rules for building sources it contributes
Drivers/CMSIS/Device/ST/STM32H7xx/Source/Templates/%.o Drivers/CMSIS/Device/ST/STM32H7xx/Source/Templates/%.su: ../Drivers/CMSIS/Device/ST/STM32H7xx/Source/Templates/%.c Drivers/CMSIS/Device/ST/STM32H7xx/Source/Templates/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m7 -std=gnu11 -g3 -DDEBUG -DNucleo=8000000UL -DBoard=25000000UL -DHSE_VALUE=Nucleo -DUSE_HAL_DRIVER -DSTM32H723xx -DDATA_IN_D2_SRAM -c -I"D:/hyperloop/ST-LIB" -I"D:/hyperloop/ST-LIB/Inc" -I"D:/hyperloop/ST-LIB/Inc/HALAL/Models" -I"D:/hyperloop/ST-LIB/Inc/HALAL/Services" -I"D:/hyperloop/ST-LIB/Inc/ST-LIB_LOW" -I"D:/hyperloop/ST-LIB/Inc/ST-LIB_HIGH" -I"D:/hyperloop/ST-LIB/Inc/HALAL/Services/Communication" -I"D:/hyperloop/ST-LIB/Inc/HALAL/Services/Communication/Ethernet" -I"D:/hyperloop/ST-LIB/Inc/HALAL/Services/Communication/Ethernet/UDP" -I"D:/hyperloop/ST-LIB/Inc/HALAL/Services/Communication/Ethernet/TCP" -I../Inc -I"D:/hyperloop/LCU-H9/LCU-SHARED/Inc" -O0 -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfpu=fpv5-d16 -mfloat-abi=hard -mthumb -o "$@"

clean: clean-Drivers-2f-CMSIS-2f-Device-2f-ST-2f-STM32H7xx-2f-Source-2f-Templates

clean-Drivers-2f-CMSIS-2f-Device-2f-ST-2f-STM32H7xx-2f-Source-2f-Templates:
	-$(RM) ./Drivers/CMSIS/Device/ST/STM32H7xx/Source/Templates/system_stm32h7xx.d ./Drivers/CMSIS/Device/ST/STM32H7xx/Source/Templates/system_stm32h7xx.o ./Drivers/CMSIS/Device/ST/STM32H7xx/Source/Templates/system_stm32h7xx.su

.PHONY: clean-Drivers-2f-CMSIS-2f-Device-2f-ST-2f-STM32H7xx-2f-Source-2f-Templates

