################################################################################
# Automatically-generated file. Do not edit!
################################################################################

-include ../makefile.init

RM := rm -rf

# All of the sources participating in the build are defined here
-include sources.mk
-include Source/WSQ/subdir.mk
-include Source/Services/Sigfox/subdir.mk
-include Source/Services/AT_cli/subdir.mk
-include Source/QuarkTS/subdir.mk
-include Source/Drivers/Temp_Hum/subdir.mk
-include Source/Drivers/SigFox/subdir.mk
-include Source/Drivers/Debounce/subdir.mk
-include Source/App/subdir.mk
-include Source/subdir.mk
-include MIddleware/USB_DEVICE/Target/subdir.mk
-include MIddleware/USB_DEVICE/App/subdir.mk
-include MIddleware/ST/STM32_USB_Device_Library/Core/Src/subdir.mk
-include MIddleware/ST/STM32_USB_Device_Library/Class/CDC/Src/subdir.mk
-include MCU/subdir.mk
-include Drivers/Src/subdir.mk
-include subdir.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXECUTABLES += \
Ejemplo_QuartkTS.elf \

SIZE_OUTPUT += \
default.size.stdout \

OBJDUMP_LIST += \
Ejemplo_QuartkTS.list \

OBJCOPY_HEX += \
Ejemplo_QuartkTS.hex \

OBJCOPY_BIN += \
Ejemplo_QuartkTS.bin \


# All Target
all: Ejemplo_QuartkTS.elf secondary-outputs

# Tool invocations
Ejemplo_QuartkTS.elf: $(OBJS) $(USER_OBJS) C:\Users\Julian\Desktop\wifi_git_2021\PRJ_IBUTTON_WSQ\FW\Ejemplo_QuarkTS\STM32L072CBTX_FLASH.ld
	arm-none-eabi-gcc -o "Ejemplo_QuartkTS.elf" @"objects.list" $(USER_OBJS) $(LIBS) -mcpu=cortex-m0plus -T"C:\Users\Julian\Desktop\wifi_git_2021\PRJ_IBUTTON_WSQ\FW\Ejemplo_QuarkTS\STM32L072CBTX_FLASH.ld" --specs=nosys.specs -Wl,-Map="Ejemplo_QuartkTS.map" -Wl,--gc-sections -static --specs=nano.specs -mfloat-abi=soft -mthumb -Wl,--start-group -lc -lm -Wl,--end-group
	@echo 'Finished building target: $@'
	@echo ' '

default.size.stdout: $(EXECUTABLES)
	arm-none-eabi-size  $(EXECUTABLES)
	@echo 'Finished building: $@'
	@echo ' '

Ejemplo_QuartkTS.list: $(EXECUTABLES)
	arm-none-eabi-objdump -h -S $(EXECUTABLES) > "Ejemplo_QuartkTS.list"
	@echo 'Finished building: $@'
	@echo ' '

Ejemplo_QuartkTS.hex: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O ihex $(EXECUTABLES) "Ejemplo_QuartkTS.hex"
	@echo 'Finished building: $@'
	@echo ' '

Ejemplo_QuartkTS.bin: $(EXECUTABLES)
	arm-none-eabi-objcopy  -O binary $(EXECUTABLES) "Ejemplo_QuartkTS.bin"
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) *
	-@echo ' '

secondary-outputs: $(SIZE_OUTPUT) $(OBJDUMP_LIST) $(OBJCOPY_HEX) $(OBJCOPY_BIN)

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets
