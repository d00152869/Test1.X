/*
 * File:   controller.c
 * Author: d00152869
 *
 * Created on 07 March 2017, 09:15
 */

#include <xc.h>

#define _XTAL_FREQ 8000000

void delay_ms(unsigned int msec);
void delay_s(unsigned int sec);
void initial(void);

void main(void) {
    float ADCres;
    float Voltage;
    float resistance;
    unsigned int setpoint = 5000;
    signed long error = 0;
    unsigned char error_state = 0;
    unsigned char error_range = 0;
    signed int pwmrate = 0;
    initial();
    //CCPR1L = 20;
    while(1) {
        ADCON0bits.GO_nDONE = 1;
        while(ADCON0bits.GO_nDONE);
        ADCres = ((ADRESH<<8)+ADRESL);
        Voltage = ADCres * 5 / 1024;
        resistance = (Voltage * 10000) / (5 - Voltage);
        error = resistance - setpoint;
        if(error>0) {
            error_state = 1;
        }
        else {
            error_state = 0;
            error = error * -1;
        }
        if(error<100) {
            error_range = 1;
        }
        else if(error<1000) {
            error_range = 5;
        }
        else {
            error_range = 10;
        }
        if(error_state==1) {
            pwmrate = pwmrate + error_range;
            if(pwmrate >100) {
                pwmrate = 100;
            }
        }
        else {
            pwmrate = pwmrate - error_range;
            if(pwmrate < 0) {
                pwmrate = 0;
            }
        }
        PWM3DCH = pwmrate;
        delay_ms(50);
    }
}

void initial(void) {
    TRISC = 0x00;
    OSCCON = 0b01110011;
    TRISCbits.TRISC3 = 1;
    //ANSELbits.AN7 = 1;
    ADCON0 = 0b00011101;
    ADCON1 = 0b10010000;
    ANSELCbits.ANSC3 = 1;    
    T2CONbits.ON = 1;   
    //CCP1CON = 0b00001100;
    RC5PPS = 0b00001110;
    PWM3CON = 0x80;
    PR2 = 99; //99
    PWM3DCH = 20;
    delay_s(1);
    PWM3DCH = 50;
    delay_s(1);
    PWM3DCH = 80;
    delay_s(1);
}

void delay_s(unsigned int sec)
{
    unsigned char j;
    for (j=0;j<sec;j++) {
        unsigned char i;
        for (i=0;i<25;i++) {
            __delay_ms(40);
        }
    }
}

void delay_ms(unsigned int msec) {
    unsigned int i;
    for (i=0;i<msec;i++) {
        __delay_ms(1);
    }
}
