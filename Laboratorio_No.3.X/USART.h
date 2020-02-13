#ifndef __USART_H_
#define	__USART_H_

#include <xc.h> 
void CONFIG_USART(long);
void USART_tx(char);
char USART_rx(void);

#endif	
