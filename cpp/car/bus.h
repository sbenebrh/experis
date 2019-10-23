#ifndef __BUS_H__
#define __BUS_H__


#include <string>
#include <iostream>
#include "car_t.h"
using namespace std;

class Bus_t:public Car_t
{
private:
	size_t m_line;
	size_t m_seats;
public:
	Bus_t()															{ SetGear(AUTOMATIC);SetName("bus"); m_line = 0; m_seats = 0;}
	Bus_t(const Bus_t& _bus): 
		Car_t(_bus),m_line(_bus.m_line), m_seats(_bus.m_seats) 		{ SetName("bus"); SetGear(AUTOMATIC);}
	Bus_t(size_t _capacity, size_t _numOfSeats, size_t _line):
			Car_t(_capacity), m_line(_line), m_seats(_numOfSeats)	{ SetName("bus"); SetGear(AUTOMATIC);}
	~Bus_t(){}

	void SetLine(size_t _line) 										{ m_line = _line;}
	void SetSeats(size_t _seats) 									{ m_seats = _seats;}

	size_t GetSeats() const 										{ return m_seats;}
	size_t GetLine() const											{ return m_line;} 
	
	Bus_t& operator=(const Bus_t _bus);
};

#endif /*__BUS_H__*/
