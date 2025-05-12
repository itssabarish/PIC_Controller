// PIC16F877A Configuration Bit Settings

// CONFIG
#pragma config FOSC = EXTRC     // Oscillator Selection bits (RC oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage Programming (disabled)
#pragma config CPD = OFF        // Data EEPROM Code Protection bit
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits
#pragma config CP = OFF         // Flash Program Memory Code Protection bit

#include <xc.h>
#define _XTAL_FREQ 6000000

void START_CONFIGURATION();
void LCD_COMMAND_TO_THE_CONTROLLER(unsigned char);
void LCD_DATA_TO_THE_CONTROLLER(unsigned char);
void LCD_OUTPUT(float);
void keyscane();

unsigned char array[15] = {"BATTERY=  . "};
unsigned char lb[20] = {"VOLTAGE LOW   "};
unsigned char nb[20] = {"VOLTAGE NORMAL"};
unsigned char hb[20] = {"VOLTAGE HIGH  "};

unsigned int i, d1, d2, d3;
float j = 155.0;
unsigned char x, value;

void main(void) {
    START_CONFIGURATION();
    while (1) {
        keyscane();
    }
}

void START_CONFIGURATION() {
    TRISC = 0x00;
    TRISD = 0x00;
    TRISB = 0xF0;  // RB4?RB7 as input
    PORTB = 0x00;
    OPTION_REG &= 0x7F;

    LCD_COMMAND_TO_THE_CONTROLLER(0x30);
    __delay_ms(100);
    LCD_COMMAND_TO_THE_CONTROLLER(0x30);
    __delay_ms(100);
    LCD_COMMAND_TO_THE_CONTROLLER(0x38);
    __delay_ms(100);
    LCD_COMMAND_TO_THE_CONTROLLER(0x06);
    __delay_ms(100);
    LCD_COMMAND_TO_THE_CONTROLLER(0x0C);
    __delay_ms(100);
    LCD_COMMAND_TO_THE_CONTROLLER(0x01);
    __delay_ms(100);
}

void keyscane() {
    PORTB &= 0xF0;
    value = PORTB;

    switch (value) {
        case 0xE0:  // Show value
            LCD_COMMAND_TO_THE_CONTROLLER(0x80);
            for (x = 0; x < 15; x++) {
                LCD_DATA_TO_THE_CONTROLLER(array[x]);
            }
            LCD_OUTPUT(j);
            break;

        case 0xD0:  // Increment by 0.1
            j += 0.1;
            if (j > 225.0) j = 225.0;
            LCD_OUTPUT(j);
            if (j < 175.0) {
                PORTB |= 0x02;
                LCD_COMMAND_TO_THE_CONTROLLER(0xC0);
                for (x = 0; x < 14; x++) LCD_DATA_TO_THE_CONTROLLER(lb[x]);
            } else if (j > 205.0) {
                PORTB |= 0x08;
                LCD_COMMAND_TO_THE_CONTROLLER(0xC0);
                for (x = 0; x < 14; x++) LCD_DATA_TO_THE_CONTROLLER(hb[x]);
            } else {
                PORTB |= 0x04;
                LCD_COMMAND_TO_THE_CONTROLLER(0xC0);
                for (x = 0; x < 14; x++) LCD_DATA_TO_THE_CONTROLLER(nb[x]);
            }
            break;

        case 0xB0:  // Decrement by 0.1
            j -= 0.1;
            if (j < 155.0) j = 155.0;
            LCD_OUTPUT(j);
            if (j < 175.0) {
                PORTB |= 0x02;
                LCD_COMMAND_TO_THE_CONTROLLER(0xC0);
                for (x = 0; x < 14; x++) LCD_DATA_TO_THE_CONTROLLER(lb[x]);
            } else if (j > 205.0) {
                PORTB |= 0x08;
                LCD_COMMAND_TO_THE_CONTROLLER(0xC0);
                for (x = 0; x < 14; x++) LCD_DATA_TO_THE_CONTROLLER(hb[x]);
            } else {
                PORTB |= 0x04;
                LCD_COMMAND_TO_THE_CONTROLLER(0xC0);
                for (x = 0; x < 14; x++) LCD_DATA_TO_THE_CONTROLLER(nb[x]);
            }
            break;

        case 0x70:  // Reset to 155.0
            j = 155.0;
            LCD_OUTPUT(j);
            if (j < 175.0) {
                LCD_COMMAND_TO_THE_CONTROLLER(0xC0);
                for (x = 0; x < 14; x++) LCD_DATA_TO_THE_CONTROLLER(lb[x]);
            } else if (j > 205.0) {
                LCD_COMMAND_TO_THE_CONTROLLER(0xC0);
                for (x = 0; x < 14; x++) LCD_DATA_TO_THE_CONTROLLER(hb[x]);
            } else {
                LCD_COMMAND_TO_THE_CONTROLLER(0xC0);
                for (x = 0; x < 14; x++) LCD_DATA_TO_THE_CONTROLLER(nb[x]);
            }
            break;

        default:
            break;
    }
}

void LCD_COMMAND_TO_THE_CONTROLLER(unsigned char i) {
    PORTC &= ~(0x08); // RS = 0 (Command)
    PORTD = i;
    PORTC |= 0x01;    // EN = 1
    PORTC &= ~(0x01); // EN = 0
    __delay_ms(100);
}

void LCD_DATA_TO_THE_CONTROLLER(unsigned char i) {
    PORTC |= 0x08;    // RS = 1 (Data)
    PORTD = i;
    PORTC |= 0x01;    // EN = 1
    PORTC &= ~(0x01); // EN = 0
    __delay_ms(100);
}

void LCD_OUTPUT(float value) {
    int int_part = (int)value;
    int decimal_part = (int)((value - int_part) * 10);  // one decimal

    d3 = (unsigned char)(int_part / 100);
    d2 = (unsigned char)((int_part % 100) / 10);
    d1 = (unsigned char)(int_part % 10);

    LCD_COMMAND_TO_THE_CONTROLLER(0x88);
    LCD_DATA_TO_THE_CONTROLLER(0x30 + d3);
    LCD_COMMAND_TO_THE_CONTROLLER(0x89);
    LCD_DATA_TO_THE_CONTROLLER(0x30 + d2);
    LCD_COMMAND_TO_THE_CONTROLLER(0x8A);
    LCD_DATA_TO_THE_CONTROLLER(0x30 + d1);
    LCD_COMMAND_TO_THE_CONTROLLER(0x8B);
    LCD_DATA_TO_THE_CONTROLLER('.');  // decimal point
    LCD_COMMAND_TO_THE_CONTROLLER(0x8C);
    LCD_DATA_TO_THE_CONTROLLER(0x30 + decimal_part);
}
