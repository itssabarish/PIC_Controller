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


void adc_lcd_init();
void adc_read();
void output_channel_1(unsigned int);
void output_channel_4(unsigned int);
void LCD_COMMAND_TO_THE_CONTROLLER(unsigned char);
void LCD_DATA_TO_THE_CONTROLLER(unsigned char);

unsigned char channel_1[] = {"CH1:"};
unsigned char channel_4[] = {"CH4:"};
unsigned int calibration_data,adc_volt;
unsigned char adc_high, adc_low;

void main(void)
{
    adc_lcd_init();
    while(1)
    {
        ADCON0 = 0X89;  //channel_1 AN1
        __delay_ms(10);
        ADCON0 |= 0x04;
        while(ADCON0 & 0x04);
        adc_high = ADRESH;
        adc_low = ADRESL;
        adc_volt = (adc_high << 8) + adc_low;
        output_channel_1(adc_volt);
        
        
       //__delay_ms(10);
        ADCON0 = 0xA1;  //channel_4 AN4
        __delay_ms(10);
        ADCON0 |= 0x04;
        while(ADCON0 & 0x04);
        adc_high = ADRESH;
        adc_low = ADRESL;
        adc_volt = (adc_high << 8) + adc_low;
        calibration_data = ((adc_volt * 135) / 1023);
        output_channel_4(calibration_data);
    }
}


void adc_lcd_init()
{
    
    // All pins are output 
    //TRISA = 0XFF;
    TRISC = 0x00;
    TRISD = 0x00;
    PORTD = 0X00;
    PORTC = 0X00;
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
     
     /*ADC initaliazation*/
     
     ADCON1 = 0X8E;
     ADCON0 = 0X89;  //channel_1 AN1
     __delay_ms(10);
      
}

void output_channel_1(unsigned int i)
{
   int j = 1, s;
   int x = 0;
   unsigned int m;
   unsigned char k[5];
   m = i;
   if (m ==0)
   {
       k[j++] = 0;
   }
   else
   {
   while(m != 0)
   {
       s = (m -((m/10)*10));
       k[j] = s;
       j++;
       m = m/10;
   } 
   }
   k[j] = '\0';
   j--;
   LCD_COMMAND_TO_THE_CONTROLLER(0X80);
   for (x=0;x<4;x++)
   {
       LCD_DATA_TO_THE_CONTROLLER(channel_1[x]);
       
    }
   if(k[4] > 0)
   {
       LCD_COMMAND_TO_THE_CONTROLLER(0x84);
       LCD_DATA_TO_THE_CONTROLLER(0x30 + k[4]);
       LCD_COMMAND_TO_THE_CONTROLLER(0x85);
       LCD_DATA_TO_THE_CONTROLLER(0x30 + k[3]);
       LCD_COMMAND_TO_THE_CONTROLLER(0x86);
       LCD_DATA_TO_THE_CONTROLLER(0x30 + k[2]);
       LCD_COMMAND_TO_THE_CONTROLLER(0x87);
       LCD_DATA_TO_THE_CONTROLLER(0x30 + k[1]);
   }
   else if (k[3] > 0)
   {
       LCD_COMMAND_TO_THE_CONTROLLER(0x84);
       LCD_DATA_TO_THE_CONTROLLER(0x20);
       LCD_COMMAND_TO_THE_CONTROLLER(0x85);
       LCD_DATA_TO_THE_CONTROLLER(0x30 + k[3]);
       LCD_COMMAND_TO_THE_CONTROLLER(0x86);
       LCD_DATA_TO_THE_CONTROLLER(0x30 + k[2]);
       LCD_COMMAND_TO_THE_CONTROLLER(0x87);
       LCD_DATA_TO_THE_CONTROLLER(0x30 + k[1]);
   }
   else if (k[2] > 0)
   {
       LCD_COMMAND_TO_THE_CONTROLLER(0x84);
       LCD_DATA_TO_THE_CONTROLLER(0x20);
       LCD_COMMAND_TO_THE_CONTROLLER(0x85);
       LCD_DATA_TO_THE_CONTROLLER(0x20);
       LCD_COMMAND_TO_THE_CONTROLLER(0x86);
       LCD_DATA_TO_THE_CONTROLLER(0x30 + k[2]);
       LCD_COMMAND_TO_THE_CONTROLLER(0x87);
       LCD_DATA_TO_THE_CONTROLLER(0x30 + k[1]);
   }
   else
   {
       LCD_COMMAND_TO_THE_CONTROLLER(0x84);
       LCD_DATA_TO_THE_CONTROLLER(0x20);
       LCD_COMMAND_TO_THE_CONTROLLER(0x85);
       LCD_DATA_TO_THE_CONTROLLER(0x20);
       LCD_COMMAND_TO_THE_CONTROLLER(0x86);
       LCD_DATA_TO_THE_CONTROLLER(0x20);
       LCD_COMMAND_TO_THE_CONTROLLER(0x87);
       LCD_DATA_TO_THE_CONTROLLER(0x30 + k[1]);
   }
   LCD_COMMAND_TO_THE_CONTROLLER(0x88);
   LCD_DATA_TO_THE_CONTROLLER(0x76);
       
}

void output_channel_4(unsigned int i)
{
   int j = 1, s;
   int x = 0;
   unsigned int m;
   unsigned char k[5];
   m = i;
   /*if (m ==0)
   {
       k[j++] = 0;
   }*/
   //else
   //{
       while(m != 0)
      {
          s = (m -((m/10)*10));
          k[j] = s;
          j++;
          m = m/10;
       } 
   //}
   k[j] = '\0';
   j--;
   LCD_COMMAND_TO_THE_CONTROLLER(0XC0);
   for (x=0;x<4;x++)
   {
       LCD_DATA_TO_THE_CONTROLLER(channel_4[x]);
       
   }
   if(k[3] > 0)
   {
       LCD_COMMAND_TO_THE_CONTROLLER(0xC4);
       LCD_DATA_TO_THE_CONTROLLER(0x30 + k[3]);
       LCD_COMMAND_TO_THE_CONTROLLER(0xC5);
       LCD_DATA_TO_THE_CONTROLLER(0x30 + k[2]);
       LCD_COMMAND_TO_THE_CONTROLLER(0xC6);
       LCD_DATA_TO_THE_CONTROLLER(0x30 + k[1]);
   }
   else if (k[2] > 0)
   {
       LCD_COMMAND_TO_THE_CONTROLLER(0xC4);
       LCD_DATA_TO_THE_CONTROLLER(0x20);
       LCD_COMMAND_TO_THE_CONTROLLER(0xC5);
       LCD_DATA_TO_THE_CONTROLLER(0x30 + k[2]);
       LCD_COMMAND_TO_THE_CONTROLLER(0xC6);
       LCD_DATA_TO_THE_CONTROLLER(0x30 + k[1]);
   }
   else
   {
       LCD_COMMAND_TO_THE_CONTROLLER(0xC4);
       LCD_DATA_TO_THE_CONTROLLER(0x20);
       LCD_COMMAND_TO_THE_CONTROLLER(0xC5);
       LCD_DATA_TO_THE_CONTROLLER(0x20);
       LCD_COMMAND_TO_THE_CONTROLLER(0xC6);
       LCD_DATA_TO_THE_CONTROLLER(0x30 + k[1]);
   }
   LCD_COMMAND_TO_THE_CONTROLLER(0xC7);
   LCD_DATA_TO_THE_CONTROLLER(0x76);
}


void LCD_COMMAND_TO_THE_CONTROLLER(unsigned char i)
{
    PORTC &= ~(0x08); // RS = 0
    PORTD = i;
    PORTC |= 0x01;    // EN = 1
    __delay_ms(1);
    PORTC &= ~(0x01); // EN = 0
    __delay_ms(100);
}

void LCD_DATA_TO_THE_CONTROLLER(unsigned char i) 
{
    PORTC |= 0x08;    // RS = 1
    PORTD = i;
    PORTC |= 0x01;    // EN = 1
    __delay_ms(1);
    PORTC &= ~(0x01); // EN = 0
    __delay_ms(100);
}

