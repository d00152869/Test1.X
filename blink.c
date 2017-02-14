/*
 * File:   blink.c
 * Author: d00152869
 *
 * Created on 31 January 2017, 11:47
 */


#include <xc.h>

#define _XTAL_FREQ 8000000

void delay_1s(void);
void initial(void);

void main(void) {
    float ADCres;
    float Voltage;
    float resistance;
    initial();
    while(1) {
        PORTCbits.RC0 = !PORTCbits.RC0;
        ADCON0bits.GO_nDONE = 1;
        while(ADCON0bits.GO_nDONE);
        ADCres = ((ADRESH<<8)+ADRESL);
        Voltage = ADCres * 5 / 1024;
        resistance = (Voltage * 10000) / (5 - Voltage);
        delay_1s();
        NOP();
    }
}

void initial(void) {
    
    TRISC = 0x00; //RC3 = Input
    TRISCbits.TRISC3 = 1;
    //ANSELbits.AN7 = 1;
    ADCON0 = 0b00011101;
    ADCON1 = 0b10010000;
    ANSELCbits.ANSC3 = 1;
    OSCCON = 0b01110011;
    PORTCbits.RC0 = 1;
    delay_1s();
    PORTCbits.RC0 = 0;
    delay_1s();
}

void delay_1s(void)
{
    unsigned char i;
    for (i=0;i<25;i++) {
        __delay_ms(40);
    }
}
