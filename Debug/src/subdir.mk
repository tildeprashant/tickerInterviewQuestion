################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CC_SRCS += \
../src/gtest_main.cc 

CPP_SRCS += \
../src/InputReader.cpp \
../src/InputReader_test.cpp 

CC_DEPS += \
./src/gtest_main.d 

OBJS += \
./src/InputReader.o \
./src/InputReader_test.o \
./src/gtest_main.o 

CPP_DEPS += \
./src/InputReader.d \
./src/InputReader_test.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++1y -I/home/prashant/Downloads/googletest/include -I/home/prashant/Downloads/googletest/include/gtest -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/%.o: ../src/%.cc
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++1y -I/home/prashant/Downloads/googletest/include -I/home/prashant/Downloads/googletest/include/gtest -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

