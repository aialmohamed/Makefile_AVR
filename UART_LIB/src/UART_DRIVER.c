#include "UART_DRIVER.h"


ring_buffer_t rb_tx;
ring_buffer_t rb_rx;


static inline void SetBit(volatile uint8_t  *Register,uint8_t Mask,uint8_t Bit){

    *Register |=(Bit << Mask);
}
static inline void ClearBit(volatile uint8_t  *Register,uint8_t Mask,uint8_t Bit){
    *Register &=~(Bit << Mask);
}


uint8_t SetOperatingMode(uint32_t Baud,OP_MODE_t Op_mode){
    uint16_t Ubrr_Val=0;
    
    
    
    // for debugging 
    uint8_t Flag_Val=0;
    // Defult : 
    ClearBit(&UCSR0C,7,1);
    ClearBit(&UCSR0C,6,1);

    switch (Op_mode)
    {
    case ASY:
        Ubrr_Val= ((F_CPU/16/Baud))-1;
        ClearBit(&UCSR0C,7,1);
        ClearBit(&UCSR0C,6,1);
        ClearBit(&UCSR0A,1,1);
        Flag_Val=ASY_MODE;
        break;
    case ASY_D: 
        Ubrr_Val= ((F_CPU/8/Baud))-1;
        ClearBit(&UCSR0C,7,1);
        ClearBit(&UCSR0C,6,1);
        SetBit(&UCSR0A,1,1);
        Flag_Val=ASY_D_MODE;
        break;
    case SYC:
        Ubrr_Val= ((F_CPU/2/Baud))-1;
        SetBit(&UCSR0C,7,1);
        SetBit(&UCSR0C,6,1);
        Flag_Val=SYC_MODE;
        break;
    default:
        ClearBit(&UCSR0C,7,1);
        ClearBit(&UCSR0C,6,1);
        Flag_Val=OP_MODE_ERROR;
        break;
    }
    
    UBRR0H=(unsigned char)(Ubrr_Val >> 8);
    UBRR0L=(unsigned char )(Ubrr_Val);
    SetBit(&UCSR0B,3,1);
    SetBit(&UCSR0C,4,1);
    SetBit(&UCSR0C,0,1);
    SetBit(&UCSR0C,1,1);
    RBInit(&rb_tx);
    RBInit(&rb_rx);
    UART_EN_RX();
    

    return Flag_Val;
}


void UartTransmit(unsigned char *data,unsigned char bytes){

    RBWrite(&rb_tx,data,bytes);
    UART_EN_TX();
    
}

uint8_t UartRead()
{
    uint8_t data;
    if(RBLength(&rb_rx) > 0)
    {
        data=RBReadByte(&rb_rx);
    }
    UDR0=0;
    return data;
}

ISR(USART_UDRE_vect)
{
    if (RBLength(&rb_tx) > 0)
    {
        UDR0=RBReadByte(&rb_tx);
    }
    else
    {
        UART_DS_TX();   
    }
}

ISR(USART_RX_vect)
{
    RBWriteByte(&rb_rx,UDR0);
    
}

