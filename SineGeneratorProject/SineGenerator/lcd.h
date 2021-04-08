/*
 * lcd.h
 *
 * Created: 02.04.2021 18:32:32
 *  Author: PC
 */ 

#define F_CPU 16000000UL
#ifndef LCD_H_
#define LCD_H_
#include "main.h"

void LCD_ini(void);
void setpos(unsigned char x, unsigned y);
void str_lcd (char str1[]);
void sendchar(unsigned char c);


#endif /* LCD_H_ */