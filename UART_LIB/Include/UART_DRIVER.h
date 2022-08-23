#ifndef __AVR_ATmega328P__
#define __AVR_ATmega328P__
#endif
#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <string.h>
#include "RingBuffer.h"
#define F_CPU 16000000UL


#define UART_EN_TX()        UCSR0B |=(1<<UDRIE0)
#define UART_DS_TX()        UCSR0B &=~(1<<UDRIE0)


#define UART_EN_RX()        UCSR0B |=(1<<RXCIE0)
#define UART_DS_RX()        UCSR0B &=~(1<<RXCIE0)

// Flags 
#define ASY_MODE    0
#define ASY_D_MODE  1
#define SYC_MODE    2
#define OP_MODE_ERROR 15



typedef enum {ASY,ASY_D,SYC}OP_MODE_t;
// Structs :


// Enums 





// Methods :
uint8_t SetOperatingMode(uint32_t Baud,OP_MODE_t Op_mode);
void UartTransmit(unsigned char *data,unsigned char bytes);
uint8_t UartRead();