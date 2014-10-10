/* 
* LCD1602Half.cpp
*
* Created: 2014-10-09 오전 12:32:02
* Author: haksoo
*/


#include "LCD1602Half.h"

LCD1602Half * LCD1602Half::m_pInstance = NULL;
// default constructor
LCD1602Half::LCD1602Half()
{
	
	_init_PORT();			
} //LCD1602Half

// default destructor
LCD1602Half::~LCD1602Half()
{
} //~LCD1602Half

bool LCD1602Half::_init_PORT()
{
	m_RS = m_RW = m_E = 0;
	DDR_PORT = 0xFF;
	DATA_PORT = 0x00;
	return true;
}
bool LCD1602Half::_init_LCD()
{
	_init_PORT();
	
	m_RW = 0;
	m_RS = 0;
	_delay_ms(50);
	
	_output_half_high_byte(0b00110000); 	_delay_ms(50);
	_output_half_high_byte(0b00110000); 	_delay_ms(50);
	_output_half_high_byte(0b00110000); 	_delay_ms(50);
	
	_output_half_high_byte(0b00100000); // 4bit interface setting
	
	_output_control_byte(0b00101000); // 4bit interface setting
	
	
	
	
	
	return true;	
}
bool LCD1602Half::_output_control_byte(uint8_t data)
{
	m_RW = 0;
	m_RS = 0;
	_output_half_high_byte(data);
	_output_half_low_byte(data);
	return true;
}	
bool LCD1602Half::_output_data_byte(uint8_t data)
{
	m_RW = 1;
	m_RS = 0;
		
	return true;
}

bool LCD1602Half::_output_half_high_byte(uint8_t data)
{
	uint8_t temp;
	temp = ( (m_RW<<RW_PIN) | (m_RS<<RS_PIN) ) | ((data & 0xF0)>>4);
	DATA_PORT = temp;
	_pulse(temp);
	return true;
}
bool LCD1602Half::_output_half_low_byte(uint8_t data)
{
	uint8_t temp;
	temp = ( (m_RW<<RW_PIN) | (m_RS<<RS_PIN) ) | ((data & 0x0F));
	DATA_PORT = temp;
	_pulse(temp);
	return true;
}

void LCD1602Half::_pulse(uint8_t data)
{
	PULSE_DELAY_FUNCTION(PULSE_PERIOD);
	DATA_PORT = data | 1<<E_PIN;
	PULSE_DELAY_FUNCTION(PULSE_PERIOD);
	DATA_PORT = data;
	// only E pin should move here.
}





