
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


#include <xc.h>
#define _XTAL_FREQ 6000000

void main(void) 
{
    unsigned char number; 
    
    TRISB =  0XF0;    // 1111 0000 as RC4 and RC7 pin as input and RB0 to RB3 output  
    TRISC =  0X00;   // 0000 0000 RC1 and RC6 pin as output
    
    PORTB = 0X00;   // 0000 0000 (RB4 to RB7 input + connected with pull up)
    PORTC = 0X00;  //  0000 0000 initially value need to set a value
    
    while(1)
    {
        number = PORTB;
        switch(number)
        {
            case 0xE0: PORTC = 0X02; // 0000 0010
            break;
            case 0xD0: PORTC = 0X42; // 0100 0010
            break;
            case 0xB0: PORTC = 0X40; // 0100 0000
            break;
            case 0x70: PORTC = 0X00; // 0000 0000
            break;
            case 0xF0: PORTC = 0X00; // 0000 0000
            break;
        }
    }
}