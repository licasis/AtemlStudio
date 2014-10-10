/*
 * LCDDriver4BitInterface.cpp
 *
 * Created: 2014-10-09 오전 1:33:47
 *  Author: haksoo
 */ 


#include <avr/io.h>
#include "LCD1602Half.h"
int main(void)
{
	uint8_t temp = 0xF0;
	DDRA = 0xFF;
	PORTA = temp;
	PORTA = temp>>1;
	PORTA = temp>>2;
	PORTA = temp>>3;
	PORTA = temp>>4;
	PORTA = temp>>5;
	temp = 0b10111000;
	PORTA = (temp & 0xF0)>>4;
	
	PORTA = 0xF0;
	LCD1602Half::getInstance()->test1();
	
	
    while(1)
    {
        //TODO:: Please write your application code 
    }
}