/*
 * HD44780U.c
 *
 *  Created on: Mar 16, 2021
 *      Author: M.Bon
 */
#include "HD44780U.h"
#include <msp430.h>
#include <stdio.h>
#include <string.h> //github is dumb

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
        Write_init_control(0x21);
        __delay_cycles(50000);
        Write_init_control(0x21);
        __delay_cycles(10000);
        Write_init_control(0x21);
        __delay_cycles(50000);
        Write_init_control(0x20);
        __delay_cycles(20000);
        Write_init_control(0x20);
        __delay_cycles(20000);
        Write_control(0x08);//Curser moves right and DDRAM addr +1
        Write_control(0x02);//Return Curser to start
        Write_control(0x01);//Clear Display
        Write_control(0x0F);//Enable Display, curser on, curser blink



}

void Write_data(char x) //4 bit data write
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

void Write_control(char x) //4bit control write
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

void Write_init_control(char x) //4bit control write
{
        P1OUT &= ~Enable;// ensure enable is low
        P2OUT = 0; //Clear Ouput register
        P2OUT &= ~R_S; //select instructions
        P2OUT &= ~R_W;//Select Write
        LCD_TEMP = x;//load temp
        P2OUT |= LCD_TEMP; //load data from temp
        P1OUT ^= Enable;// enable lcd
        __delay_cycles(20000);//delay
        //P1OUT ^= Enable;//disable lcd
        P1OUT &= ~Enable;// ensure enable is low
        P2OUT = 0; //Clear Ouput register

}


void Write_control_start(char x) //4bit control write
{
        P1OUT &= ~Enable;// ensure enable is low
        P2OUT = 0; //Clear Ouput register
        P2OUT &= ~R_S; //select instructions
        P2OUT &= ~R_W;//Select Write
        LCD_TEMP = x;//load temp
        LCD_TEMP >>= 4; // shift temp by 4
        P2OUT = LCD_TEMP; //load data from temp
        P1OUT ^= Enable;// enable lcd
        __delay_cycles(20000);//delay

        P1OUT ^= Enable;//disable lcd
        P2OUT &= ~R_S; //select instructions
        P2OUT &= ~R_W;//Select Write
        LCD_TEMP = x;//load temp again
        LCD_TEMP <<= 4;
        LCD_TEMP >>= 4;
        P2OUT = LCD_TEMP;//send lower 4.
        P1OUT ^= Enable;//enable lcd
        __delay_cycles(20000);//delay
        P1OUT ^= Enable;//disable
        __delay_cycles(20000);//delay
        P1OUT &= ~Enable;// ensure enable is low
        P2OUT = 0; //Clear Ouput register
}

void Clear_display()
{
  Write_control(0x01);
}

void Return_curser()
{
 Write_control(0x02);
}

void LCD_print(char lcd_string[])
{
    int j = 0;
    for ( j = 0; j < strlen(lcd_string); j++)
    {
        Write_data(lcd_string[j]);
    }
}





