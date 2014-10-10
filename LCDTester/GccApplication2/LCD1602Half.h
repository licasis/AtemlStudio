/* 
* LCD1602Half.h
*
* Created: 2014-10-09 오전 12:32:02
* Author: haksoo
*/


#ifndef __LCD1602HALF_H__
#define __LCD1602HALF_H__

#ifndef F_CPU
    #define F_CPU 16000000UL 
#endif


#include <stdio.h>
#include <stdlib.h>
#include <avr/io.h>
#include <util/delay.h>


#define DDR_PORT  DDRE
#define DATA_PORT PORTE

#define RS_PIN (5)
#define RW_PIN (6)
#define E_PIN (7)
#define PULSE_DELAY_FUNCTION _delay_ms
#define PULSE_PERIOD (10)

#define mkCOM(RS,RW,E) ((RS)<<RS_PIN | (RW)<<RW_PIN | (E)<<E_PIN)


class LCD1602Half
{
//variables
public:
protected:
private:
	uint8_t m_RS;
	uint8_t m_RW;
	uint8_t m_E;
	LCD1602Half();
	static LCD1602Half * m_pInstance;
	LCD1602Half( const LCD1602Half &c );
	LCD1602Half& operator=( const LCD1602Half &c );
	bool _init_LCD();
	
	bool _init_PORT();
	
	bool _output_control_byte(uint8_t data);
	bool _output_data_byte(uint8_t data);
	bool _output_half_high_byte(uint8_t data);

	void _pulse(uint8_t data);

	
//functions
protected:
private:
public:
	~LCD1602Half();
	
	void * operator new(size_t size)
	{
		return malloc(size);
	}
	void operator delete(void * ptr)
	{
		free(ptr);
	}

	

}; //LCD1602Half

#endif //__LCD1602HALF_H__
