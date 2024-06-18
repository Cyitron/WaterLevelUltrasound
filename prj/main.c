/*
 * File:   main.c
 * Author: Wodan
 *
 * Created on 18 de Junho de 2024, 15:54
 */
#pragma config FOSC = XT        // Oscillator Selection bits (XT oscillator)
#pragma config WDTE = ON        // Watchdog Timer Enable bit (WDT enabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

#include <xc.h>
#define _XTAL_FREQ 4000000

// NOTE: To use the macros below, YOU must have previously defined _XTAL_FREQ
 //#define __delay_us(x) _delay((unsigned long)((x)*(_XTAL_FREQ/4000000.0)))
 //#define __delay_ms(x) _delay((unsigned long)((x)*(_XTAL_FREQ/4000.0)))
 void main(void) {
    //76543210
    TRISB = 0b00000000;
    PORTB = 0b00000000;
    while(1){
    //PORTBbits.RB0 = 1;
    //__delay_ms(1000);
    //PORTBbits.RB0 = 0;
    //__delay_ms(1000);
     PORTB++;
    __delay_ms(500);
    }
 }