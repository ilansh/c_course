################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
C_SRCS += \
../Draw2DCharArray.c \
../IOHelper.c \
../Perceptron.c \
../Separator.c \
../SeparatorMap.c 

OBJS += \
./Draw2DCharArray.o \
./IOHelper.o \
./Perceptron.o \
./Separator.o \
./SeparatorMap.o 

C_DEPS += \
./Draw2DCharArray.d \
./IOHelper.d \
./Perceptron.d \
./Separator.d \
./SeparatorMap.d 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


