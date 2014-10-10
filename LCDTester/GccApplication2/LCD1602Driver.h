/* 
* LCD1602Driver.h
*
* Created: 2014-09-30 오후 11:53:48
* Author: haksoo
*/
#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>

#ifndef __LCD1602DRIVER_H__
#define __LCD1602DRIVER_H__


#ifndef NULL
#define NULL (0)
#endif

#define DATA_PORT PORTE
#define DDR_DATA_PORT DDRE

#define CTRL_PORT PORTC
#define DDR_CTRL_PORT DDRC

#define PULSE_PIN (1<<2)

#define INTERFACE_FULL (true)
#define INTERFACE_HALF (false)

#define MAX_LINE_LENGTH (16)
#define PULSE_DELAY _delay_us
#define DELAY_PERIOD (1000)


//Singleton
class LCD1602Driver
{
//variables
public:

protected:
private:
	bool m_bInterface;
//functions
public:
	LCD1602Driver();
	LCD1602Driver(bool);
	~LCD1602Driver();
	bool write_string(char * data);
	bool initDevice();		
		
protected:
private:



	bool _initDeviceHalfInterface();	
	bool _initDeviceFullInterface();	
	
	bool _write_control_port(bool,bool);
	bool _write_data_port(volatile uint8_t );
	bool _pulse();
	bool m_RS;
	bool m_RW;
	

	
	
	bool _clearscreen();
	bool _moveNextLine();
	
	
public: 
	bool _write_char(char data) ;
}; //LCD1602Driver

#endif //__LCD1602DRIVER_H__
