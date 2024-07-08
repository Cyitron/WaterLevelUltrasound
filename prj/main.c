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
#include <pic16f877a.h>
#include <stdio.h>

unsigned int echo_time = 0;
unsigned int start_time = 0;
unsigned int end_time = 0;
unsigned int echo_recebido = 0;

// FUNCAO PARA ENVIAR PULSO DE TRIGGER
void send_trigger_pulse(void) {
    PORTBbits.RB2 = 1; // Envia TRIGGER
    __delay_us(10);    // Espera 10 microssegundos
    PORTBbits.RB2 = 0; // Termina TRIGGER
}


//FUNCAO DE INTERRUPCAO
void __interrupt() isr(void) {
    if(INTCONbits.INTF) { //Verifica se a interrupcao externa foi acionada (RB0)
        if(PORTBbits.RB1 == 1) { // Verifica se o ECHO subiu (esta em high)
            TMR1 = 0; // Reseta o timer1
            T1CONbits.TMR1ON = 1; // Liga o timer1
        }
        
        else { // Verifica se o echo desceu (esta em low)
            T1CONbits.TMR1ON = 0; // Desliga o timer1
            echo_time = (TMR1H << 8) | TMR1L; // Calcula o tempo em ticks
            echo_recebido = 1; // Sinaliza que o pulso foi recebido
        }
        
        INTCONbits.INTF = 0; // Limpa a flag de interrupcao externa
    }
}

//FUNCAO PARA CALCULAR A DISTANCIA COM BASE NO TEMPO DO ECHO
float calcular_distancia(unsigned int echo_time) {
    
    // velocidade do som = 34300 cm/s
    // distancia em cm = (tempo de echo em us) * (velocidade do som em cm/us) /2 
    
    return (float)echo_time * .0343 / 2;
}


 void main(void) {
    
     // Configuracoes iniciais
     
    TRISB = 0b00000010; // configura RB1 como entrada(echo)
                        // e RB2 como saida(TRIGGER)
    PORTB = 0b00000000; // Inicializa o PORTB com todos os pinos em LOW
    
    INTCONbits.INTE = 1; // habilita interrupcao externa (RB0/INT)
    INTCONbits.GIE = 1; // Habilita interrupcoes globais
    
    T1CON = 0b00000001; // Configura o timer1 com prescaler 1:1
    
    while(1){
        send_trigger_pulse(); // envia o pulso de TRIGGER
        
        while(!echo_recebido); // Espera até que o pulso ECHO seja recebido
        
        float distance = calcular_distancia(echo_time); // calcula distancia
        
        echo_recebido = 0;  // resta a flag
        
        __delay_ms(1000); // Espera 1 segundo antes de medir novamente
    }
 }
 
 /*
  RA0,RA3 = CCP1 INPUT
  RA1,RA2 = CCP2 INPUT
  RC1 = CCP1 OUTPUT
  RC2 = CCP2 OUTPUT
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