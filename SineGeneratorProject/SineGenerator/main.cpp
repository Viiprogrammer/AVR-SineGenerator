#include "config.h"
#include <avr/io.h>
#include <stdlib.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "buttons.h"
#include "compilers_4.h"
#include "lcd_lib_2.h"

const uint8_t B[] PROGMEM = {
	0b11111,
	0b10000,
	0b10000,
	0b11111,
	0b10001,
	0b10001,
	0b11110,
	0b0
};


volatile uint8_t pinus[256] =
{
	0x80,0x83,0x86,0x89,0x8C,0x8F,0x92,0x95,0x98,0x9B,0x9E,0xA2,0xA5,0xA7,0xAA,0xAD,
	0xB0,0xB3,0xB6,0xB9,0xBC,0xBE,0xC1,0xC4,0xC6,0xC9,0xCB,0xCE,0xD0,0xD3,0xD5,0xD7,
	0xDA,0xDC,0xDE,0xE0,0xE2,0xE4,0xE6,0xE8,0xEA,0xEB,0xED,0xEE,0xF0,0xF1,0xF3,0xF4,
	0xF5,0xF6,0xF8,0xF9,0xFA,0xFA,0xFB,0xFC,0xFD,0xFD,0xFE,0xFE,0xFE,0xFF,0xFF,0xFF,
	0xFF,0xFF,0xFF,0xFF,0xFE,0xFE,0xFE,0xFD,0xFD,0xFC,0xFB,0xFA,0xFA,0xF9,0xF8,0xF6,
	0xF5,0xF4,0xF3,0xF1,0xF0,0xEE,0xED,0xEB,0xEA,0xE8,0xE6,0xE4,0xE2,0xE0,0xDE,0xDC,
	0xDA,0xD7,0xD5,0xD3,0xD0,0xCE,0xCB,0xC9,0xC6,0xC4,0xC1,0xBE,0xBC,0xB9,0xB6,0xB3,
	0xB0,0xAD,0xAA,0xA7,0xA5,0xA2,0x9E,0x9B,0x98,0x95,0x92,0x8F,0x8C,0x89,0x86,0x83,
	0x80,0x7C,0x79,0x76,0x73,0x70,0x6D,0x6A,0x67,0x64,0x61,0x5D,0x5A,0x58,0x55,0x52,
	0x4F,0x4C,0x49,0x46,0x43,0x41,0x3E,0x3B,0x39,0x36,0x34,0x31,0x2F,0x2C,0x2A,0x28,
	0x25,0x23,0x21,0x1F,0x1D,0x1B,0x19,0x17,0x15,0x14,0x12,0x11,0x0F,0x0E,0x0C,0x0B,
	0x0A,0x09,0x07,0x06,0x05,0x05,0x04,0x03,0x02,0x02,0x01,0x01,0x01,0x00,0x00,0x00,
	0x00,0x00,0x00,0x00,0x01,0x01,0x01,0x02,0x02,0x03,0x04,0x05,0x05,0x06,0x07,0x09,
	0x0A,0x0B,0x0C,0x0E,0x0F,0x11,0x12,0x14,0x15,0x17,0x19,0x1B,0x1D,0x1F,0x21,0x23,
	0x25,0x28,0x2A,0x2C,0x2F,0x31,0x34,0x36,0x39,0x3B,0x3E,0x41,0x43,0x46,0x49,0x4C,
	0x4F,0x52,0x55,0x58,0x5A,0x5D,0x61,0x64,0x67,0x6A,0x6D,0x70,0x73,0x76,0x79,0x7C
};

volatile uint16_t M = M_VALUE;
volatile uint32_t buck = 0, freq = DEFAULT_FREQ, step = 0;
volatile uint8_t SET = 0;

//5 индекс не трогать, он зарезервирован точкой
uint32_t position[7] = {100000, 10000, 1000, 100, 0, 10, 1};
	
ISR(TIMER0_OVF_vect)
{
	buck += step;
	PORTD = pinus[(buck >> 24)];
}

void timer0_init()
{
	TCCR0 = (1 << CS00);
	TIMSK = (1 << TOIE0);
	
}
void port_ini(void)
{
	PORTB = 0x00;
	DDRB = 0xFF;
}
void printFreq(){
	//Вывод частоты
	LCD_Goto(0, 0);
	LCD_WriteData((freq / 100000)+0x30);
			
	LCD_Goto(1, 0);
	LCD_WriteData(((freq % 100000)/10000)+0x30);
			
	LCD_Goto(2, 0);
	LCD_WriteData(((freq % 10000)/1000)+0x30);
			
	LCD_Goto(3, 0);
	LCD_WriteData(((freq % 1000)/100)+0x30);
			
	LCD_Goto(4, 0);
	LCD_WriteData('.');
			
	LCD_Goto(5, 0);
	LCD_WriteData(((freq % 100)/10)+0x30);
			
	LCD_Goto(6, 0);
	LCD_WriteData((freq % 10)+0x30);
			
	LCD_SendStr(" Hz");
			
	LCD_Goto(13, 1);
	LCD_SendStr("CK");
	LCD_WriteData(0);
}
void changeNumber(uint8_t positionNumber, uint8_t type){
	#if FREQ_NUMBER_RANK_LIMIT == 1
		uint8_t checkNumberLimit = 0;

		if(positionNumber){
			if(positionNumber >= 4){
				checkNumberLimit = (freq % position[positionNumber-1]) / position[positionNumber+1];
				} else {
				checkNumberLimit = (freq % position[positionNumber-1]) / position[positionNumber];
			}
			} else {
			checkNumberLimit = freq / position[positionNumber];
		}
	#endif
	if(type){
		#if FREQ_NUMBER_RANK_LIMIT == 1
		if(freq < MAX_FREQ && freq + position[positionNumber] <= MAX_FREQ && checkNumberLimit != 9) {
		#else	
		if(freq < MAX_FREQ && freq + position[positionNumber] <= MAX_FREQ) {
		#endif	
			freq += position[positionNumber];
		}
	} else {
		#if FREQ_NUMBER_RANK_LIMIT == 1
		if(freq > MIN_FREQ  && freq >= position[positionNumber] && freq - position[positionNumber] >= MIN_FREQ && checkNumberLimit != 0){
		#else	
		if(freq > MIN_FREQ  && freq >= position[positionNumber] && freq - position[positionNumber] >= MIN_FREQ){
		#endif	
			freq -= position[positionNumber];
		}
	}	
	step = M*freq;	
}

int main(void)
{
	step = M*freq;
	DDRD = 255;
	PORTD = 0;
	BUT_Init();
	timer0_init();
		
	LCD_Init();
	LCD_SetUserChar(B, 0); 
	LCD_Goto(0, 0);

	LCD_SendStr("  DESIGNED BY  ");
	LCD_Goto(2, 1);
	LCD_WriteData('"');
	LCD_SendStr("CK");
	LCD_WriteData(0);
	LCD_WriteData('"');

	LCD_SendStr(VERSION);
	
	_delay_ms(1000);
	
	//LCD clear
	LCD_Clear();

	//Рисуем стрелочку
	LCD_Goto(0, 1);
	LCD_WriteData('^');

    sei();
    while (1) 
    {
		uint8_t button = 0, buttonCode = 0;
		BUT_Poll(); //Опрос кнопок

		//Проверка буфера кнопок и получения ID нажатой кнопки
		button = BUT_GetBut();
		if (button){
			//Повторный вызов функции для получения типа события кнопки
			buttonCode = BUT_GetBut();


			//Увеличиваем
			if(button == BUTTON_INCREMENT && buttonCode == BUT_PRESSED_CODE){
				cli();
			    changeNumber(SET, INCREMENT);
				sei();
			//Уменьшаем
			} else if(button == BUTTON_DECREMENT && buttonCode == BUT_PRESSED_CODE){
				cli();
				changeNumber(SET, DECREMENT);
				sei();
			//Двигаем вправо 	
			}  else if(button == BUTTON_LEFT && buttonCode == BUT_PRESSED_CODE){
				if (SET >= MIN_SET)
				{		
					//Очищаем стрелочку слектор
					LCD_Goto(SET, 1);	
					LCD_WriteData(' ');
					if(SET == 5){
						SET -= 2;
					} else {
						SET--;
					}
					//Рисуем новую стрелочку
					LCD_Goto(SET, 1);
					LCD_WriteData('^');
				}
			//Двигаем влево 	
			}  else if(button == BUTTON_RIGHT && buttonCode == BUT_PRESSED_CODE){
				if (SET < MAX_SET)
				{		
					//Очищаем стрелочку слектор
					LCD_Goto(SET, 1);
					LCD_WriteData(' ');
					
						
					if(SET == 3){
						SET += 2;
					} else {
						SET++;
					}
							
					LCD_Goto(SET, 1);
					LCD_WriteData('^');
				}
			}
		}
		
		printFreq();
	}
}

