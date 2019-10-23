#include "bus.h"
#include "car_t.h"


Bus_t& Bus_t::operator=(const Bus_t _bus)
{
	if(this != &_bus)
	{
		Car_t::operator=(_bus);
		m_line = _bus.m_line; 
		m_seats = _bus.m_seats;
	}
	return *this;
}
