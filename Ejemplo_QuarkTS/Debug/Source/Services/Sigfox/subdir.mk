################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Source/Services/Sigfox/Task_Service_Sigfox.c 

OBJS += \
./Source/Services/Sigfox/Task_Service_Sigfox.o 

C_DEPS += \
./Source/Services/Sigfox/Task_Service_Sigfox.d 


# Each subdirectory must supply rules for building sources it contributes
Source/Services/Sigfox/Task_Service_Sigfox.o: ../Source/Services/Sigfox/Task_Service_Sigfox.c
	arm-none-eabi-gcc "$<" -mcpu=cortex-m0plus -std=gnu11 -g3 -DSTM32L072CBTx -DUSE_FULL_LL_DRIVER -DUSE_HAL_DRIVER -DSTM32L072xx -DSTM32 -DDEBUG -DSTM32L0 -c -I../Inc -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/QuarkTS/include" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/CMSIS" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/MCU" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/WSQ" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/MIddleware/ST/STM32_USB_Device_Library/Class/CDC/Inc" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/MIddleware/ST/STM32_USB_Device_Library/Core/Inc" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/MIddleware/USB_DEVICE/App" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/MIddleware/USB_DEVICE/Target" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Drivers/Inc" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/Drivers/Debounce" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/Drivers/SigFox" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/Services/Sigfox" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/Services/AT_cli" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/Bsp" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/App" -I"C:/Users/Julian/Desktop/wifi_git_2021/PRJ_IBUTTON_WSQ/FW/Ejemplo_QuarkTS/Source/Drivers/Temp_Hum" -Os -ffunction-sections -fdata-sections -Wall -fstack-usage -MMD -MP -MF"Source/Services/Sigfox/Task_Service_Sigfox.d" -MT"$@" --specs=nano.specs -mfloat-abi=soft -mthumb -o "$@"

