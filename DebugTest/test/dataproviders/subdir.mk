################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../test/dataproviders/RocksdbProviderTest.cpp 

OBJS += \
./test/dataproviders/RocksdbProviderTest.o 

CPP_DEPS += \
./test/dataproviders/RocksdbProviderTest.d 


# Each subdirectory must supply rules for building sources it contributes
test/dataproviders/%.o: ../test/dataproviders/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I../external/rocksdb_source/include -I../src -I../external/casablanca/Release/include -O0 -g3 -Wall -c -fmessage-length=0 -std=c++11 -fprofile-arcs -ftest-coverage -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

