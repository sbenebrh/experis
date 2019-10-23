#ifndef __CAR_H__
#define __CAR_H__

#include <string>
#include <iostream>
using namespace std;


class Car_t
{
public:
	enum Car_Gear
	{
		STANDARD, 
		AUTOMATIC
	};

private:
	static size_t 	s_id;													// counter to get unique id
	const size_t 	m_id;													// id of the car
	string 			m_name;													// name of the car
	Car_Gear 		m_gear;													// gear of the car once set can't be change
	int 			m_capacity;												// capacity of the engine
	bool 			m_flag;

protected:
	~Car_t(){}
	void SetName(string _str) 			{m_name = _str;}
	void SetGear(Car_Gear _gear) 		{if(!m_flag){m_gear = _gear;m_flag = 1;}}
	void SetCapacity(size_t _capacity)	{m_capacity = _capacity;}
	void SetFlag() 						{ m_flag = 1;}
public:

	//CTOR/DCTOR
	Car_t():m_id(s_id), m_capacity(1500){s_id++;}							// default CTOR
	Car_t(const Car_t& _car);												//copy CTOR
	Car_t(int _capacity):m_id(s_id), m_capacity(_capacity) {s_id++;}

	//OPERATOR
	Car_t& 	operator=(const Car_t& _car);									// assignement from car . it do not copy the id bu get a new one
	bool 	operator<(const Car_t& _car) const {return (m_capacity < _car.m_capacity);}
	bool 	operator==(const Car_t& _car) const {return (m_name == _car.m_name);}

	//function
	int 			GetCapacity() 	const { return m_capacity;}
	Car_Gear 		GetGear() 		const { return m_gear;}
	const string& 	GetName() 		const { return m_name;}
	size_t 			GetId() 		const { return m_id;}

};

ostream& operator<<(ostream& _os, Car_t& _car);
//istream& operator>>(istream _is, Car_t& _car);

#endif /*__CAR_H__*/
