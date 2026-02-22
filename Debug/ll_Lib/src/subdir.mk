################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../ll_Lib/src/Font_8x10.c \
../ll_Lib/src/Image_rgb.c \
../ll_Lib/src/PulseC.c \
../ll_Lib/src/freqC.c \
../ll_Lib/src/st7735s_ll.c 

OBJS += \
./ll_Lib/src/Font_8x10.o \
./ll_Lib/src/Image_rgb.o \
./ll_Lib/src/PulseC.o \
./ll_Lib/src/freqC.o \
./ll_Lib/src/st7735s_ll.o 

C_DEPS += \
./ll_Lib/src/Font_8x10.d \
./ll_Lib/src/Image_rgb.d \
./ll_Lib/src/PulseC.d \
./ll_Lib/src/freqC.d \
./ll_Lib/src/st7735s_ll.d 


# Each subdirectory must supply rules for building sources it contributes
ll_Lib/src/%.o ll_Lib/src/%.su ll_Lib/src/%.cyclo: ../ll_Lib/src/%.c ll_Lib/src/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -g3 -DDEBUG -DUSE_FULL_LL_DRIVER -DSTM32F103xB -DHSE_VALUE=8000000 -DHSE_STARTUP_TIMEOUT=100 -DLSE_STARTUP_TIMEOUT=5000 -DLSE_VALUE=32768 -DHSI_VALUE=8000000 -DLSI_VALUE=40000 -DVDD_VALUE=3300 -DPREFETCH_ENABLE=1 -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/andyx/STM32CubeIDE/Fresh_WorkSpace/FrequencyCounter_Animation/CaptureLib/fpCounter/inc" -I"C:/Users/andyx/STM32CubeIDE/Fresh_WorkSpace/FrequencyCounter_Animation/ll_Lib/inc" -I"C:/Users/andyx/STM32CubeIDE/Fresh_WorkSpace/FrequencyCounter_Animation/Stairman" -O2 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-ll_Lib-2f-src

clean-ll_Lib-2f-src:
	-$(RM) ./ll_Lib/src/Font_8x10.cyclo ./ll_Lib/src/Font_8x10.d ./ll_Lib/src/Font_8x10.o ./ll_Lib/src/Font_8x10.su ./ll_Lib/src/Image_rgb.cyclo ./ll_Lib/src/Image_rgb.d ./ll_Lib/src/Image_rgb.o ./ll_Lib/src/Image_rgb.su ./ll_Lib/src/PulseC.cyclo ./ll_Lib/src/PulseC.d ./ll_Lib/src/PulseC.o ./ll_Lib/src/PulseC.su ./ll_Lib/src/freqC.cyclo ./ll_Lib/src/freqC.d ./ll_Lib/src/freqC.o ./ll_Lib/src/freqC.su ./ll_Lib/src/st7735s_ll.cyclo ./ll_Lib/src/st7735s_ll.d ./ll_Lib/src/st7735s_ll.o ./ll_Lib/src/st7735s_ll.su

.PHONY: clean-ll_Lib-2f-src

