#include "UART_DRIVER.h"


ring_buffer_t rb_tx;
ring_buffer_t rb_rx;


static inline void SetBit(volatile uint8_t  *Register,uint8_t Mask,uint8_t Bit){

    *Register |=(Bit << Mask);
}
static inline void ClearBit(volatile uint8_t  *Register,uint8_t Mask,uint8_t Bit){
    *Register &=~(Bit << Mask);
}


uint8_t SetOperatingMode(UART_OP_T* Uart_Operating_Configs,uint32_t Baud,OP_MODE_t Op_mode){
    uint16_t Ubrr_Val=0;
    
    Uart_Operating_Configs->Baud=Baud;
    Uart_Operating_Configs->operation_mode=Op_mode;
    // for debugging 
    uint8_t Flag_Val=0;
    // Defult : 
    ClearBit(&UCSR0C,7,1);
    ClearBit(&UCSR0C,6,1);

    switch (Uart_Operating_Configs->operation_mode)
    {
    case ASY:
        Ubrr_Val= ((F_CPU/16/Uart_Operating_Configs->Baud))-1;
        ClearBit(&UCSR0C,7,1);
        ClearBit(&UCSR0C,6,1);
        Flag_Val=ASY_MODE;
        break;
    case ASY_D: 
        Ubrr_Val= ((F_CPU/8/Uart_Operating_Configs->Baud))-1;
        ClearBit(&UCSR0C,7,1);
        ClearBit(&UCSR0C,6,1);
        Flag_Val=ASY_D_MODE;
        break;
    case SYC:
        Ubrr_Val= ((F_CPU/2/Uart_Operating_Configs->Baud))-1;
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

    return Flag_Val;
}

void UartInit(){
    UCSR0B = 1<<RXEN0 | 1<<TXEN0;
    RBInit(&rb_tx);
    RBInit(&rb_rx);
    UART_EN_RX();
}

void UartTransmit(unsigned char *data,unsigned char bytes){

    RBWrite(&rb_tx,data,bytes);
    
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

