/* 
* LCD1602Driver.cpp
*
* Created: 2014-09-30 오후 11:53:48
* Author: haksoo
*/


#include "LCD1602Driver.h"

LCD1602Driver::LCD1602Driver()
{
	m_bInterface = INTERFACE_FULL;
	m_RS=0;
	m_RW=0;
	initDevice();
		
		
} //LCD1602Driver

LCD1602Driver::LCD1602Driver(bool inter)
{
	m_bInterface = inter;
	m_RS=0;
	m_RW=0;
	initDevice();
} //LCD1602Driver

// default destructor
LCD1602Driver::~LCD1602Driver()
{
} //~LCD1602Driver
bool LCD1602Driver::initDevice()
{
	(m_bInterface==INTERFACE_FULL)?_initDeviceFullInterface():_initDeviceHalfInterface();
	return true;
}
bool LCD1602Driver::_initDeviceHalfInterface()
{
	_delay_ms(50); // first delay at least 50ms.
	return true;
}
bool LCD1602Driver::_initDeviceFullInterface()
{
	_delay_ms(100); // first delay at least 50ms.

	DDR_CTRL_PORT = 0xff;
	DDR_DATA_PORT = 0xff;

	_write_control_port(false,false);
	_write_data_port(0b00110000);
	_pulse();
	_delay_ms(50);
	
	
	_write_control_port(false,false);
	_write_data_port(0b00110000);
	_pulse();
	_delay_ms(50);
	
	
	_write_control_port(false,false);
	_write_data_port(0b00110000);
	_pulse();
	_delay_ms(50);
	
	
	
	_write_control_port(false,false);

	_write_data_port(0b00111000); //DL,N,F
	_pulse();
	
	_write_data_port(0b00001101);
	_pulse();
	
	
	_write_data_port(0b00010000);
	_pulse();
		
		
	_write_data_port(0b00000001);
	_pulse();
	
	_write_data_port(0b00000110);//맨끝 비트(0번)를 셋하면, 0번째 주소값문자는 안 찌김
	_pulse();
	_delay_ms(50);
	return true;
}
bool LCD1602Driver::_clearscreen()
{
	_write_control_port(false,false);
	_write_data_port(0b00000001); //clear
	_pulse();
	return true;
}

bool LCD1602Driver::_moveNextLine()
{
	_write_control_port(false,false);
	_write_data_port(0b10000000 |  0x40); //move AC to second line address
	_pulse();
	return true;
}

bool LCD1602Driver::write_string(char * data)
{
	int index = 0;
	bool line=0;
	
	_clearscreen();
	//PORTA = 0xFF;
	while(1)
	{
		
		switch ( *(data+index) )
		{
			case '\r':
				PORTA = 0x04;
			break;
			
			case '\n':
			//	PORTA = 0x01;
				if(line)
					return false; // if one line over 16charecters,  second line wont be shown up
				else
					_moveNextLine();
					line = 1;
					break;
			case '\0': // the end of line
			//	PORTA = 0x03;
				return true;

			default:
				_write_char(*(data+index));
		}
		index++;
		if(index == 16 && line == 0)
		{
			line = 1;
			_moveNextLine();	
		}
		if(index == 32)
		{
			return false;
		}
	}
	return true;
	
}
bool LCD1602Driver::_write_char(char data)
{
	_write_control_port(true,false);
	_write_data_port(data);
	_pulse();
	return true;
}
bool LCD1602Driver::_write_control_port(bool RS,bool RW )
{
		m_RS = RS;
		m_RW = RW;
		CTRL_PORT  = (RS?1:0) | (RW?1:0)<<1;

	return true;	
}
bool LCD1602Driver::_write_data_port(volatile uint8_t data )
{

	DATA_PORT = data;
	return true;	
}
bool LCD1602Driver::_pulse()
{
	//_delay_ms(1);
	PULSE_DELAY(DELAY_PERIOD);
	CTRL_PORT =(m_RS?1:0) | (m_RW?1:0)<<1 | (1<<2);
	PULSE_DELAY(DELAY_PERIOD);
	CTRL_PORT = (m_RS?1:0) | (m_RW?1:0)<<1;
	PULSE_DELAY(DELAY_PERIOD);
	return true;
}



