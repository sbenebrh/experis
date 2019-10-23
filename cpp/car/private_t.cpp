#include "private_t.h"


Private_t& Private_t::operator=(const Private_t& _private)
{
	if(this != &_private)
	{
		Car_t::operator=(_private);
		m_speed = _private.m_speed;
	}
	return *this;
}
