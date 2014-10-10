/*
 * GccApplication2.cpp
 *
 * Created: 2014-09-30 오후 11:52:26
 *  Author: haksoo
 */ 
#define F_CPU 16000000UL 

#include <avr/io.h>
#include <avr/interrupt.h>

#include "LCD1602Driver.h"
#include <stdio.h>

uint8_t bit_map[8]={0b00000001,0b00000010,0b00000100,0b00001000,0b00010000,0b00100000,0b01000000,0b10000000};
uint8_t bit_map2[5]={0b00111000,0b00001111,0b00010000,0b00000001,0b00000011};
	
LCD1602Driver * gInstance=NULL;	
volatile uint8_t index = 0;	
volatile uint8_t index2 = 0;	
volatile uint64_t g_cnt = 0;
volatile bool g_flag = false;
ISR(INT0_vect)
{
	gInstance->write_string("init1");
}
ISR(TIMER0_COMP_vect)
{
	if(++g_cnt >= 62500)
	{
		g_cnt =0;
		if(g_flag)
		{
			PORTA=0xFF;	
			g_flag = false;
		}
		else
		{
			PORTA=0x00;	
			g_flag = true;
		}
		
	}
}

ISR(INT2_vect)
{
	index ++;
	char  data[100] ;
	sprintf(data,"counter %d input",index);
	gInstance->write_string(data);
}
void interrupt_control()
{
	DDRD =  0b11111000;
	PORTD=  0b00000111; //pull-up 
	
	EICRA = 0b10101010;
	EIMSK = 0b00000111;
	EICRB = 0x00;
	
}
void timer0_control()
{
	

	
	TCNT0 = 0;
	TCCR0 = 0b00011111;
	OCR0 = 0xFF;
	TIMSK = 0b00000011;
}

void system_control()
{
	DDRA = 0xFF;
	PORTA = 0xFF;
	interrupt_control();
	timer0_control();
	sei();
}


int main(void)
{
	int news_index = 0;
	char *news=" Is a possible threat to an ancient tomb at the heart of Turkey's debate on whether to step up its role in the fight against ISIS?The Turkish Parliament is debating and will vote later Thursday on whether to authorize the use of military force against ISIS fighters in Syria and Iraq.Up until now, Turkey, a NATO member, has declined to join a U.S.-led coalition, offering only tacit support to some 40 nations that make up the group going after ISIS in Iraq and Syria.But that seems to have changed in recent days, with ISIS on its doorstep, tens of thousands fleeing across its border and reports that the tomb of the grandfather of the founder of the Ottoman Empire has been surrounded.The tomb -- a white marble mausoleum -- is considered a Turkish enclave, despite its location inside Syria. As part of the Treaty of Ankara in 1921, which ended the Franco-Turkish War, Turkey was allowed to keep the tomb, place guards at it and raise a Turkish flag over it.";
	system_control();
	

	LCD1602Driver a = LCD1602Driver();
	a.write_string((char *)"Hello World my friend??");
	gInstance = &a;
	
	//gInstance->write_string((char *)"Hello my frined , I think we need to get together.");
	while(news_index < 963)
	{
		break; //////////////////////////////////////BREAK here to skip!
		gInstance->write_string(news+news_index);
		news_index+=32;
	}
	
    while(1)
    {
        //TODO:: Please write your application code 
    }
}