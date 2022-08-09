#Main application file name
MAIN_APP = main
#Main hex file path in windows format
MAIN_HEX_PATH = C:\Bachalor\MT_7\MAKE_ARD\Makefile_AVR\UART_LIB\$(MAIN_APP).hex

SRC_DIR = src
INCLUDE_DIR = include
BUILD_DIR= build

# Compiler and other Section
CC = avr-gcc
OBJCOPY = avr-objcopy.exe
AVRDUDE := avrdude

#Options for avr-gcc
CFLAGS = -g -Os -o

#Linking options for avr-gcc
LFLAGS = -Os -mmcu=atmega328p -o

#Options for HEX file generation
HFLAGS = -j .text -j .data -O ihex

#Options for avrdude to burn the hex file
#MMCU model here according to avrdude options
DUDEFLAGS = -c
DUDEFLAGS += arduino 
DUDEFLAGS += -p
DUDEFLAGS += m328p  
DUDEFLAGS += -P 
DUDEFLAGS += COM3 
DUDEFLAGS += -b 
DUDEFLAGS +=  115200
DUDEFLAGS += -U flash:w:$(MAIN_HEX_PATH):i

# Sources files needed for building the application 
SRC = $(SRC_DIR)/$(MAIN_APP).c
SRC += $(SRC_DIR)/RingBuffer.c
SRC += $(SRC_DIR)/UART_DRIVER.c

# The headers files needed for building the application
INCLUDE = -I
INCLUDE += $(INCLUDE_DIR)

# commands Section
Burn : Build
	$(AVRDUDE) $(DUDEFLAGS)

Build :$(MAIN_APP).elf
	$(OBJCOPY) $(HFLAGS) $< $(MAIN_APP).hex
	
$(MAIN_APP).elf:$(MAIN_APP).o
	$(CC) $(SRC) $(INCLUDE) $(LFLAGS) $@
	
$(MAIN_APP).o:$(SRC)
	$(CC) $^ $(INCLUDE) $(CFLAGS) $@
