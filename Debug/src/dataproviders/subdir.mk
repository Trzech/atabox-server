################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/dataproviders/FileDataProvider.cpp 

OBJS += \
./src/dataproviders/FileDataProvider.o 

CPP_DEPS += \
./src/dataproviders/FileDataProvider.d 


# Each subdirectory must supply rules for building sources it contributes
src/dataproviders/%.o: ../src/dataproviders/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++0x -D__GXX_EXPERIMENTAL_CXX0X__ -I../external/rocksdb_source/include -I../src -I../external/casablanca/Release/include -I../external/boost -I../external/kiss_fft -O0 -g3 -c -fmessage-length=0 -std=c++11 -fprofile-arcs -ftest-coverage -DBOOST_LOG_DYN_LINK -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


