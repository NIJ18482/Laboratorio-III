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
    if (result>=250){result = 250;}
    uint8_t valor      = 0;
    uint8_t coordenada = 0;
    uint8_t unidades        = (result - (result % 50))/50;
    uint8_t decimas         = ((result %50) -((result %50)%5))/5;
    uint8_t centesimas      = (((result %50)%5) -(((result %50)%5)%1))*2;
    int numero[] = {unidades,decimas,centesimas};  
    if (column == 0){
        for (int i=0; i<3;i++){
            valor = numero[i];
            if (i == 0) {coordenada = 1;}
            if (i == 1) {coordenada = 3;}
            if (i == 2) {coordenada = 4;}
            if (valor == 0){LCD_PRINT_WP(coordenada,2,"0");}
            if (valor == 1){LCD_PRINT_WP(coordenada,2,"1");}
            if (valor == 2){LCD_PRINT_WP(coordenada,2,"2");}
            if (valor == 3){LCD_PRINT_WP(coordenada,2,"3");}
            if (valor == 4){LCD_PRINT_WP(coordenada,2,"4");}
            if (valor == 5){LCD_PRINT_WP(coordenada,2,"5");}
            if (valor == 6){LCD_PRINT_WP(coordenada,2,"6");}
            if (valor == 7){LCD_PRINT_WP(coordenada,2,"7");}
            if (valor == 8){LCD_PRINT_WP(coordenada,2,"8");}
            if (valor == 9){LCD_PRINT_WP(coordenada,2,"9");}}}
    if (column == 1){
            for (int i=0; i<3;i++){
                valor = numero[i];
                if (i == 0) {coordenada = 7;}
                if (i == 1) {coordenada = 9;}
                if (i == 2) {coordenada = 10;}
                if (valor == 0){LCD_PRINT_WP(coordenada,2,"0");}
                if (valor == 1){LCD_PRINT_WP(coordenada,2,"1");}
                if (valor == 2){LCD_PRINT_WP(coordenada,2,"2");}
                if (valor == 3){LCD_PRINT_WP(coordenada,2,"3");}
                if (valor == 4){LCD_PRINT_WP(coordenada,2,"4");}
                if (valor == 5){LCD_PRINT_WP(coordenada,2,"5");}
                if (valor == 6){LCD_PRINT_WP(coordenada,2,"6");}
                if (valor == 7){LCD_PRINT_WP(coordenada,2,"7");}
                if (valor == 8){LCD_PRINT_WP(coordenada,2,"8");}
                if (valor == 9){LCD_PRINT_WP(coordenada,2,"9");}   
   
        }}
}
