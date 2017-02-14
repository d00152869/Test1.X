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
    while(1) {
        unsigned char duty[3] = {30, 60, 90};
        for (i=0; i<3 ; i++)
        {
            PWM1DCL = 0;
            PWM1DCH = duty[i];
            delay_s(5);
        }
    }
}

void initial(void) {
    TRISC = 0x00;
    OSCCON = 0b01110011;
    T2CON = 0x80;
    PWM1CON = 0x80;
    PR2 = 0x63; //99
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
