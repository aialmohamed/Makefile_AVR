#ifndef __AVR_ATmega328P__
#define __AVR_ATmega328P__
#endif
#include <string.h>
#include "UART_DRIVER.h"
#include <util/delay.h>



unsigned char test1[]="data has been read\r\n";
unsigned char test2[]="No data to read\r\n";
int main(void){

    SetOperatingMode(115200,ASY_D);
    sei();
    uint8_t data=0;
    

    while(1)
    {
        data = UartRead();
        while(data == 10){
        UartTransmit(test1,strlen(test1));
        _delay_ms(1000);
        data = UartRead();
        }
        UartTransmit(test2,strlen(test1));
        _delay_ms(1000);

    }
    return;
}
