################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Draw2DCharArray.c \
../Separator.c \
../SeparatorMap.c \
../ioHelper.c 

OBJS += \
./Draw2DCharArray.o \
./Separator.o \
./SeparatorMap.o \
./ioHelper.o 

C_DEPS += \
./Draw2DCharArray.d \
./Separator.d \
./SeparatorMap.d \
./ioHelper.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


