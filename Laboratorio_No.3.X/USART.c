

#include <xc.h>
void CONFIG_USART(long BAUD){
    TRISCbits.TRISC6  = 0;   /*RC& = TX*/
    TRISCbits.TRISC7  = 1;   /*RC& = TX*/
    TXSTAbits.SYNC    = 0;  /* INDICA COMUNICACI�N SERIAL AS�NCRONA           */
    RCSTAbits.SPEN    = 1;  /* HABILITA LA TRANSMISI�N Y RECEPCI�N DE DATOS   */
    TXSTAbits.BRGH    = 0;  /*INDICA QUESER� UNA VELOCIDAD BAJA DE TRANSMISION*/
    TXSTAbits.TX9     = 0;
    TXSTAbits.TXEN    = 1;
    RCSTAbits.RC9     = 0;
    RCSTAbits.CREN    = 1;
    SPBRG = (unsigned char)(((4000000/BAUD)/(64))-1);}

void USART_tx(char data){
    TXREG = data;
}

char USART_rx(){
    return RCREG; 
}