NAME := avrBingo
CC := avr-gcc
CXX := avr-g++
CFLAGS := -Wall -std=c11 -Os -I./include
CXXFLAGS := -Wall -std=c++11 -Os -I./include

#SRCS := $(wildcard src/*.cpp)
SRCS := src/main.cpp src/Pin.cpp src/ShiftReg.cpp src/Timer.cpp src/ADC.cpp
OBJS := $(patsubst %.cpp,%.o, $(SRCS))

MCU := attiny44a
USER := $(shell whoami)
SERIAL_PORT := /dev/ttyACM0

all: build flash

build: $(NAME).elf

strip: $(NAME).hex

flash: $(NAME).hex
	sudo chown ${USER} ${SERIAL_PORT}
	avrdude -c avrisp -p $(MCU) -P ${SERIAL_PORT} -b 19200 -U flash:w:$<:a -v

clean:
	@rm $(OBJS)

clean-all:
	@rm $(OBJS) $(NAME).hex $(NAME).elf

help:
	@echo "Make file for building bingo machine program for AVR MCU"
	@echo -e "\tbuild:\t\tbuild the ELF binary"
	@echo -e "\tstrip:\t\tstrip ELF binary into HEX binary for flashing"
	@echo -e "\tflash:\t\tflash HEX binary to MCU with avrdude"
	@echo -e "\tall:\t\tdoes all of above in one go"
	@echo -e "\tclean:\t\tclean all object files"
	@echo -e "\tclean-all:\tclean all product files including ELF and HEX binary"

%.o: %.cpp
	$(CXX) -c -mmcu=$(MCU) $(CXXFLAGS) $^ -o $@

%.hex: %.elf
	avr-objcopy -j .text -j .data -O ihex $^ $@

$(NAME).elf: $(OBJS)
	$(CXX) -mmcu=$(MCU) $^ -o $(NAME).elf

