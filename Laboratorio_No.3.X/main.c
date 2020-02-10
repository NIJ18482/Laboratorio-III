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
/************ PROTOCOLO DE FUNCIONES, VARIABLES Y DEMÁS DEFINICIONES **********/
void setup (void);
uint8_t cambiante = 0;      /*     VAR DE CONTROL DE CAMBIO DE CANAL ADC      */
uint8_t eADC      = 0;      /* VAR DE CONTROL DENTRO DEL LOOP PRINCIPAL       */
uint8_t ADCAN0    = 0;      /* VAR PARA OBTENER EL VALOR DEL 1ER POTENCIÓMETRO*/
uint8_t ADCAN1    = 0;      /* VAR PARA OBTENER EL VALOR DEL 2O POTENCIÓMETRO */
/******************************************************************************/

/************************* RUTINA DE INTERRUPCIÓN *****************************/
void __interrupt() isr(void){
    if (INTCONbits.T0IF == 1){ /*SI EL TMR0 HA SUFRIDO DESBORDE, T - T0 = 1mS */
        if (cambiante == 0){ADCON0bits.CHS0 = 1;} /*ESTE ARREGLO DE IFS, DEJA */
        if (cambiante == 1){ADCON0bits.CHS0 = 0;} /*CAMBIAR DE CANAL CADA 1ms */
        cambiante++;                              /*LA VAR CONTROL QUE CAMBIA */
        if (cambiante > 1){cambiante = 0;}
        if (ADCON0bits.GO_DONE == 0){eADC = 1;}
        INTCONbits.T0IF = 0;
        TMR0 = 130;
        eADC = 1;
    }}
/****************************************** ************************************/
void main(void) {
    setup();        /************* FUNCIÓN DE CONFIGURACIÓN INICIAL ***********/
    while(1){       /*************** MAIN GLORIUS SPARTAN PROGRAM *************/
        if (eADC == 1){
            eADC = 0;
            if (cambiante == 0){ADCAN0 = ADRESH; PORTB = ADCAN0;}
            if (cambiante == 1){ADCAN1 = ADRESH; PORTC = ADCAN1;}
            ADCON0bits.GO_DONE = 1;}
    
    }
    
    return;   
 /*****************************************************************************/
}

/*************************** RUTINA DE CONFIGURACION  *************************/
void setup (void){
/*****CONFIGURANDO PUERTOS DE ENTRADA Y SALIDA ASÍ COMO VALORES INICIALES *****/
    TRISA  = 0b00000011;/*Todos los pines del puerto exepto RA0 y RA1 como OUT*/
    ANSEL  = 0b00000011;           /*Utilizaré el canal AN[0,1] del modulo ADC*/ 
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
/************** CONFIGURACIÓN DE TIMER 0 Y DE SUS INTERRUPCIONES **************/
    OPTION_REGbits.T0CS = 0; /* TMR0 Clock Selector-> 0 = FOSC/4, 1 = EXTERNAl*/
    OPTION_REGbits.PSA  = 0; /* Prescaler selector-> 0 = TMR0 Module, 1 = WDT */
    OPTION_REGbits.PS0  = 0; /* PS[2:0] definen el preescalador del TMR0      */
    OPTION_REGbits.PS1  = 1; /* 0      1     0     -> 1:8                     */ 
    OPTION_REGbits.PS2  = 0; /* PS2   PS1   PS0                               */
    INTCONbits.T0IE     = 1; /* TMR0 INTERRUPT ENABLE-> 0 = nope, 1 = yes     */
    INTCONbits.T0IF     = 0; /* TMR0 INTERRUPT FLAG                           */
    TMR0                = 130;/* Valor precargado para obtener 1ms de TMR0    */
/******************************************************************************/
/****************** CONFIGURACIÓN DE ADC E INTERRIPCION DE ADC ****************/
    CONFIG_ADC();
}



