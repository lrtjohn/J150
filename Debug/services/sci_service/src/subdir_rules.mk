################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL = cmd.exe

# Each subdirectory must supply rules for building sources it contributes
services/sci_service/src/%.obj: ../services/sci_service/src/%.c $(GEN_OPTS) | $(GEN_FILES)
	@echo 'Building file: "$<"'
	@echo 'Invoking: C2000 Compiler'
	"C:/ti/ccs901/ccs/tools/compiler/ti-cgt-c2000_18.12.1.LTS/bin/cl2000" -v28 -ml -mt --float_support=fpu32 --include_path="C:/git/J150/platform/pfal/isr/inc" --include_path="C:/git/J150/services/adc_service/inc" --include_path="C:/git/J150/user_lib/inc" --include_path="C:/git/J150/user/inc" --include_path="C:/git/J150/bsp/inc" --include_path="C:/git/J150/platform/prod" --include_path="C:/git/J150/platform/pfal/hal/inc" --include_path="C:/git/J150/platform/pfal/cfg/inc" --include_path="C:/git/J150/user_lib/Flash28335_API_V210/inc" --include_path="C:/git/J150/services/sci_service/inc" --include_path="C:/git/J150/services/arinc429/inc" --include_path="C:/git/J150/services/algorithm_service/inc" --include_path="C:/git/J150/services/sensor_service/inc" --include_path="C:/git/J150/platform/prod/cfg/inc" --include_path="C:/git/J150/services/gpio_service/inc" --include_path="C:/git/J150/platform/sys/inc" --include_path="C:/git/J150/services/sys_service/inc" --include_path="C:/ti/ccs901/ccs/tools/compiler/ti-cgt-c2000_18.12.1.LTS/include" -g --diag_warning=225 --diag_wrap=off --display_error_number --abi=coffabi --preproc_with_compile --preproc_dependency="services/sci_service/src/$(basename $(<F)).d_raw" --obj_directory="services/sci_service/src" $(GEN_OPTS__FLAG) "$<"
	@echo 'Finished building: "$<"'
	@echo ' '


