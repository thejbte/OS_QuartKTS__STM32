################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
S_SRCS += \
../MCU/startup_stm32l072cbtx.s 

C_SRCS += \
../MCU/sysmem.c \
../MCU/system_stm32l0xx.c 

OBJS += \
./MCU/startup_stm32l072cbtx.o \
./MCU/sysmem.o \
./MCU/system_stm32l0xx.o 

C_DEPS += \
./MCU/sysmem.d \
./MCU/system_stm32l0xx.d 


# Each subdirectory must supply rules for building sources it contributes
MCU/%.o: ../MCU/%.s
	arm-none-eabi-gcc -mcpu=cortex-m0plus -g3 -c -x assembler-with-cpp --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@" "$<"
MCU/sysmem.o: ../MCU/sysmem.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DSTM32L072CBTx -DUSE_FULL_LL_DRIVER -DUSE_HAL_DRIVER -DSTM32L072xx -DSTM32 -DDEBUG -DSTM32L0 -c -I../Inc -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/QuarkTS/include" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/CMSIS" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/MCU" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/WSQ" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/MIddleware/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/MIddleware/ST/STM32_USB_Device_Library/Core/Inc" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/MIddleware/USB_DEVICE/App" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/MIddleware/USB_DEVICE/Target" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Drivers/Inc" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/Drivers/Debounce" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/Drivers/SigFox" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/Services/Sigfox" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/Services/AT_cli" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/Bsp" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/App" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/Drivers/Temp_Hum" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"MCU/sysmem.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"
MCU/system_stm32l0xx.o: ../MCU/system_stm32l0xx.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DSTM32L072CBTx -DUSE_FULL_LL_DRIVER -DUSE_HAL_DRIVER -DSTM32L072xx -DSTM32 -DDEBUG -DSTM32L0 -c -I../Inc -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/QuarkTS/include" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/CMSIS" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/MCU" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/WSQ" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/MIddleware/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/MIddleware/ST/STM32_USB_Device_Library/Core/Inc" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/MIddleware/USB_DEVICE/App" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/MIddleware/USB_DEVICE/Target" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Drivers/Inc" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/Drivers/Debounce" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/Drivers/SigFox" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/Services/Sigfox" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/Services/AT_cli" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/Bsp" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/App" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/Drivers/Temp_Hum" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"MCU/system_stm32l0xx.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

