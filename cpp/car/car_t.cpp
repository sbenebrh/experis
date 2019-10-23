#include <iostream>
#include <string>
#include "car_t.h"

size_t Car_t::s_id = 1;


Car_t::Car_t(const Car_t& _car):m_id(s_id)
{
	m_name 		= _car.m_name;
	m_gear 		= _car.m_gear;
	m_capacity 	= _car.m_capacity;
}

Car_t& 	Car_t::operator=(const Car_t& _car)
{
	if(this != &_car)
	{
		m_name 		= _car.m_name;
		m_gear 		= _car.m_gear;
		m_capacity 	= _car.m_capacity;	
	}
	return *this;
}

ostream& operator<<(ostream& _os, Car_t& _car)
{
	_os << "id: 		"<< _car.GetId() << endl
		<<"name: 		"<< _car.GetName()<<endl
		<<"capacity:	"<< _car.GetCapacity() << endl
		<< "gear: 		"<< (_car.GetGear() ? "automatic": "standard");
	return _os;
}
