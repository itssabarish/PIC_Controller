
// PIC16F877A Configuration Bit Settings

// 'C' source line config statements

// CONFIG
#pragma config FOSC = EXTRC     // Oscillator Selection bits (RC oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = ON       // Brown-out Reset Enable bit (BOR enabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#define _XTAL_FREQ 6000000

unsigned char pwm10_high, pwm10_low;
unsigned char pwm50_high, pwm50_low;
unsigned char pwm80_high, pwm80_low;

void pwm_init();
void pwm_dutycycle_dimming();

void main(void)
{
    pwm_init();
    while(1)
    {
        pwm_dutycycle_dimming();
    }
}
void pwm_init()
{
    TRISC = 0xFB; //1111 1011 set pin configuration 
    CCP1CON = 0X0C;
    PR2 = 0X5D; //period
    T2CON = 0X06;
    pwm10_high = 0x09;
    pwm10_low = 0x02;
    pwm50_high = 0x2F;
    pwm50_low = 0x00;
    pwm80_high = 0x4B;
    pwm80_low = 0x01;
}

void pwm_dutycycle_dimming()
{
    CCPR1L = pwm10_high; //10% high 8 bits
    CCP1CON = ((CCP1CON & 0XCF) | (pwm10_low << 4)); // 10% low 2 bits sends to duty cycle
    __delay_ms(3000);
     CCPR1L = pwm50_high; //50% high 8 bits
     CCP1CON = ((CCP1CON & 0XCF) | (pwm50_low << 4)); // 100% low 2 bits sends to duty cycle
    __delay_ms(3000);
     CCPR1L = pwm80_high; //80% high 8 bits
     CCP1CON = ((CCP1CON & 0XCF) | (pwm80_low << 4)); // 10% low 2 bits sends to duty cycle
    __delay_ms(3000);
    
}