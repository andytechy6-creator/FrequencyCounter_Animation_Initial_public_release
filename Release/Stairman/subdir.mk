################################################################################
# Automatically-generated file. Do not edit!
# Toolchain: GNU Tools for STM32 (13.3.rel1)
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Stairman/Stairman.c \
../Stairman/stairman1.c \
../Stairman/stairman10.c \
../Stairman/stairman11.c \
../Stairman/stairman12.c \
../Stairman/stairman13.c \
../Stairman/stairman14.c \
../Stairman/stairman15.c \
../Stairman/stairman16.c \
../Stairman/stairman17.c \
../Stairman/stairman18.c \
../Stairman/stairman19.c \
../Stairman/stairman2.c \
../Stairman/stairman20.c \
../Stairman/stairman21.c \
../Stairman/stairman22.c \
../Stairman/stairman23.c \
../Stairman/stairman24.c \
../Stairman/stairman25.c \
../Stairman/stairman26.c \
../Stairman/stairman27.c \
../Stairman/stairman28.c \
../Stairman/stairman3.c \
../Stairman/stairman4.c \
../Stairman/stairman5.c \
../Stairman/stairman6.c \
../Stairman/stairman7.c \
../Stairman/stairman8.c \
../Stairman/stairman9.c \
../Stairman/stairmanfront.c 

OBJS += \
./Stairman/Stairman.o \
./Stairman/stairman1.o \
./Stairman/stairman10.o \
./Stairman/stairman11.o \
./Stairman/stairman12.o \
./Stairman/stairman13.o \
./Stairman/stairman14.o \
./Stairman/stairman15.o \
./Stairman/stairman16.o \
./Stairman/stairman17.o \
./Stairman/stairman18.o \
./Stairman/stairman19.o \
./Stairman/stairman2.o \
./Stairman/stairman20.o \
./Stairman/stairman21.o \
./Stairman/stairman22.o \
./Stairman/stairman23.o \
./Stairman/stairman24.o \
./Stairman/stairman25.o \
./Stairman/stairman26.o \
./Stairman/stairman27.o \
./Stairman/stairman28.o \
./Stairman/stairman3.o \
./Stairman/stairman4.o \
./Stairman/stairman5.o \
./Stairman/stairman6.o \
./Stairman/stairman7.o \
./Stairman/stairman8.o \
./Stairman/stairman9.o \
./Stairman/stairmanfront.o 

C_DEPS += \
./Stairman/Stairman.d \
./Stairman/stairman1.d \
./Stairman/stairman10.d \
./Stairman/stairman11.d \
./Stairman/stairman12.d \
./Stairman/stairman13.d \
./Stairman/stairman14.d \
./Stairman/stairman15.d \
./Stairman/stairman16.d \
./Stairman/stairman17.d \
./Stairman/stairman18.d \
./Stairman/stairman19.d \
./Stairman/stairman2.d \
./Stairman/stairman20.d \
./Stairman/stairman21.d \
./Stairman/stairman22.d \
./Stairman/stairman23.d \
./Stairman/stairman24.d \
./Stairman/stairman25.d \
./Stairman/stairman26.d \
./Stairman/stairman27.d \
./Stairman/stairman28.d \
./Stairman/stairman3.d \
./Stairman/stairman4.d \
./Stairman/stairman5.d \
./Stairman/stairman6.d \
./Stairman/stairman7.d \
./Stairman/stairman8.d \
./Stairman/stairman9.d \
./Stairman/stairmanfront.d 


# Each subdirectory must supply rules for building sources it contributes
Stairman/%.o Stairman/%.su Stairman/%.cyclo: ../Stairman/%.c Stairman/subdir.mk
	arm-none-eabi-gcc "$<" -mcpu=cortex-m3 -std=gnu11 -DUSE_FULL_LL_DRIVER -DSTM32F103xB -DHSE_VALUE=8000000 -DHSE_STARTUP_TIMEOUT=100 -DLSE_STARTUP_TIMEOUT=5000 -DLSE_VALUE=32768 -DHSI_VALUE=8000000 -DLSI_VALUE=40000 -DVDD_VALUE=3300 -DPREFETCH_ENABLE=1 -c -I../Core/Inc -I../Drivers/STM32F1xx_HAL_Driver/Inc -I../Drivers/CMSIS/Device/ST/STM32F1xx/Include -I../Drivers/CMSIS/Include -I"C:/Users/andyx/STM32CubeIDE/Fresh_WorkSpace/FrequencyCounter_Animation/ll_Lib/inc" -I"C:/Users/andyx/STM32CubeIDE/Fresh_WorkSpace/FrequencyCounter_Animation/Stairman" -I"C:/Users/andyx/STM32CubeIDE/Fresh_WorkSpace/FrequencyCounter_Animation/CaptureLib/fpCounter/inc" -O1 -ffunction-sections -fdata-sections -Wall -fstack-usage -fcyclomatic-complexity -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

clean: clean-Stairman

clean-Stairman:
	-$(RM) ./Stairman/Stairman.cyclo ./Stairman/Stairman.d ./Stairman/Stairman.o ./Stairman/Stairman.su ./Stairman/stairman1.cyclo ./Stairman/stairman1.d ./Stairman/stairman1.o ./Stairman/stairman1.su ./Stairman/stairman10.cyclo ./Stairman/stairman10.d ./Stairman/stairman10.o ./Stairman/stairman10.su ./Stairman/stairman11.cyclo ./Stairman/stairman11.d ./Stairman/stairman11.o ./Stairman/stairman11.su ./Stairman/stairman12.cyclo ./Stairman/stairman12.d ./Stairman/stairman12.o ./Stairman/stairman12.su ./Stairman/stairman13.cyclo ./Stairman/stairman13.d ./Stairman/stairman13.o ./Stairman/stairman13.su ./Stairman/stairman14.cyclo ./Stairman/stairman14.d ./Stairman/stairman14.o ./Stairman/stairman14.su ./Stairman/stairman15.cyclo ./Stairman/stairman15.d ./Stairman/stairman15.o ./Stairman/stairman15.su ./Stairman/stairman16.cyclo ./Stairman/stairman16.d ./Stairman/stairman16.o ./Stairman/stairman16.su ./Stairman/stairman17.cyclo ./Stairman/stairman17.d ./Stairman/stairman17.o ./Stairman/stairman17.su ./Stairman/stairman18.cyclo ./Stairman/stairman18.d ./Stairman/stairman18.o ./Stairman/stairman18.su ./Stairman/stairman19.cyclo ./Stairman/stairman19.d ./Stairman/stairman19.o ./Stairman/stairman19.su ./Stairman/stairman2.cyclo ./Stairman/stairman2.d ./Stairman/stairman2.o ./Stairman/stairman2.su ./Stairman/stairman20.cyclo ./Stairman/stairman20.d ./Stairman/stairman20.o ./Stairman/stairman20.su ./Stairman/stairman21.cyclo ./Stairman/stairman21.d ./Stairman/stairman21.o ./Stairman/stairman21.su ./Stairman/stairman22.cyclo ./Stairman/stairman22.d ./Stairman/stairman22.o ./Stairman/stairman22.su ./Stairman/stairman23.cyclo ./Stairman/stairman23.d ./Stairman/stairman23.o ./Stairman/stairman23.su ./Stairman/stairman24.cyclo ./Stairman/stairman24.d ./Stairman/stairman24.o ./Stairman/stairman24.su ./Stairman/stairman25.cyclo ./Stairman/stairman25.d ./Stairman/stairman25.o ./Stairman/stairman25.su ./Stairman/stairman26.cyclo ./Stairman/stairman26.d ./Stairman/stairman26.o ./Stairman/stairman26.su ./Stairman/stairman27.cyclo ./Stairman/stairman27.d ./Stairman/stairman27.o ./Stairman/stairman27.su ./Stairman/stairman28.cyclo ./Stairman/stairman28.d ./Stairman/stairman28.o ./Stairman/stairman28.su ./Stairman/stairman3.cyclo ./Stairman/stairman3.d ./Stairman/stairman3.o ./Stairman/stairman3.su ./Stairman/stairman4.cyclo ./Stairman/stairman4.d ./Stairman/stairman4.o ./Stairman/stairman4.su ./Stairman/stairman5.cyclo ./Stairman/stairman5.d ./Stairman/stairman5.o ./Stairman/stairman5.su ./Stairman/stairman6.cyclo ./Stairman/stairman6.d ./Stairman/stairman6.o ./Stairman/stairman6.su ./Stairman/stairman7.cyclo ./Stairman/stairman7.d ./Stairman/stairman7.o ./Stairman/stairman7.su ./Stairman/stairman8.cyclo ./Stairman/stairman8.d ./Stairman/stairman8.o ./Stairman/stairman8.su ./Stairman/stairman9.cyclo ./Stairman/stairman9.d ./Stairman/stairman9.o ./Stairman/stairman9.su ./Stairman/stairmanfront.cyclo ./Stairman/stairmanfront.d ./Stairman/stairmanfront.o ./Stairman/stairmanfront.su

.PHONY: clean-Stairman

