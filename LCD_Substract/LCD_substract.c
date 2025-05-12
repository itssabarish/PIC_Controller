
// PIC16F877A Configuration Bit Settings

// 'C' source line config statements

// CONFIG
#pragma config FOSC = EXTRC     // Oscillator Selection bits (RC oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = ON       // Power-up Timer Enable bit (PWRT enabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF         // Flash Program Memory Code Protection bit (Code protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.


#include <xc.h>
#define _XTAL_FREQ 6000000

void START_CONFIGURATION();
void LCD_COMMAND_TO_THE_CONTROLLER(unsigned char);
void LCD_DATA_TO_THE_CONTROLLER(unsigned char);
void LCD_OUTPUT(unsigned int);
unsigned int num1, num2, m;
unsigned char j,k[5],equal, plus, sub;
unsigned int sum;

void main(void)
{
    START_CONFIGURATION(); // configuring the MC and LCD 
    num1 = 189;
    num2 = 435;
    equal = '=';
    plus = '+';
    sub = '-';
    LCD_COMMAND_TO_THE_CONTROLLER(0X80); //LCD start position 
    LCD_OUTPUT(num1); // num1 print at position from 0x80 to 0x82
    LCD_DATA_TO_THE_CONTROLLER(sub); // character '+' prints at position at 0x83
    LCD_OUTPUT(num2); // num2 print at position from 0x84 to 0x86
    LCD_DATA_TO_THE_CONTROLLER(equal); // character '=' prints at position at 0x87
    if (num1 > num2)   // condition to check if num1 is greater than num2 so it can add the two numbers
    {
        LCD_DATA_TO_THE_CONTROLLER(plus); // character '+' prints at position at 0x88
        sum = num1 - num2;
        LCD_OUTPUT(sum); // sum prints at position at 0x89
    }
    else              // condition to check if num1 is less than num2 so it can subtract the two numbers
    {
            LCD_DATA_TO_THE_CONTROLLER(sub); // character '-' prints at position at 0x88
            sum = num2 - num1;
            LCD_OUTPUT(sum); // sum prints at position at 0x89
    }
    while(1);
}

 void START_CONFIGURATION()
 {
     TRISC = 0X00; // configuring the pin as both input and output 
     TRISD = 0X00; // configuring the pin as both input and output 
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
     PORTC&=~(0x08); //RS = 1 at RC3
     PORTD = i;        // data
     PORTC|=0X01;   // EN = 1 at RC0
     PORTC&=~(0x01);   // EN = 0 at RC0
     __delay_ms(100);
 }
 
  void LCD_DATA_TO_THE_CONTROLLER(unsigned char i)
 {
     PORTC|=(0x08); //RS = 0 at RC3
     PORTD=i;        // data
     PORTC|=0X01;   // EN = 1 at RC0
     PORTC&=~(0x01);   // EN = 0 at RC0
     __delay_ms(100);
 }
  
  void LCD_OUTPUT(unsigned int i)  //function to segregate the integer to single character into array  
  {
      unsigned char s, j = 1;
      unsigned char n;
      m = i;
      while (m != 0)
      {
          s = m -((m/10)*10);
          k[j] = s;
          j++;
          m = m/10;
      }
       k[j] = '\0'; // assign null
       j = j-1;
      while(j != 0)
      {
          n = 0x30 + k[j]; //ASCII convert // 0x30 => 48 
          LCD_DATA_TO_THE_CONTROLLER(n);
          j--;
      }
  }