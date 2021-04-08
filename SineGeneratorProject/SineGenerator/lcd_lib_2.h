//***************************************************************************
//  File........: lcd_lib.h
//
//  Author(s)...: Pashgan    chipenable.ru
//
//  Target(s)...: ATMega...
//
//  Compiler....: IAR, CodeVision, GNU GCC
//
//  Description.: ƒрайвер знакосинтезирующего жк диспле€
//
//  Data........: 20.07.13  
//
//***************************************************************************
#ifndef LCD_LIB_H
#define LCD_LIB_H
#include "config.h"
#include "compilers_4.h"

#define VIRT_PORT
#ifdef VIRT_PORT

//здесь € определил виртуальный порт

//шина данных LCD
#define LCD_PORT  LCD_DATA, F, _VIRT

#define LCD_DATA_0  D, 0, _NONE
#define LCD_DATA_1  D, 1, _NONE
#define LCD_DATA_2  D, 2, _NONE
#define LCD_DATA_3  C, 5, _NONE
#define LCD_DATA_4  B, 4, _HI
#define LCD_DATA_5  B, 5, _HI
#define LCD_DATA_6  B, 0, _HI
#define LCD_DATA_7  C, 5, _HI

//управл€ющие выводы LCD
#define LCD_RS  B, 2, _HI
#define LCD_RW  B, 1, _HI
#define LCD_EN  B, 3, _HI  

#else

//а здесь € определил реальный порт

//шина данных LCD
#define LCD_PORT  LCD_DATA, A, _REAL

#define LCD_DATA_0  A, 0, _HI
#define LCD_DATA_1  A, 1, _HI
#define LCD_DATA_2  A, 2, _HI
#define LCD_DATA_3  A, 3, _HI
#define LCD_DATA_4  A, 4, _HI
#define LCD_DATA_5  A, 5, _HI
#define LCD_DATA_6  A, 6, _HI
#define LCD_DATA_7  A, 7, _HI

//управл€ющие выводы LCD
#define LCD_RS  D, 5, _HI
#define LCD_RW  D, 6, _HI
#define LCD_EN  D, 7, _HI

#endif

/*____________________________________________________________________*/

//глобальные настройки драйвера
#define LCD_CHECK_FL_BF             1
#define LCD_BUS_4_8_BIT             0

//настройки инициализации диспле€
#define LCD_ONE_TWO_LINE            1
#define LCD_FONT58_FONT511          0
#define LCD_DEC_INC_DDRAM           1
#define LCD_SHIFT_RIGHT_LEFT        0
#define LCD_DISPLAY_OFF_ON          1
#define LCD_CURSOR_OFF_ON           0
#define LCD_CURSOR_BLINK_OFF_ON     0
#define LCD_CURSOR_DISPLAY_SHIFT    0

/*_____________________макро функции________________________________*/

//команды
#define LCD_CLEAR_DISPLAY  0x01
#define LCD_RETURN_HOME    0x02

//очистка диспле€
#define LCD_Clear() do{LCD_WriteCom(LCD_CLEAR_DISPLAY); _delay_ms(2);}while(0)   

//возврат курсора в начальное положение
#define LCD_ReturnHome()  do{LCD_WriteCom(LCD_RETURN_HOME);}while(0)

//позиционирование курсора
#define LCD_Goto(x, y)    LCD_WriteCom(((((y)& 1)*0x40)+((x)& 15))|128)  

/*___________________пользовательские функции_______________________*/

void LCD_Init(void);                                  //инициализаци€ портов и жкд по умолчанию
void LCD_WriteCom(uint8_t data);                      //посылает команду жкд
void LCD_WriteData(char data);                        //выводит символ на жкд
void LCD_SendStr(const char *str);                          //выводит строку из ќ«”

#ifdef __GNUC__
   void LCD_SendStrFl(char *str);                           //выводит строку из флэш пам€ти     
   void LCD_SetUserChar(uint8_t const *sym, uint8_t adr);   //загрузить пользовательский символ
#else
   void LCD_SendStrFl(char __flash *str);                   //выводит строку из флэш пам€ти
   void LCD_SetUserChar(uint8_t __flash *sym, uint8_t adr); //загрузить пользовательский символ
#endif

#endif