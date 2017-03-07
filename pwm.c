/*
 * File:   temlate.c
 * Author: d00152869
 *
 * Created on 14 February 2017, 09:36
 */

#include <xc.h>

#define _XTAL_FREQ 8000000

void delay_ms(unsigned int msec);
void delay_s(unsigned int sec);
void initial(void);

void main(void) {
    initial();
    //CCPR1L = 20;
    while(1) {
        PWM3DCH = 20;
        delay_s(1);
        PWM3DCH = 50;
        delay_s(1);
        PWM3DCH = 80;
        delay_s(1);
    }
}

void initial(void) {
    TRISC = 0x00;
    OSCCON = 0b01110011;    
    T2CONbits.ON = 1;   
    //CCP1CON = 0b00001100;
    RC5PPS = 0b00001110;
    PWM3CON = 0x80;
     
    PR2 = 99; //99
    
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
