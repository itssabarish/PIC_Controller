
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
#define size 12

void START_CONFIGURATION();
void LCD_COMMAND_TO_THE_CONTROLLER(unsigned char);
void LCD_DATA_TO_THE_CONTROLLER(unsigned char);

unsigned char i;

unsigned char sabari[size] = {"HELLO WORLD!"};

void main(void) {
    
    START_CONFIGURATION();
    
    LCD_COMMAND_TO_THE_CONTROLLER(0x80); // Data to be displayed from very start of the display
    
    for (i = 0; i < size; i++ )
    {
         LCD_DATA_TO_THE_CONTROLLER(sabari[i]); // Data is displayed in LCD from here 
    }
    while(1); //Loop runs forever
    
}

void START_CONFIGURATION()
{
    TRISC = 0X00; // configuring the pin as both input and output 
    TRISD = 0X00; // configuring the pin as both input and output 
    
    LCD_COMMAND_TO_THE_CONTROLLER(0x30); // 0011 0000 setting as initialization
    __delay_ms(100);
    LCD_COMMAND_TO_THE_CONTROLLER(0x30); // 0011 0000 setting as initialization
    __delay_ms(100);
    LCD_COMMAND_TO_THE_CONTROLLER(0x30); // 0011 0000 setting as initialization
    __delay_ms(100);
    LCD_COMMAND_TO_THE_CONTROLLER(0x38); // 0011 1000 setting initialization of N and F
    __delay_ms(100);
    LCD_COMMAND_TO_THE_CONTROLLER(0x06); // 0011 0110 setting the initialization of cursor left to right move
    __delay_ms(100);
    LCD_COMMAND_TO_THE_CONTROLLER(0x0C); // 0000 1100 setting display as on and cursor as off
    __delay_ms(100);
    LCD_COMMAND_TO_THE_CONTROLLER(0x01); // 0000 0001 setting display to clear
    __delay_ms(100);
}

void LCD_COMMAND_TO_THE_CONTROLLER(unsigned char i)
{
    RC3 = 0;  //RS = 0 (command)
    PORTD = i;
    RC0 = 1;  // pulse is setting as high
    __delay_ms(100);
    RC0 = 0; // pulse is setting as low
    
}

void LCD_DATA_TO_THE_CONTROLLER(unsigned char i)
{
    RC3 = 1;  //RS = 1 (data)
    PORTD = i;
    RC0 = 1;  // pulse is setting as high
    __delay_ms(100);
    RC0 = 0; // pulse is setting as low
    
}