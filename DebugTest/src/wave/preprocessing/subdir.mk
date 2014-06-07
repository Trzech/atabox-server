################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/wave/preprocessing/SilenceCuttingFilter.cpp \
../src/wave/preprocessing/SilenceCuttingFilterTest.cpp \
../src/wave/preprocessing/WavePreprocessor.cpp 

OBJS += \
./src/wave/preprocessing/SilenceCuttingFilter.o \
./src/wave/preprocessing/SilenceCuttingFilterTest.o \
./src/wave/preprocessing/WavePreprocessor.o 

CPP_DEPS += \
./src/wave/preprocessing/SilenceCuttingFilter.d \
./src/wave/preprocessing/SilenceCuttingFilterTest.d \
./src/wave/preprocessing/WavePreprocessor.d 


# Each subdirectory must supply rules for building sources it contributes
src/wave/preprocessing/%.o: ../src/wave/preprocessing/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -I../external/rocksdb_source/include -I../src -I../external/casablanca/Release/include -I../external/boost -O0 -g3 -c -fmessage-length=0 -std=c++11 -fprofile-arcs -ftest-coverage -DBOOST_LOG_DYN_LINK -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


