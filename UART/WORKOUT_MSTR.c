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
unsigned char rx_state;

void main() 
{
   
    initialization();
    while(1)
    {
        state = PORTB;  //switch state is assigned to local variable state
        
        //based on the switch pressed, created the condition and its going to transmit the data to the receiver
        
        switch(state)
        {
            case 0xE0: 
                TXREG = 'A';
                __delay_ms(1000);
                break;
            case 0xD0: 
                TXREG = 'B';
                __delay_ms(1000);
                break;
            case 0xB0: 
                TXREG = 'C';
                __delay_ms(1000);
                break;
            case 0x70: 
                TXREG = 'D';
                __delay_ms(1000);
                break;
        }
    
        if(PIR1 & 0X20)  /* This condition check is whenever the RCIF pin is receieved as 1 then only the condition check is passed 
                            RCIF pin The USART receive buffer is full or empty*/
        {
            rx_state = RCREG;  //switch state is assigned to local variable state

            //based on the switch pressed, created the condition and its going to turn on the LED at RD6 and RD1

            switch(rx_state)
            {
                case 'a': 
                    PORTD = 0x02;       //0000 0010 RD1 LED alone will blink
                    __delay_ms(1000);
                    break;
                case 'b': 
                    PORTD = 0x40;       //0100 0000 RD6 LED alone will blink
                    __delay_ms(1000);
                    break;
                case 'c': 
                    PORTD = 0x00;      //0000 0000 RD1 and RD6 LED's will turn off
                    __delay_ms(1000);
                    break;
                case 'd': 
                    PORTD = 0x42;     //0000 0000 RD1 and RD6 LED's will blink
                    __delay_ms(1000);
                    break;
            }
        }
    }
}

void initialization()
{
    TRISB = 0xF0;    // setting RB4 to RB7 as input and other pins as output
    PORTB = 0x00;    // initialization of PORTB
    TRISD = 0x00;    // setting all pin as output
    PORTD = 0x00;    // initialization of PORTD
    OPTION_REG = 0x7f;  // activating the internal pull-up registor
    
    // UART initialization
    TRISC = 0xc0;    // setting the bit of RC7 and RC6 as 1 to act as receiver and transmitter
    TXSTA = 0x20;    // setting the bit of TXEN to transmission to enable and other pin as 0 
    RCSTA = 0x90;    // enabling the serial port tranmission as SPEN and CREN pin as asynchronous mode
    SPBRG = 0x09;    // baud rate generator
}