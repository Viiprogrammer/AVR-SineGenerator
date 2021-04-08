#ifndef CONFIG_H
	#define CONFIG_H
	#define F_CPU 16000000UL
	/* 
	  Если равно 1 то число разряда будет лимитировано в пределах 0-9 и не будет меньшатся или увеличиватся влияя на соседний разряд
	*/
	#define FREQ_NUMBER_RANK_LIMIT 0
	
	#define M_VALUE 688
	
	#define VERSION "v1.0.0"
	
	//Лимиты частоты
	#define MAX_FREQ 500000
	#define MIN_FREQ 100

	//Частота по умолчанию
	#define DEFAULT_FREQ 100

	#define INCREMENT 1
	#define DECREMENT 0

	//Лимит курсора
	#define MAX_SET 6
	#define MIN_SET 1

	//ID кнопок
	#define BUTTON_INCREMENT 1
	#define BUTTON_DECREMENT 2
	#define BUTTON_LEFT 3
	#define BUTTON_RIGHT 4
#endif