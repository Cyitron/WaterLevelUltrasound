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
#include <pic16f877a.h>
#define _XTAL_FREQ 4000000

float dist_init = 0;

 void main(void) {
    // clear ports
    PORTB = 0b00000000;
    
    // set outputs and inputs
    TRISB = 0b00001001; //1 input 0 output
    
    while(1){
        
        TRISBbits.TRISB2 = 1;  //TRIG1
        TRISBbits.TRISB5 = 1;//TRIG2
        
        __delay_us(10);
        TRISBbits.TRISB1 = 1; //ECHO1
        TRISBbits.TRISB2 = 0;  //TRIG1
        TRISBbits.TRISB4 = 1; //ECHO2
        TRISBbits.TRISB5 = 0;//TRIG2
    }
 }
 
 /*
  RB1 = ECHO1
  RB2 = TRIG1
  RB4 = ECHO2
  RB5 = TRIG2
  */
 
//------------------------------
/* Código feito no ARDUINO (validado)
#define trigPin 10
#define echoPin 13

void setup() {
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  float duration, distance;
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
 
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) * 0.0344;
  
  if (distance >= 400 || distance <= 2){
    Serial.print("Distance = ");
    Serial.println("Out of range");
  }
  else {
    Serial.print("Distance = ");
    Serial.print(distance);
    Serial.println(" cm");
    delay(500);
  }
  delay(500);
}
 */
 
 //#define __delay_us(x) _delay((unsigned long)((x)*(_XTAL_FREQ/4000000.0)))
 //#define __delay_ms(x) _delay((unsigned long)((x)*(_XTAL_FREQ/4000.0)))