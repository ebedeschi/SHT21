################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

CG_TOOL_ROOT := C:/tiv6_2/ccsv6/tools/compiler/ti-cgt-msp430_4.4.5

GEN_OPTS__FLAG := 
GEN_CMDS__FLAG := 

ORDERED_OBJS += \
"./main_SHT21.obj" \
"./shtLib.obj" \
"../lnk_msp430fr5969.cmd" \
$(GEN_CMDS__FLAG) \
-llibmpu_init.a \
-l"libc.a" \
-l"libmath.a" \

-include ../makefile.init

RM := DEL /F
RMDIR := RMDIR /S/Q

# All of the sources participating in the build are defined here
-include sources.mk
-include subdir_vars.mk
-include subdir_rules.mk
-include objects.mk

ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(S_DEPS)),)
-include $(S_DEPS)
endif
ifneq ($(strip $(S_UPPER_DEPS)),)
-include $(S_UPPER_DEPS)
endif
ifneq ($(strip $(S62_DEPS)),)
-include $(S62_DEPS)
endif
ifneq ($(strip $(C64_DEPS)),)
-include $(C64_DEPS)
endif
ifneq ($(strip $(ASM_DEPS)),)
-include $(ASM_DEPS)
endif
ifneq ($(strip $(CC_DEPS)),)
-include $(CC_DEPS)
endif
ifneq ($(strip $(S55_DEPS)),)
-include $(S55_DEPS)
endif
ifneq ($(strip $(C67_DEPS)),)
-include $(C67_DEPS)
endif
ifneq ($(strip $(CLA_DEPS)),)
-include $(CLA_DEPS)
endif
ifneq ($(strip $(C??_DEPS)),)
-include $(C??_DEPS)
endif
ifneq ($(strip $(CPP_DEPS)),)
-include $(CPP_DEPS)
endif
ifneq ($(strip $(S??_DEPS)),)
-include $(S??_DEPS)
endif
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
ifneq ($(strip $(C62_DEPS)),)
-include $(C62_DEPS)
endif
ifneq ($(strip $(CXX_DEPS)),)
-include $(CXX_DEPS)
endif
ifneq ($(strip $(C++_DEPS)),)
-include $(C++_DEPS)
endif
ifneq ($(strip $(ASM_UPPER_DEPS)),)
-include $(ASM_UPPER_DEPS)
endif
ifneq ($(strip $(K_DEPS)),)
-include $(K_DEPS)
endif
ifneq ($(strip $(C43_DEPS)),)
-include $(C43_DEPS)
endif
ifneq ($(strip $(INO_DEPS)),)
-include $(INO_DEPS)
endif
ifneq ($(strip $(S67_DEPS)),)
-include $(S67_DEPS)
endif
ifneq ($(strip $(SA_DEPS)),)
-include $(SA_DEPS)
endif
ifneq ($(strip $(S43_DEPS)),)
-include $(S43_DEPS)
endif
ifneq ($(strip $(OPT_DEPS)),)
-include $(OPT_DEPS)
endif
ifneq ($(strip $(PDE_DEPS)),)
-include $(PDE_DEPS)
endif
ifneq ($(strip $(S64_DEPS)),)
-include $(S64_DEPS)
endif
ifneq ($(strip $(C_UPPER_DEPS)),)
-include $(C_UPPER_DEPS)
endif
ifneq ($(strip $(C55_DEPS)),)
-include $(C55_DEPS)
endif
endif

-include ../makefile.defs

# Add inputs and outputs from these tool invocations to the build variables 
EXE_OUTPUTS += \
SHT21.out \

EXE_OUTPUTS__QUOTED += \
"SHT21.out" \

BIN_OUTPUTS += \
SHT21.hex \

BIN_OUTPUTS__QUOTED += \
"SHT21.hex" \


# All Target
all: SHT21.out

# Tool invocations
SHT21.out: $(OBJS) $(CMD_SRCS) $(GEN_CMDS)
	@echo 'Building target: $@'
	@echo 'Invoking: MSP430 Linker'
	"C:/tiv6_2/ccsv6/tools/compiler/ti-cgt-msp430_4.4.5/bin/cl430" -vmspx --abi=eabi --data_model=restricted -Ooff --advice:power="all" --advice:hw_config="all" -g --define=__MSP430FR5969__ --define=_MPU_ENABLE --diag_warning=225 --display_error_number --diag_wrap=off --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU40 --printf_support=full -z -m"SHT21.map" --heap_size=160 --stack_size=160 --use_hw_mpy=F5 --cinit_hold_wdt=on -i"C:/tiv6_2/ccsv6/ccs_base/msp430/include" -i"C:/tiv6_2/ccsv6/tools/compiler/ti-cgt-msp430_4.4.5/lib" -i"C:/tiv6_2/ccsv6/tools/compiler/ti-cgt-msp430_4.4.5/include" -i"C:/tiv6_2/ccsv6/ccs_base/msp430/lib/5xx_6xx_FRxx" -i"C:/tiv6_2/ccsv6/ccs_base/msp430/lib/FR59xx" --reread_libs --priority --define=_MPU_ENABLE --warn_sections --display_error_number --diag_wrap=off --xml_link_info="SHT21_linkInfo.xml" --rom_model -o "SHT21.out" $(ORDERED_OBJS)
	@echo 'Finished building target: $@'
	@echo ' '

SHT21.hex: $(EXE_OUTPUTS)
	@echo 'Invoking: MSP430 Hex Utility'
	"C:/tiv6_2/ccsv6/tools/compiler/ti-cgt-msp430_4.4.5/bin/hex430" --memwidth=8 --romwidth=8 -o "SHT21.hex" $(EXE_OUTPUTS__QUOTED)
	@echo 'Finished building: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXE_OUTPUTS__QUOTED)$(BIN_OUTPUTS__QUOTED)
	-$(RM) "main_SHT21.pp" "shtLib.pp" 
	-$(RM) "main_SHT21.obj" "shtLib.obj" 
	-@echo 'Finished clean'
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:

-include ../makefile.targets

