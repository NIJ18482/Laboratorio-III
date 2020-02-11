/******************************************************************************/
/* AUTOR: LUIS JAVIER NIJ CULAJAY                                             */
/* FECHA: ENERO DE 2020                                                       */
/*                                                                            */                                   
/* ESTA LIBRERÍA, CONSTITUYE UN CONGLOMERADO DE FUNCIONES ESPECIALES PARA EL  */
/* USO E IMPLEMENTACIÓN DEL MÓDULO DE CONVERSIÓN ADC DEL MICROCONTROLADOR PIC */
/* MODELO 16F887 Y SUS VARIANTES APLICABLES.                                  */
/* TODA COMERCIALIZACIÓN NO AUTORIZADA DE LA SIGUIENTE LIBRERÍA LOS METERÁ EN */
/* BRONCAS CON EL AUTOR, Y ES BRAVO ASI QUE AGUAS.                            */
/* POR UNA GUATEMALA EN PAZ, REPORTÓ GUATEVISIÓN                              */
#include <xc.h>
#include <stdint.h>
#include "LCD.h"
#include "DELAYS.h"
#include <stdio.h>
#include <stdlib.h>



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
    if (y == 1){location = 0x80 + x;}
    else if (y ==2) {location = 0xC0 + x;}
    else {location = 0xC0 + x;}
    LCD_CONTROL(location);
    LCD_PRINT(frase);
}

void VAL(uint8_t result,uint8_t column){
    uint8_t unidades = 0;
    unidades = (result - (result % 51))/51;
    if (column == 0) {
        if (unidades == 0){LCD_PRINT_WP(0,2,"-0.00V");}
        else if (unidades == 1){LCD_PRINT_WP(0,2,"-1.00V");}
        else if (unidades == 2){LCD_PRINT_WP(0,2,"-2.00V");}
        else if (unidades == 3){LCD_PRINT_WP(0,2,"-3.00V");}
        else if (unidades == 4){LCD_PRINT_WP(0,2,"-4.00V");}
        else if (unidades == 5){LCD_PRINT_WP(0,2,"-5.00V");}}
    else if (column == 1){
        if (unidades == 0){LCD_PRINT_WP(6,2,"-0.00V");}
        else if (unidades == 1){LCD_PRINT_WP(6,2,"-1.00V");}
        else if (unidades == 2){LCD_PRINT_WP(6,2,"-2.00V");}
        else if (unidades == 3){LCD_PRINT_WP(6,2,"-3.00V");}
        else if (unidades == 4){LCD_PRINT_WP(6,2,"-4.00V");}
        else if (unidades == 5){LCD_PRINT_WP(6,2,"-5.00V");}}
    
    }
