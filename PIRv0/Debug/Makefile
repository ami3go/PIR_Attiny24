################################################################################
# Automatically-generated file. Do not edit!
################################################################################

SHELL := cmd.exe
RM := rm -rf

USER_OBJS :=

LIBS := 
PROJ := 

O_SRCS := 
C_SRCS := 
S_SRCS := 
S_UPPER_SRCS := 
OBJ_SRCS := 
ASM_SRCS := 
PREPROCESSING_SRCS := 
OBJS := 
OBJS_AS_ARGS := 
C_DEPS := 
C_DEPS_AS_ARGS := 
EXECUTABLES := 
OUTPUT_FILE_PATH :=
OUTPUT_FILE_PATH_AS_ARGS :=
AVR_APP_PATH :=$$$AVR_APP_PATH$$$
QUOTE := "
ADDITIONAL_DEPENDENCIES:=
OUTPUT_FILE_DEP:=
LIB_DEP:=
LINKER_SCRIPT_DEP:=

# Every subdirectory with source files must be described here
SUBDIRS := 


# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS +=  \
../main.c


PREPROCESSING_SRCS += 


ASM_SRCS += 


OBJS +=  \
main.o

OBJS_AS_ARGS +=  \
main.o

C_DEPS +=  \
main.d

C_DEPS_AS_ARGS +=  \
main.d

OUTPUT_FILE_PATH +=PIRv0.elf

OUTPUT_FILE_PATH_AS_ARGS +=PIRv0.elf

ADDITIONAL_DEPENDENCIES:=

OUTPUT_FILE_DEP:= ./makedep.mk

LIB_DEP+= 

LINKER_SCRIPT_DEP+= 


# AVR32/GNU C Compiler



./%.o: .././%.c
	@echo Building file: $<
	@echo Invoking: AVR/GNU C Compiler : 4.3.3
	$(QUOTE)C:\WinAVR-20100110\bin\avr-gcc.exe$(QUOTE)  -x c -funsigned-char -funsigned-bitfields -DDEBUG  -I"C:\Program Files (x86)\Atmel\Studio\7.0\Packs\Atmel\ATtiny_DFP\1.3.172\include"  -O1 -ffunction-sections -fdata-sections -fpack-struct -fshort-enums -g2 -Wall  -mmcu=attiny24a  -c -std=gnu99 -MD -MP -MF "$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -MT"$(@:%.o=%.o)"   -o "$@" "$<" 
	@echo Finished building: $<
	



# AVR32/GNU Preprocessing Assembler



# AVR32/GNU Assembler




ifneq ($(MAKECMDGOALS),clean)
ifneq ($(strip $(C_DEPS)),)
-include $(C_DEPS)
endif
endif

# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: $(OUTPUT_FILE_PATH) $(ADDITIONAL_DEPENDENCIES)

$(OUTPUT_FILE_PATH): $(OBJS) $(USER_OBJS) $(OUTPUT_FILE_DEP) $(LIB_DEP) $(LINKER_SCRIPT_DEP)
	@echo Building target: $@
	@echo Invoking: AVR/GNU Linker : 4.3.3
	$(QUOTE)C:\WinAVR-20100110\bin\avr-gcc.exe$(QUOTE) -o$(OUTPUT_FILE_PATH_AS_ARGS) $(OBJS_AS_ARGS) $(USER_OBJS) $(LIBS) -Wl,-Map="PIRv0.map" -Wl,--start-group -Wl,-lm  -Wl,--end-group -Wl,-L"D:\DOCs\Dropbox\Freelance\Pir\Firmware\AVR_studio\PIRv0" -Wl,-L"D:\DOCs\Dropbox\Freelance\Pir\Firmware\AVR_studio\PIRv0\PIRv0"  -Wl,--gc-sections  -mmcu=attiny24a   
	@echo Finished building target: $@
	"C:\WinAVR-20100110\bin\avr-objcopy.exe" -O ihex -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures  "PIRv0.elf" "PIRv0.hex"
	"C:\WinAVR-20100110\bin\avr-objcopy.exe" -j .eeprom  --set-section-flags=.eeprom=alloc,load --change-section-lma .eeprom=0  --no-change-warnings -O ihex "PIRv0.elf" "PIRv0.eep" || exit 0
	"C:\WinAVR-20100110\bin\avr-objdump.exe" -h -S "PIRv0.elf" > "PIRv0.lss"
	"C:\WinAVR-20100110\bin\avr-objcopy.exe" -O srec -R .eeprom -R .fuse -R .lock -R .signature -R .user_signatures "PIRv0.elf" "PIRv0.srec"
	"C:\WinAVR-20100110\bin\avr-size.exe" "PIRv0.elf"
	
	





# Other Targets
clean:
	-$(RM) $(OBJS_AS_ARGS) $(EXECUTABLES)  
	-$(RM) $(C_DEPS_AS_ARGS)   
	rm -rf "PIRv0.elf" "PIRv0.a" "PIRv0.hex" "PIRv0.lss" "PIRv0.eep" "PIRv0.map" "PIRv0.srec" "PIRv0.usersignatures"
	