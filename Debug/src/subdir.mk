################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../src/Assignment3.cpp \
../src/Color.cpp \
../src/Ray.cpp \
../src/Vector4.cpp \
../src/colorKernel.cpp \
../src/geometryKernel.cpp \
../src/interpolator.cpp \
../src/rayTracer.cpp 

C_SRCS += \
../src/pic.c 

OBJS += \
./src/Assignment3.o \
./src/Color.o \
./src/Ray.o \
./src/Vector4.o \
./src/colorKernel.o \
./src/geometryKernel.o \
./src/interpolator.o \
./src/pic.o \
./src/rayTracer.o 

C_DEPS += \
./src/pic.d 

CPP_DEPS += \
./src/Assignment3.d \
./src/Color.d \
./src/Ray.d \
./src/Vector4.d \
./src/colorKernel.d \
./src/geometryKernel.d \
./src/interpolator.d \
./src/rayTracer.d 


# Each subdirectory must supply rules for building sources it contributes
src/%.o: ../src/%.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

src/%.o: ../src/%.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C Compiler'
	gcc -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o"$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


