#ifndef __PRIVATE_H__
#define __PRIVATE_H__


#include <string>
#include <iostream>
#include "car_t.h"
using namespace std;

class Private_t:public Car_t
{

private:
	size_t m_speed;

public:
	//CTOR
	Private_t()										{SetGear(STANDARD);SetName("private"); m_speed = 100;}
	Private_t(const Private_t& _private): 
		Car_t(_private),m_speed(_private.m_speed) 	{SetName("private"); SetGear(STANDARD);}

	Private_t(size_t _capacity, size_t _speed):
				Car_t(_capacity),m_speed(_speed)	{SetName("private"); SetGear(STANDARD);}
	
	//DCTOR
	~Private_t(){}

	//FUNCTIONS
	void IncSpeed() 								{m_speed += 10;}					// increment the speed by 10
	void DecSpeed() 								{if(m_speed <= 10){m_speed -= 10;}}				// decrement the speed by 10
	void SetSpeed(int _speed) 						{m_speed = _speed;}
	size_t GetSpeed() const 						{return m_speed;}					// return the speed of the private car

	//OPERATORS
	Private_t& operator=(const Private_t& _private);

};
/*
ostream& operator<<(ostream& _os, Private_t& _p);
{
	//operator<<(_os, _p);
	_os << "speed: "<< _p.GetSpeed() << endl;
	return _os;
}*/
#endif /*__PRIVATE_H__*/
