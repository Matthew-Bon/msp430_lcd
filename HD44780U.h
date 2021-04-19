/*
 * HD44780U.h
 *
 *  Created on: Jan 6, 2021
 *      Author: M.Bon
 *
 *      Default pin definitions
 *      2.0 - D4
 *      2.1 - D5
 *      2.2 - D6
 *      2.3 - D7
 *      2.4 - R/S
 *      2.5 - R/W
 *      1.0 - Enable (if you don't like using 2 ports, 2.6 or 2.7 works well if you don't need to use an external crystal)
 *      Tested on the Sparkfun LCD-00255 (GMD1602K)
 *
 */

#ifndef HD44780U_H_
#define HD44780U_H_

void LCD_init();

void Write_data(char x); //4 bit data write

void Write_control(char x); //4bit control write
void Write_init_control(char x);
void Clear_display();
void Return_cursor();
void LCD_print(char lcd_string[]);



#define LCD_data    P2OUT               //Port 2 selection register
#define R_S BIT4
#define R_W BIT5
#define Enable BIT0
unsigned char   LCD_TEMP;





#endif /* HD44780U_H_ */
