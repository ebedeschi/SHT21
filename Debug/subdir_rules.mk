################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Each subdirectory must supply rules for building sources it contributes
main_SHT21.obj: ../main_SHT21.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"C:/tiv6_2/ccsv6/tools/compiler/ti-cgt-msp430_4.4.5/bin/cl430" -vmspx --abi=eabi --data_model=restricted -Ooff --include_path="C:/tiv6_2/ccsv6/ccs_base/msp430/include" --include_path="C:/tiv6_2/ccsv6/tools/compiler/ti-cgt-msp430_4.4.5/include" --advice:power="all" --advice:hw_config="all" -g --define=__MSP430FR5969__ --define=_MPU_ENABLE --diag_warning=225 --display_error_number --diag_wrap=off --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU40 --printf_support=full --preproc_with_compile --preproc_dependency="main_SHT21.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '

shtLib.obj: ../shtLib.c $(GEN_OPTS) $(GEN_HDRS)
	@echo 'Building file: $<'
	@echo 'Invoking: MSP430 Compiler'
	"C:/tiv6_2/ccsv6/tools/compiler/ti-cgt-msp430_4.4.5/bin/cl430" -vmspx --abi=eabi --data_model=restricted -Ooff --include_path="C:/tiv6_2/ccsv6/ccs_base/msp430/include" --include_path="C:/tiv6_2/ccsv6/tools/compiler/ti-cgt-msp430_4.4.5/include" --advice:power="all" --advice:hw_config="all" -g --define=__MSP430FR5969__ --define=_MPU_ENABLE --diag_warning=225 --display_error_number --diag_wrap=off --silicon_errata=CPU21 --silicon_errata=CPU22 --silicon_errata=CPU40 --printf_support=full --preproc_with_compile --preproc_dependency="shtLib.pp" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: $<'
	@echo ' '


