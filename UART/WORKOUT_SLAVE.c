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
unsigned char rx[15] = {"RX data: "};
unsigned char tx[15] = {"TX data: "};
void LCD_COMMAND_TO_THE_CONTROLLER(unsigned char);
void LCD_DATA_TO_THE_CONTROLLER(unsigned char);
void LCD_OUTPUT(unsigned int i);


void main() 
{
    initialization();
    while(1)
    {  
        if(PIR1 & 0X20)  /* This condition check is whenever the RCIF pin is receieved as 1 then only the condition check is passed 
                            RCIF pin The USART receive buffer is full or empty*/
        {
             state = RCREG;  //received data is to local variable state
            
             //here the below code will send the array of rx[] and tx[] data to the LCD 
             
             LCD_COMMAND_TO_THE_CONTROLLER(0X80);
            for (int x=0;x<8;x++)
            {
                LCD_DATA_TO_THE_CONTROLLER(rx[x]);
            }
            LCD_COMMAND_TO_THE_CONTROLLER(0X88);
            LCD_DATA_TO_THE_CONTROLLER(state);
            LCD_COMMAND_TO_THE_CONTROLLER(0Xc0);
            for (int x=0;x<8;x++)
            {
                LCD_DATA_TO_THE_CONTROLLER(tx[x]);
            }
 
            //based on the switch pressed, created the condition and its going send the data to the LCD
            switch(state)
            {
                case 'A': 
                TXREG = 'a';
                LCD_COMMAND_TO_THE_CONTROLLER(0Xc8);
                LCD_DATA_TO_THE_CONTROLLER(TXREG);
                break;
                case 'B': 
                TXREG = 'b';
                LCD_COMMAND_TO_THE_CONTROLLER(0Xc8);
                LCD_DATA_TO_THE_CONTROLLER(TXREG);
                break;
                case 'C': 
                TXREG = 'c';
                LCD_COMMAND_TO_THE_CONTROLLER(0Xc8);
                LCD_DATA_TO_THE_CONTROLLER(TXREG);
                break;
                case 'D': 
                TXREG = 'd'; 
                LCD_COMMAND_TO_THE_CONTROLLER(0Xc8);
                LCD_DATA_TO_THE_CONTROLLER(TXREG);
                break;
            }
            __delay_ms(1000);
        }
    }
}

void initialization()
{
    TRISB = 0x00;     // setting all pin as output
    PORTB = 0x00;     // initialization of PORTB
    TRISD = 0x00;     // setting all pin as output
    PORTD = 0x00;     // initialization of PORTD
    OPTION_REG = 0x7f;  // activating the internal pull-up registor
    
    // UART initialization
    
    TRISC = 0xc0;    // setting the bit of RC7 and RC6 as 1 to act as receiver and transmitter
    TXSTA = 0x20;    // setting the bit of TXEN to transmission to enable and other pin as 0 
    RCSTA = 0x90;    // enabling the serial port tranmission as SPEN and CREN pin as asynchronous mode
    SPBRG = 0x09;    // baud rate generator
    
    
    //LCD configuration
    LCD_COMMAND_TO_THE_CONTROLLER(0X30); // 0011 0000 setting as initialization
     __delay_ms(100);
     LCD_COMMAND_TO_THE_CONTROLLER(0X30); // 0011 0000 setting as initialization
     __delay_ms(100);
     LCD_COMMAND_TO_THE_CONTROLLER(0X38); // 0011 1000 setting initialization of N and F
     __delay_ms(100);
     LCD_COMMAND_TO_THE_CONTROLLER(0X06); // 0000 0110 setting the initialization of cursor left to right move
     __delay_ms(100);
     LCD_COMMAND_TO_THE_CONTROLLER(0X0C); // 0000 1100 setting display as on and cursor as off
     __delay_ms(100);
     LCD_COMMAND_TO_THE_CONTROLLER(0X01); // 0000 0001 setting display to clear
     __delay_ms(100);
    
}

void LCD_COMMAND_TO_THE_CONTROLLER(unsigned char i)
{
    PORTB &= ~(0x08); // RS = 0
    PORTD = i;
    PORTB |= 0x01;    // EN = 1
    __delay_ms(1);
    PORTB &= ~(0x01); // EN = 0
    __delay_ms(100);
}

void LCD_DATA_TO_THE_CONTROLLER(unsigned char i) 
{
    PORTB |= 0x08;    // RS = 1
    PORTD = i;
    PORTB |= 0x01;    // EN = 1
    __delay_ms(1);
    PORTB &= ~(0x01); // EN = 0
    __delay_ms(100);
}