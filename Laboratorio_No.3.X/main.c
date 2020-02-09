/*************************** PALABRA DE CONFIGURACION *************************/
    #pragma config FOSC = INTRC_NOCLKOUT           
    #pragma config WDTE = OFF       
    #pragma config PWRTE = OFF      
    #pragma config MCLRE = OFF      
    #pragma config CP = OFF         
    #pragma config CPD = OFF         
    #pragma config BOREN = OFF     
    #pragma config IESO = OFF      
    #pragma config FCMEN = OFF     
    #pragma config LVP = OFF       
    #pragma config BOR4V = BOR40V   
    #pragma config WRT = OFF        
    #include <xc.h>
    #include <stdint.h>
    #include "ADC.h"
    #include "DELAYS.h"
/******************************************************************************/
/************ PROTOCOLO DE FUNCIONES, VARIABLES Y DEM�S DEFINICIONES **********/
void setup (void);
/******************************************************************************/



void main(void) {
    setup();        /************* FUNCI�N DE CONFIGURACI�N INICIAL ***********/
    while(1){       /*************** MAIN GLORIUS SPARTAN PROGRAM *************/
        
    }
    return;   
 /*****************************************************************************/
}

/*************************** RUTINA DE CONFIGURACION  *************************/
void setup (void){
/*****CONFIGURANDO PUERTOS DE ENTRADA Y SALIDA AS� COMO VALORES INICIALES *****/
    TRISA  = 0b00000011;/*Todos los pines del puerto exepto RA0 y RA1 como OUT*/
    ANSEL  = 0b00000011;           /*Utilizar� el canal AN[0,1] del modulo ADC*/ 
    ANSELH = 0b00000000;           /*     Uso nulo del puerto B como ANIN     */
    TRISB  = 0b00000000;           /*    Todo el PORTB declarado como OUTPUT  */
    TRISC  = 0b00000000;           /*    Todo el PORTC declarado como OUTPUT  */
    TRISD  = 0b00000000;           /*    Todo el PORTC declarado como OUTPUT  */
    TRISE  = 0b0000;               /*    Todo el PORTE declarado como OUTPUT  */
    PORTB  = 0b00000000;           /*    Todo el PORTB colocado a 0v          */
    PORTC  = 0b00000000;           /*    Todo el PORTC colocado a 0v          */
    PORTD  = 0b00000000;           /*    Todo el PORTD colocado a 0v          */
    PORTE  = 0b0000;               /*    Todo el PORTE colocado a 0v          */
/******************************************************************************/
/************** CONFIGURACI�N DE TIMER 0 Y DE SUS INTERRUPCIONES **************/
    OPTION_REGbits.T0CS = 0; /* TMR0 Clock Selector-> 0 = FOSC/4, 1 = EXTERNAl*/
    OPTION_REGbits.PSA  = 0; /* Prescaler selector-> 0 = TMR0 Module, 1 = WDT */
    OPTION_REGbits.PS0  = 0; /* PS[2:0] definen el preescalador del TMR0      */
    OPTION_REGbits.PS1  = 1; /* 0      1     0     -> 1:8                     */ 
    OPTION_REGbits.PS2  = 0; /* PS2   PS1   PS0                               */
    INTCONbits.T0IE     = 1; /* TMR0 INTERRUPT ENABLE-> 0 = nope, 1 = yes     */
    INTCONbits.T0IF     = 0; /* TMR0 INTERRUPT FLAG                           */
    TMR0                = 130;/* Valor precargado para obtener 1ms de TMR0    */
/******************************************************************************/
/****************** CONFIGURACI�N DE ADC E INTERRIPCION DE ADC ****************/
    CONFIG_ADC();
}


