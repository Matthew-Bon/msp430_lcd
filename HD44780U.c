/*
 * HD44780U.c
 *
 *  Created on: Mar 16, 2021
 *      Author: M.Bon
 *
 *  Tested on the Sparkfun LCD-00255 (GMD1602K)
 */
#include "HD44780U.h"
#include <msp430.h>
#include <stdio.h>
#include <string.h>

/*Initialize LCD 16x2, 4 bit interface,  Cursor in the upper left */
void LCD_init()
{



    /* Configure port 2 for LCD operation */
    P1DIR |= BIT0;
    P2SEL |= 0; //Set port 2 to GPIO
    P2DIR |= 255; //Set all pins as outputs
    P2OUT = 0x00; //Ensure all pins are set low
    P1SEL &= ~BIT0;
    P1DIR |= BIT0;
    P1OUT &= ~BIT0;

        __delay_cycles(150000); //delay 15ms
        Write_init_control(0x20);
        __delay_cycles(50000);
        Write_init_control(0x20);
        __delay_cycles(10000);
        Write_init_control(0x20);
        __delay_cycles(50000);
        Write_control(0x28);
        __delay_cycles(20000);
        Write_control(0x28);
        __delay_cycles(20000);
        Write_control(0x28);
        Write_control(0x08);//Cursor moves right and DDRAM addr +1
        Write_control(0x0F);//Enable Display, cursor on, cursor blink
        Write_control(0x02);//Return Cursor to start
        Write_control(0x01);//Clear Display



}

/* 4 bit data write*/
void Write_data(char x)
{
        P1OUT &= ~Enable;// ensure enable is low
        P2OUT = 0; //Clear Ouput register
        P2OUT ^= R_S; //select data
        P2OUT &= ~R_W;//Select Write
        LCD_TEMP = x;//load temp
        LCD_TEMP >>= 4; // shift temp by 4
        P2OUT |= LCD_TEMP; //load data from temp
        P1OUT ^= Enable;// enable lcd
        __delay_cycles(20000);//delay

        P1OUT ^= Enable;//disable lcd
        P2OUT = 0; //Clear Ouput register
        P2OUT ^= R_S; //select data
        P2OUT &= ~R_W;//Select Write
        LCD_TEMP = x;//load temp again
        LCD_TEMP <<= 4;
        LCD_TEMP >>= 4;
        P2OUT |= LCD_TEMP;//send lower 4.
        P1OUT ^= Enable;//enable lcd
        __delay_cycles(20000);//delay
        P1OUT ^= Enable;//disable
        __delay_cycles(20000);//delay
        P1OUT &= ~Enable;// ensure enable is low
        P2OUT = 0; //Clear Ouput register
}

/* 4bit control write*/
void Write_control(char x)
{
        P1OUT &= ~Enable;// ensure enable is low
        P2OUT = 0; //Clear Ouput register
        P2OUT &= ~R_S; //select instructions
        P2OUT &= ~R_W;//Select Write
        LCD_TEMP = x;//load temp
        LCD_TEMP >>= 4; // shift temp by 4
        P2OUT |= LCD_TEMP; //load data from temp
        P1OUT ^= Enable;// enable lcd
        __delay_cycles(20000);//delay

        P1OUT ^= Enable;//disable lcd
        P2OUT = 0; //Clear Ouput register
        P2OUT &= ~R_S; //select instructions
        P2OUT &= ~R_W;//Select Write
        LCD_TEMP = x;//load temp again
        LCD_TEMP <<= 4;
        LCD_TEMP >>= 4;
        P2OUT |= LCD_TEMP;//send lower 4.
        P1OUT ^= Enable;//enable lcd
        __delay_cycles(20000);//delay
        P1OUT ^= Enable;//disable
        __delay_cycles(20000);//delay
        P1OUT &= ~Enable;// ensure enable is low
        P2OUT = 0; //Clear Ouput register
}

/*Simplified control write function to make the initialization easier*/
void Write_init_control(char x)
{
        P1OUT &= ~Enable;// ensure enable is low
        P2OUT = 0; //Clear Ouput register
        P2OUT &= ~R_S; //select instructions
        P2OUT &= ~R_W;//Select Write
        LCD_TEMP = x;//load temp
        LCD_TEMP >>= 4; // shift temp by 4
        P2OUT |= LCD_TEMP; //load data from temp
        P1OUT ^= Enable;// enable lcd
        __delay_cycles(20000);//delay
        //P1OUT ^= Enable;//disable lcd
        P1OUT &= ~Enable;// ensure enable is low
        P2OUT = 0; //Clear Ouput register

}

/* Wipes display and returns cursor*/
void Clear_display()
{
  Write_control(0x01);
}

/*Returns cursor to upper left*/
void Return_cursor()
{
 Write_control(0x02);
}

/*Prints string to LCD*/
void LCD_print(char lcd_string[])
{
    int j = 0;
    for ( j = 0; j < strlen(lcd_string); j++)
    {
        if (j==16)
        {
            cursor_2nd_line();
        }
        Write_data(lcd_string[j]);
    }
}

void cursor_2nd_line()
{
    Write_control(0xC0);
}

void cursor_middle_1()
{
    Write_control(0x87);
}
void cursor_middle_2()
{
    Write_control(0xC7);
}





