#ifndef __AVR_ATmega328P__
#define __AVR_ATmega328P__
#endif
#include <string.h>
#include "UART_DRIVER.h"
#include <util/delay.h>
#define F_CPU 16000000UL


unsigned char test1[]="HALLO !! \r\n";

void main(void){

    OP_MODE_t urt_t;
    SetOperatingMode(&urt_t,9600,ASY);
    UartInit();
    UART_EN_TX();
    

    while(1)
    {
        UartTransmit(test1,strlen(test1));
        _delay_ms(1000);
    }
}
