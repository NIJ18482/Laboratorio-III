
#ifndef __LCD_H_
#define	__LCD_H_
#define RS      PORTEbits.RE0
#define EN      PORTEbits.RE1
#define TRISRS  TRISEbits.TRISE0
#define TRISEN  TRISEbits.TRISE1
#define PORTRIS TRISD
#define PUERTO  PORTD
#include <xc.h> 
#include <stdint.h>

void INIT_LCD(void);
void LCD_CLEAR(void);
void lcd_control (uint8_t);
void LCD_PULSE(void);
void LCD_DATO(uint8_t);


#endif

