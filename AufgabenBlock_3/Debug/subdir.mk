################################################################################
# Automatically-generated file. Do not edit!
################################################################################

# Add inputs and outputs from these tool invocations to the build variables 
CPP_SRCS += \
../SimuClient.cpp \
../SimuClientSocket.cpp 

CPP_DEPS += \
./SimuClient.d \
./SimuClientSocket.d 

OBJS += \
./SimuClient.o \
./SimuClientSocket.o 


# Each subdirectory must supply rules for building sources it contributes
%.o: ../%.cpp subdir.mk
	@echo 'Building file: $<'
	@echo 'Invoking: GCC C++ Compiler'
	g++ -std=c++17 -I/Users/lmlst/Documents/Documents/CISC124/Aufgabenblock_3 -I/Users/lmlst/boost -O0 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$@" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '


clean: clean--2e-

clean--2e-:
	-$(RM) ./SimuClient.d ./SimuClient.o ./SimuClientSocket.d ./SimuClientSocket.o

.PHONY: clean--2e-

