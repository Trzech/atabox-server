################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/utils/DanielsonLanczos.cpp 

OBJS += \
./src/utils/DanielsonLanczos.o 

CPP_DEPS += \
./src/utils/DanielsonLanczos.d 


# Each subdirectory must supply rules for building sources it contributes
src/utils/%.o: ../src/utils/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++-4.8 -std=c++1y -I"/home/aldor/workspace/atabox-server/external/rocksdb_source/include" -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


