#include "UART_DRIVER.h"


static inline void SetBit(volatile uint8_t  *Register,uint8_t Mask,uint8_t Bit){

    *Register |=(Bit << Mask);
}
static inline void ClearBit(volatile uint8_t  *Register,uint8_t Mask,uint8_t Bit){
    *Register &=~(Bit << Mask);
}


uint8_t SetOperatingMode(UART_OP_T* Uart_Operating_Configs){
    uint16_t Ubrr_Val=0;
    
    // for debugging 
    uint8_t Flag_Val=0;
    
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



