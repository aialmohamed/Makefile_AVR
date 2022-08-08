#ifndef __AVR_ATmega328P__
#define __AVR_ATmega328P__
#endif
#include <stdint.h>
#include <avr/io.h>
#include <string.h>
#define F_CPU 8000000L



// Flags 
#define ASY_MODE    0
#define ASY_D_MODE  1
#define SYC_MODE    2
#define OP_MODE_ERROR 15




// Structs :
typedef struct UART_OP_T
{
    OP_MODE_t operation_mode;
    uint32_t Baud;
    
}UART_OP_T;

typedef enum {ASY,ASY_D,SYC}OP_MODE_t;




// Methods :
uint8_t SetOperatingMode(UART_OP_T* Uart_Operating_Configs);