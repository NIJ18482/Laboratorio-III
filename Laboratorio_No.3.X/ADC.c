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

void CONFIG_ADC(void) {
    ADCON1bits.ADFM  = 0;   /*   JUST. A LA IZQ.DEL REGISTRO ADRESH Y ADRESL  */
    ADCON1bits.VCFG1 = 0;   /*  ESTABLECMOS LA REFERENCIA NEGATIVA DEL ADC    */
    ADCON1bits.VCFG0 = 0;   /*  ESTABLECMOS LA REFERENCIA POSITIVA DEL ADC    */
    ADCON0bits.ADCS1 = 0;   /*A/D CONVERSION CLOCK SELECT-> ADCS1   ADCS0     */
    ADCON0bits.ADCS0 = 1;   /* FOSC/8 A 4 MHz -> 20us         1       0       */
    ADCON0bits.CHS3  = 0;   /* BITS SELECTORES DE CANAL DE CONVERSI�N ADC     */
    ADCON0bits.CHS2  = 0;   /*  0     0     0     0     0      0    0     1   */
    ADCON0bits.CHS1  = 0;   /* CHS3  CHS2  CHS1  CHS0  CHS3  CHS2  CHS1  CHS0 */    
    ADCON0bits.CHS0  = 0;   /* CHANNEL 0000           Y CHANNEL 0001          */
    ADCON0bits.ADON  = 1;   /*    ENCENDEMOS EL M�DULO DE CONVERSI�N ADC      */
    return;
}
