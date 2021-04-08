#ifndef CONFIG_H
	#define CONFIG_H
	#define F_CPU 16000000UL
	/* 
	  ���� ����� 1 �� ����� ������� ����� ������������ � �������� 0-9 � �� ����� ��������� ��� ������������ ����� �� �������� ������
	*/
	#define FREQ_NUMBER_RANK_LIMIT 0
	
	#define M_VALUE 688
	
	#define VERSION "v1.0.0"
	
	//������ �������
	#define MAX_FREQ 500000
	#define MIN_FREQ 100

	//������� �� ���������
	#define DEFAULT_FREQ 100

	#define INCREMENT 1
	#define DECREMENT 0

	//����� �������
	#define MAX_SET 6
	#define MIN_SET 1

	//ID ������
	#define BUTTON_INCREMENT 1
	#define BUTTON_DECREMENT 2
	#define BUTTON_LEFT 3
	#define BUTTON_RIGHT 4
#endif