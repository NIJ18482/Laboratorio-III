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
    #pragma config  LVP = OFF       
    #pragma config BOR4V = BOR40V   
    #pragma config WRT = OFF        
    #include <xc.h>
    #include <stdint.h>        /* INCLUSIÓN DE LIBRERÍA DE ANCHO VARS ESTANDAR*/
    #include "ADC.h"           /* INCLUSIÓN DE MI LIBRERÍA DEL MANEJOD DE ADC */
    #include "DELAYS.h"        /*  INCLUSIÓN DE MI LIBRERÍA DE DELAYS PATITO  */
    #include "LCD.h"           /* INCLUSIÓN DE MI LIBRERÍA DEL F*UCKING LCD   */
/******************************************************************************/
/************ PROTOCOLO DE FUNCIONES, VARIABLES Y DEMÁS DEFINICIONES **********/
void setup (void);
uint8_t cambiante = 0;      /*     VAR DE CONTROL DE CAMBIO DE CANAL ADC      */
uint8_t eADC      = 0;      /* VAR DE CONTROL DENTRO DEL LOOP PRINCIPAL       */
uint8_t ADCAN0    = 0;      /* VAR PARA OBTENER EL VALOR DEL 1ER POTENCIÓMETRO*/
uint8_t ADCAN1    = 0;      /* VAR PARA OBTENER EL VALOR DEL 2O POTENCIÓMETRO */
uint8_t sensor    = 0;
uint8_t sen       = 0;
/******************************************************************************/

/************************* RUTINA DE INTERRUPCIÓN *****************************/
void __interrupt() isr(void){
    if (INTCONbits.T0IF == 1){ /*SI EL TMR0 HA SUFRIDO DESBORDE, T - T0 = 1mS */
        if (cambiante == 0){ADCON0bits.CHS0 = 1;} /*ESTE ARREGLO DE IFS, DEJA */
        if (cambiante == 1){ADCON0bits.CHS0 = 0;} /*CAMBIAR DE CANAL CADA 1ms */
        cambiante++;                              /*LA VAR CONTROL QUE CAMBIA */
        sensor++;
        if (cambiante > 1){cambiante = 0;}
        if (ADCON0bits.GO_DONE == 0){eADC = 1;}
        INTCONbits.T0IF = 0;
        TMR0 = 130;
        eADC = 1;
    }}
/******************************************************************************/
void main(void) {
    setup();        /************* FUNCIÓN DE CONFIGURACIÓN INICIAL ***********/
    INIT_LCD();
    LCD_CLEAR();
    LCD_RH();
    LCD_PRINT_WP(0,1,"LABORATORIO No.3");
    delay_ms(150);
    LCD_PRINT_WP(0,2,"Luis N. 18482UVG");
    delay_ms(150);
    LCD_CLEAR();
    LCD_RH();
    LCD_PRINT_WP(0,1,"MANEJO PANEL LCD");
    delay_ms(150);
    LCD_PRINT_WP(0,2,"-MPLABX-XC8-PIC-");
    delay_ms(150);
    LCD_CLEAR();
    LCD_RH();
    LCD_PRINT_WP(0,1,"|SEN.2|SEN.1| CT");
    LCD_PRINT_WP(0,2,"|0.00V|0.00V|000");
    CONFIG_ADC();
    while(1){       /*************** MAIN GLORIUS SPARTAN PROGRAM *************/
        
        if (eADC == 1){
            eADC = 0;
            if (cambiante == 0){ADCAN0 = ADRESH;}
            if (cambiante == 1){ADCAN1 = ADRESH;}
            ADCON0bits.GO_DONE = 1;}     
        if (sensor == 20){
            if (sen == 0){VAL(ADCAN0,0);}
            if (sen == 1){VAL(ADCAN1,1);}
            sen++;
            if (sen > 1){sen = 0;}
            sensor = 0;}
    }return;}
/*****************************************************************************/

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
    INTCONbits.GIE      = 1; /* INTERRUPCIONES GLOBALES ACTIVADAS             */
    TMR0                = 130;/* Valor precargado para obtener 1ms de TMR0    */
/******************************************************************************/
/****************** CONFIGURACIÓN DE ADC E INTERRIPCION DE ADC ****************/
}



