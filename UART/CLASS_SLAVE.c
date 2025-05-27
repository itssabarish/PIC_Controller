
// PIC16F877A Configuration Bit Settings

// 'C' source line config statements

// CONFIG
#pragma config FOSC = EXTRC     // Oscillator Selection bits (RC oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#define _XTAL_FREQ 6000000
void initialization();
unsigned char state;

void main(void) 
{
    initialization();
    while(1)
    {  
        if(PIR1 & 0X20)  /* This condition check is whenever the RCIF pin is receieved as 1 then only the condition check is passed 
                            RCIF pin The USART receive buffer is full or empty*/
        {
             state = RCREG;  //received data is to local variable state
            //based on the switch pressed, created the condition and its going to enable the LED
            switch(state)
            {
                case 'A': 
                  PORTD = 0x40;   // RD6 as on and RD2 as off
                  break;
                case 'B': 
                   PORTD = 0x02;   // RD6 as off and RD2 as on
                   break;
                case 'C': 
                   PORTD = 0x00;  // RD6 as off and RD2 as off
                   break;
                case 'D': 
                   PORTD = 0x42;   // RD6 as on and RD2 as on
                   break;
            }
            __delay_ms(1000);
        }
    }
}

void initialization()
{
    TRISD = 0x00;        // setting all pins as output to blink the LED
    PORTD = 0x00;        // initialization of PORTB;
    
    //initializing the UART pins
    TRISC = 0xc0;  // setting the bit of RC7 and RC6 as 1 to act as receiver and transmitter
    TXSTA = 0x20;  // setting the bit of TXEN to transmission to enable and other pin as 0 
    RCSTA = 0x90;  // enabling the serial port tranmission as SPEN and CREN pin as asynchronous mode
    SPBRG = 0x09;  // baud rate generator
    
}