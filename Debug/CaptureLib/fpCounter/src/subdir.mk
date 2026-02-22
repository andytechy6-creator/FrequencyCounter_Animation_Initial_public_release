################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../CaptureLib/fpCounter/src/fpCounter.c 

OBJS += \
./CaptureLib/fpCounter/src/fpCounter.o 

C_DEPS += \
./CaptureLib/fpCounter/src/fpCounter.d 


# Each subdirectory must supply rules for building sources it contributes
CaptureLib/fpCounter/src/%.o CaptureLib/fpCounter/src/%.su CaptureLib/fpCounter/src/%.cyclo: ../CaptureLib/fpCounter/src/%.c CaptureLib/fpCounter/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_FULL_LL_DRIVER -DSTM32F103xB -DHSE_VALUE=8000000 -DHSE_STARTUP_TIMEOUT=100 -DLSE_STARTUP_TIMEOUT=5000 -DLSE_VALUE=32768 -DHSI_VALUE=8000000 -DLSI_VALUE=40000 -DVDD_VALUE=3300 -DPREFETCH_ENABLE=1 -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/andyx/STM32CubeIDE/Fresh_WorkSpace/FrequencyCounter_Animation/CaptureLib/fpCounter/inc" -I"C:/Users/andyx/STM32CubeIDE/Fresh_WorkSpace/FrequencyCounter_Animation/ll_Lib/inc" -I"C:/Users/andyx/STM32CubeIDE/Fresh_WorkSpace/FrequencyCounter_Animation/Stairman" -O2 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-CaptureLib-2f-fpCounter-2f-src

clean-CaptureLib-2f-fpCounter-2f-src:
	-$(RM) ./CaptureLib/fpCounter/src/fpCounter.cyclo ./CaptureLib/fpCounter/src/fpCounter.d ./CaptureLib/fpCounter/src/fpCounter.o ./CaptureLib/fpCounter/src/fpCounter.su

.PHONY: clean-CaptureLib-2f-fpCounter-2f-src

