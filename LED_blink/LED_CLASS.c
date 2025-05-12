
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

void main(void) {
    
    TRISD =     0X7D;   // 0111 1101 as RC7 and RC1 pin as output
    
    while(1)
    {
        PORTD = 0X02;  // 0000 0010 RC1 is high 
        __delay_ms(3000);
        PORTD = 0X80;  // 1000 0000 RC8 is high
        __delay_ms(3000);
        PORTD = 0X82; // 1000 00010 RC7 and RC1 is high
        __delay_ms(3000);
        PORTD = 0X00; // 0000 0000 RC7 and RC1 is low
        __delay_ms(3000);
        
    }
}
