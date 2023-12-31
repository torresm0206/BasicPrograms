/*
 * File:   main.c
 * Author: José Manuel Torres Rivera
 *This program uses the Timer0 to generate a 10ms Delay function
 * Created on 22 de diciembre de 2023, 02:47 AM
 */
#include <xc.h>

#pragma config FOSC = HS  // Oscilador de alta velocidad externo
#pragma config WDT = OFF  // Desactiva el watchdog timer
#pragma config PWRT = ON  // Activa el Power-up Timer   -> Permite que la frecuencia del oscilador y el voltaje alcancen sus valores adecuados antes de ejecutar el programa (65ms es el valor nominal para el 18f4550)
#pragma config BOR = ON // Activa el Brown-out Reset (si VDD cae entonces el micro se reinicia para evitar malos funcionamientos)
#pragma config PBADEN = OFF // Desactiva el conversor A/D en los pines PORTB
#pragma config MCLRE = OFF // Para desactivar el mclr y usar el RE3 como I/O (si se activa, colocar un resistencia de pull-up para evitar reinicios no deseados)

#define _XTAL_FREQ 20000000
#define LED1 LATDbits.LATD7

void pinConfig()
{
    TRISDbits.TRISD7 = 0;
    PORTD = 0x00;
}

void timer0Config()
{
    T0CONbits.T08BIT = 0;  //Timer0 a 16 bits
    T0CONbits.T0CS = 0; //se configura como temporizador
    //T0CONbits.PSA = 0; //se habilita el preescaler
    //T0CONbits.T0PS = 0x7; //preescaler de 256
    TMR0H = 0x3C;  // These values to generate 10ms
    TMR0L = 0xC4;  
}

void miDelay()
{
    T0CONbits.TMR0ON = 1;
    while(!INTCONbits.TMR0IF);
    INTCONbits.TMR0IF = 0;
    T0CONbits.TMR0ON = 0;
    TMR0H = 0x3C;
    TMR0L = 0xC4;
}

void main(void) {
    pinConfig();
    timer0Config();
    
    LED1 = 0;
    while(1)
    {
        miDelay();
        LED1 = 1;
        miDelay();
        LED1 = 0;
    }
    return;
}
