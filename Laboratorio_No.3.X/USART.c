

#include <xc.h>
void CONFIG_USART(long BAUD){
    SPBRG = (unsigned char)(((4000000/BAUD)/(64))-1);}
