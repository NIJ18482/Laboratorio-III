/******************************************************************************/
/* AUTOR: LUIS JAVIER NIJ CULAJAY                                             */
/* FECHA: ENERO DE 2020                                                       */
/*                                                                            */                                   
/* ESTA LIBRER�A, CONSTITUYE UN CONGLOMERADO DE FUNCIONES ESPECIALES PARA EL  */
/* USO E IMPLEMENTACI�N DEL M�DULO DE CONVERSI�N ADC DEL MICROCONTROLADOR PIC */
/* MODELO 16F887 Y SUS VARIANTES APLICABLES.                                  */
/* TODA COMERCIALIZACI�N NO AUTORIZADA DE LA SIGUIENTE LIBRER�A LOS METER� EN */
/* BRONCAS CON EL AUTOR, Y ES BRAVO ASI QUE AGUAS.                            */
/* POR UNA GUATEMALA EN PAZ, REPORT� GUATEVISI�N                              */
#include <xc.h>
#include <stdint.h>
#include "LCD.h"
#include "DELAYS.h"



void INIT_LCD(void){
    TRISRS = 0;
    TRISEN = 0;
    PORTRIS = 0b00000000;
    RS = 0;
    EN = 0; 
    PUERTO = 0;
    delay_ms(50);
    LCD_CONTROL(0x02);
    LCD_CONTROL(0x38);
    LCD_CONTROL(0x0C);
    LCD_CONTROL(0x06);}

void LCD_CONTROL (uint8_t dato){
    RS = 0;
    PUERTO = dato;
    LCD_PULSE();
    delay_ms(2);}

void LCD_PULSE (void){
    EN = 1;
    delay_us(5);
    EN = 0;
    delay_us(5);}

void LCD_DATO(uint8_t comando){
    RS = 1;
    PUERTO = comando;
    LCD_PULSE();
    delay_us(50);
}

void LCD_CLEAR (void){
    LCD_CONTROL(0x01);}


void LCD_PRINT(char*data){
    while(*data){
        LCD_DATO (*data);
        data++;}}

void LCD_RH(void){LCD_CONTROL(0x02);}

void LCD_PRINT_WP(int x, int y, char*frase){
    char location;
    switch(y){
        case 1:
            location = 0x80 + x;
            break;
        case 2:
            location = 0xC0 + x;
            break;
        default:
            location = 0x80 + x;}
    LCD_CONTROL(location);
    LCD_PRINT(frase);
}

