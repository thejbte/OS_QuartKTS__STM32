################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Source/QuarkTS/qatcli.c \
../Source/QuarkTS/qbsbuffers.c \
../Source/QuarkTS/qclock.c \
../Source/QuarkTS/qcoroutine.c \
../Source/QuarkTS/qcritical.c \
../Source/QuarkTS/qedgecheck.c \
../Source/QuarkTS/qfsm.c \
../Source/QuarkTS/qioutils.c \
../Source/QuarkTS/qkernel.c \
../Source/QuarkTS/qlists.c \
../Source/QuarkTS/qmemmang.c \
../Source/QuarkTS/qqueues.c \
../Source/QuarkTS/qresponse.c \
../Source/QuarkTS/qstimers.c \
../Source/QuarkTS/qtasks.c \
../Source/QuarkTS/qtrace.c 

OBJS += \
./Source/QuarkTS/qatcli.o \
./Source/QuarkTS/qbsbuffers.o \
./Source/QuarkTS/qclock.o \
./Source/QuarkTS/qcoroutine.o \
./Source/QuarkTS/qcritical.o \
./Source/QuarkTS/qedgecheck.o \
./Source/QuarkTS/qfsm.o \
./Source/QuarkTS/qioutils.o \
./Source/QuarkTS/qkernel.o \
./Source/QuarkTS/qlists.o \
./Source/QuarkTS/qmemmang.o \
./Source/QuarkTS/qqueues.o \
./Source/QuarkTS/qresponse.o \
./Source/QuarkTS/qstimers.o \
./Source/QuarkTS/qtasks.o \
./Source/QuarkTS/qtrace.o 

C_DEPS += \
./Source/QuarkTS/qatcli.d \
./Source/QuarkTS/qbsbuffers.d \
./Source/QuarkTS/qclock.d \
./Source/QuarkTS/qcoroutine.d \
./Source/QuarkTS/qcritical.d \
./Source/QuarkTS/qedgecheck.d \
./Source/QuarkTS/qfsm.d \
./Source/QuarkTS/qioutils.d \
./Source/QuarkTS/qkernel.d \
./Source/QuarkTS/qlists.d \
./Source/QuarkTS/qmemmang.d \
./Source/QuarkTS/qqueues.d \
./Source/QuarkTS/qresponse.d \
./Source/QuarkTS/qstimers.d \
./Source/QuarkTS/qtasks.d \
./Source/QuarkTS/qtrace.d 


# Each subdirectory must supply rules for building sources it contributes
Source/QuarkTS/qatcli.o: ../Source/QuarkTS/qatcli.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DSTM32L072CBTx -DUSE_FULL_LL_DRIVER -DUSE_HAL_DRIVER -DSTM32L072xx -DSTM32 -DDEBUG -DSTM32L0 -c -I../Inc -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/QuarkTS/include" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/CMSIS" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/MCU" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/WSQ" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/MIddleware/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/MIddleware/ST/STM32_USB_Device_Library/Core/Inc" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/MIddleware/USB_DEVICE/App" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/MIddleware/USB_DEVICE/Target" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Drivers/Inc" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/Drivers/Debounce" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/Drivers/SigFox" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/Services/Sigfox" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/Services/AT_cli" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/Bsp" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/App" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/Drivers/Temp_Hum" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Source/QuarkTS/qatcli.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Source/QuarkTS/qbsbuffers.o: ../Source/QuarkTS/qbsbuffers.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DSTM32L072CBTx -DUSE_FULL_LL_DRIVER -DUSE_HAL_DRIVER -DSTM32L072xx -DSTM32 -DDEBUG -DSTM32L0 -c -I../Inc -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/QuarkTS/include" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/CMSIS" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/MCU" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/WSQ" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/MIddleware/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/MIddleware/ST/STM32_USB_Device_Library/Core/Inc" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/MIddleware/USB_DEVICE/App" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/MIddleware/USB_DEVICE/Target" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Drivers/Inc" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/Drivers/Debounce" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/Drivers/SigFox" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/Services/Sigfox" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/Services/AT_cli" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/Bsp" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/App" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/Drivers/Temp_Hum" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Source/QuarkTS/qbsbuffers.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Source/QuarkTS/qclock.o: ../Source/QuarkTS/qclock.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DSTM32L072CBTx -DUSE_FULL_LL_DRIVER -DUSE_HAL_DRIVER -DSTM32L072xx -DSTM32 -DDEBUG -DSTM32L0 -c -I../Inc -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/QuarkTS/include" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/CMSIS" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/MCU" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/WSQ" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/MIddleware/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/MIddleware/ST/STM32_USB_Device_Library/Core/Inc" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/MIddleware/USB_DEVICE/App" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/MIddleware/USB_DEVICE/Target" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Drivers/Inc" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/Drivers/Debounce" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/Drivers/SigFox" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/Services/Sigfox" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/Services/AT_cli" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/Bsp" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/App" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/Drivers/Temp_Hum" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Source/QuarkTS/qclock.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Source/QuarkTS/qcoroutine.o: ../Source/QuarkTS/qcoroutine.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DSTM32L072CBTx -DUSE_FULL_LL_DRIVER -DUSE_HAL_DRIVER -DSTM32L072xx -DSTM32 -DDEBUG -DSTM32L0 -c -I../Inc -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/QuarkTS/include" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/CMSIS" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/MCU" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/WSQ" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/MIddleware/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/MIddleware/ST/STM32_USB_Device_Library/Core/Inc" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/MIddleware/USB_DEVICE/App" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/MIddleware/USB_DEVICE/Target" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Drivers/Inc" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/Drivers/Debounce" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/Drivers/SigFox" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/Services/Sigfox" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/Services/AT_cli" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/Bsp" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/App" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/Drivers/Temp_Hum" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Source/QuarkTS/qcoroutine.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Source/QuarkTS/qcritical.o: ../Source/QuarkTS/qcritical.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DSTM32L072CBTx -DUSE_FULL_LL_DRIVER -DUSE_HAL_DRIVER -DSTM32L072xx -DSTM32 -DDEBUG -DSTM32L0 -c -I../Inc -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/QuarkTS/include" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/CMSIS" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/MCU" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/WSQ" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/MIddleware/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/MIddleware/ST/STM32_USB_Device_Library/Core/Inc" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/MIddleware/USB_DEVICE/App" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/MIddleware/USB_DEVICE/Target" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Drivers/Inc" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/Drivers/Debounce" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/Drivers/SigFox" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/Services/Sigfox" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/Services/AT_cli" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/Bsp" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/App" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/Drivers/Temp_Hum" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Source/QuarkTS/qcritical.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Source/QuarkTS/qedgecheck.o: ../Source/QuarkTS/qedgecheck.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DSTM32L072CBTx -DUSE_FULL_LL_DRIVER -DUSE_HAL_DRIVER -DSTM32L072xx -DSTM32 -DDEBUG -DSTM32L0 -c -I../Inc -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/QuarkTS/include" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/CMSIS" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/MCU" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/WSQ" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/MIddleware/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/MIddleware/ST/STM32_USB_Device_Library/Core/Inc" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/MIddleware/USB_DEVICE/App" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/MIddleware/USB_DEVICE/Target" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Drivers/Inc" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/Drivers/Debounce" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/Drivers/SigFox" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/Services/Sigfox" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/Services/AT_cli" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/Bsp" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/App" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/Drivers/Temp_Hum" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Source/QuarkTS/qedgecheck.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Source/QuarkTS/qfsm.o: ../Source/QuarkTS/qfsm.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DSTM32L072CBTx -DUSE_FULL_LL_DRIVER -DUSE_HAL_DRIVER -DSTM32L072xx -DSTM32 -DDEBUG -DSTM32L0 -c -I../Inc -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/QuarkTS/include" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/CMSIS" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/MCU" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/WSQ" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/MIddleware/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/MIddleware/ST/STM32_USB_Device_Library/Core/Inc" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/MIddleware/USB_DEVICE/App" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/MIddleware/USB_DEVICE/Target" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Drivers/Inc" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/Drivers/Debounce" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/Drivers/SigFox" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/Services/Sigfox" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/Services/AT_cli" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/Bsp" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/App" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/Drivers/Temp_Hum" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Source/QuarkTS/qfsm.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Source/QuarkTS/qioutils.o: ../Source/QuarkTS/qioutils.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DSTM32L072CBTx -DUSE_FULL_LL_DRIVER -DUSE_HAL_DRIVER -DSTM32L072xx -DSTM32 -DDEBUG -DSTM32L0 -c -I../Inc -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/QuarkTS/include" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/CMSIS" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/MCU" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/WSQ" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/MIddleware/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/MIddleware/ST/STM32_USB_Device_Library/Core/Inc" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/MIddleware/USB_DEVICE/App" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/MIddleware/USB_DEVICE/Target" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Drivers/Inc" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/Drivers/Debounce" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/Drivers/SigFox" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/Services/Sigfox" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/Services/AT_cli" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/Bsp" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/App" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/Drivers/Temp_Hum" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Source/QuarkTS/qioutils.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Source/QuarkTS/qkernel.o: ../Source/QuarkTS/qkernel.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DSTM32L072CBTx -DUSE_FULL_LL_DRIVER -DUSE_HAL_DRIVER -DSTM32L072xx -DSTM32 -DDEBUG -DSTM32L0 -c -I../Inc -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/QuarkTS/include" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/CMSIS" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/MCU" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/WSQ" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/MIddleware/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/MIddleware/ST/STM32_USB_Device_Library/Core/Inc" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/MIddleware/USB_DEVICE/App" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/MIddleware/USB_DEVICE/Target" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Drivers/Inc" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/Drivers/Debounce" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/Drivers/SigFox" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/Services/Sigfox" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/Services/AT_cli" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/Bsp" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/App" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/Drivers/Temp_Hum" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Source/QuarkTS/qkernel.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Source/QuarkTS/qlists.o: ../Source/QuarkTS/qlists.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DSTM32L072CBTx -DUSE_FULL_LL_DRIVER -DUSE_HAL_DRIVER -DSTM32L072xx -DSTM32 -DDEBUG -DSTM32L0 -c -I../Inc -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/QuarkTS/include" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/CMSIS" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/MCU" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/WSQ" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/MIddleware/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/MIddleware/ST/STM32_USB_Device_Library/Core/Inc" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/MIddleware/USB_DEVICE/App" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/MIddleware/USB_DEVICE/Target" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Drivers/Inc" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/Drivers/Debounce" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/Drivers/SigFox" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/Services/Sigfox" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/Services/AT_cli" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/Bsp" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/App" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/Drivers/Temp_Hum" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Source/QuarkTS/qlists.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Source/QuarkTS/qmemmang.o: ../Source/QuarkTS/qmemmang.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DSTM32L072CBTx -DUSE_FULL_LL_DRIVER -DUSE_HAL_DRIVER -DSTM32L072xx -DSTM32 -DDEBUG -DSTM32L0 -c -I../Inc -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/QuarkTS/include" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/CMSIS" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/MCU" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/WSQ" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/MIddleware/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/MIddleware/ST/STM32_USB_Device_Library/Core/Inc" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/MIddleware/USB_DEVICE/App" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/MIddleware/USB_DEVICE/Target" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Drivers/Inc" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/Drivers/Debounce" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/Drivers/SigFox" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/Services/Sigfox" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/Services/AT_cli" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/Bsp" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/App" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/Drivers/Temp_Hum" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Source/QuarkTS/qmemmang.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Source/QuarkTS/qqueues.o: ../Source/QuarkTS/qqueues.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DSTM32L072CBTx -DUSE_FULL_LL_DRIVER -DUSE_HAL_DRIVER -DSTM32L072xx -DSTM32 -DDEBUG -DSTM32L0 -c -I../Inc -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/QuarkTS/include" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/CMSIS" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/MCU" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/WSQ" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/MIddleware/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/MIddleware/ST/STM32_USB_Device_Library/Core/Inc" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/MIddleware/USB_DEVICE/App" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/MIddleware/USB_DEVICE/Target" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Drivers/Inc" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/Drivers/Debounce" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/Drivers/SigFox" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/Services/Sigfox" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/Services/AT_cli" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/Bsp" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/App" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/Drivers/Temp_Hum" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Source/QuarkTS/qqueues.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Source/QuarkTS/qresponse.o: ../Source/QuarkTS/qresponse.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DSTM32L072CBTx -DUSE_FULL_LL_DRIVER -DUSE_HAL_DRIVER -DSTM32L072xx -DSTM32 -DDEBUG -DSTM32L0 -c -I../Inc -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/QuarkTS/include" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/CMSIS" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/MCU" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/WSQ" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/MIddleware/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/MIddleware/ST/STM32_USB_Device_Library/Core/Inc" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/MIddleware/USB_DEVICE/App" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/MIddleware/USB_DEVICE/Target" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Drivers/Inc" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/Drivers/Debounce" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/Drivers/SigFox" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/Services/Sigfox" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/Services/AT_cli" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/Bsp" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/App" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/Drivers/Temp_Hum" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Source/QuarkTS/qresponse.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Source/QuarkTS/qstimers.o: ../Source/QuarkTS/qstimers.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DSTM32L072CBTx -DUSE_FULL_LL_DRIVER -DUSE_HAL_DRIVER -DSTM32L072xx -DSTM32 -DDEBUG -DSTM32L0 -c -I../Inc -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/QuarkTS/include" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/CMSIS" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/MCU" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/WSQ" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/MIddleware/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/MIddleware/ST/STM32_USB_Device_Library/Core/Inc" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/MIddleware/USB_DEVICE/App" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/MIddleware/USB_DEVICE/Target" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Drivers/Inc" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/Drivers/Debounce" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/Drivers/SigFox" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/Services/Sigfox" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/Services/AT_cli" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/Bsp" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/App" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/Drivers/Temp_Hum" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Source/QuarkTS/qstimers.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Source/QuarkTS/qtasks.o: ../Source/QuarkTS/qtasks.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DSTM32L072CBTx -DUSE_FULL_LL_DRIVER -DUSE_HAL_DRIVER -DSTM32L072xx -DSTM32 -DDEBUG -DSTM32L0 -c -I../Inc -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/QuarkTS/include" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/CMSIS" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/MCU" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/WSQ" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/MIddleware/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/MIddleware/ST/STM32_USB_Device_Library/Core/Inc" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/MIddleware/USB_DEVICE/App" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/MIddleware/USB_DEVICE/Target" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Drivers/Inc" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/Drivers/Debounce" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/Drivers/SigFox" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/Services/Sigfox" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/Services/AT_cli" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/Bsp" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/App" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/Drivers/Temp_Hum" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Source/QuarkTS/qtasks.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
Source/QuarkTS/qtrace.o: ../Source/QuarkTS/qtrace.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DSTM32L072CBTx -DUSE_FULL_LL_DRIVER -DUSE_HAL_DRIVER -DSTM32L072xx -DSTM32 -DDEBUG -DSTM32L0 -c -I../Inc -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/QuarkTS/include" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/CMSIS" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/MCU" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/WSQ" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/MIddleware/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/MIddleware/ST/STM32_USB_Device_Library/Core/Inc" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/MIddleware/USB_DEVICE/App" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/MIddleware/USB_DEVICE/Target" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Drivers/Inc" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/Drivers/Debounce" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/Drivers/SigFox" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/Services/Sigfox" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/Services/AT_cli" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/Bsp" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/App" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/Drivers/Temp_Hum" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Source/QuarkTS/qtrace.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
