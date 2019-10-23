#include "string_t.h"

#include <string.h> 	// strlen
#include <iostream> 	// cout
#include <cmath> 	// ceil

using namespace std; 	//cout

#define PRE 	0
#define POST 	1

//###############################################INIT STATIC#######################################################

unsigned int 		String_t::s_capacity 	= 16;
bool 				String_t::s_caseSens 	= 1;

//##################################################################################################################
//################################################CTOR&DCTOR########################################################
//##################################################################################################################

String_t::String_t()
{
	m_str = CreateFrom(NULL);
}

String_t::String_t(const char* _str)
{
	m_capacity = 0;
	m_str = CreateFrom(_str);
}

String_t::String_t(const String_t& _str)
{
	m_capacity = 0;
	m_str = CreateFrom(_str.m_str);
}

String_t::~String_t()
{
	delete[] m_str;
}

//##################################################################################################################
//####################################################OPERATOR######################################################
//##################################################################################################################

String_t&  String_t::operator=(const String_t& _str)
{
	if(&_str != this)
	{ 
		m_str = CreateFrom(_str.m_str);	
	}
	return *this;
}

String_t& 	String_t::operator+=(const String_t& _str)
{
	ExtendString(_str.m_str, POST);
	return *this;
}

String_t& 	String_t::operator+=(const char* _str)
{
	if(_str != NULL)
	{
		ExtendString(_str, POST);
	}
	return *this;
}

bool String_t::operator<(const String_t& _str) const
{
	return s_caseSens ?
		(strcmp(m_str, _str.m_str) < 0) : 
		(strcasecmp(m_str, _str.m_str) < 0);
}

bool String_t::operator>(const String_t& _str) const
{
	return s_caseSens ?
		(strcmp(m_str, _str.m_str) > 0) : 
		(strcasecmp(m_str, _str.m_str) > 0);
}

bool String_t::operator<=(const String_t& _str) const
{
	return s_caseSens ? 
		(strcmp(m_str, _str.m_str) <= 0) : 
		(strcasecmp(m_str, _str.m_str) <= 0);
}

bool String_t::operator>=(const String_t& _str) const
{
	return s_caseSens ?
		(strcmp(m_str, _str.m_str) >= 0) : 
		(strcasecmp(m_str, _str.m_str) >= 0);
}

bool String_t::operator==(const String_t& _str) const
{
	return s_caseSens ? 
		(strcmp(m_str, _str.m_str) == 0) : 
		(strcasecmp(m_str, _str.m_str) == 0);
}

bool String_t::operator!=(const String_t& _str) const
{
	return s_caseSens ?	
		(strcmp(m_str, _str.m_str) != 0) : 
		(strcasecmp(m_str, _str.m_str) != 0);
}

char& String_t::operator[](unsigned int _index)
{
	unsigned int size = strlen(m_str);
	return _index < size ? m_str[_index]: m_str[size];
}
const char& String_t::operator[](size_t _index) const
{
	size_t size = strlen(this->m_str);
	return (size > _index)? this->m_str[_index] : this->m_str[size];	
}
void* String_t::operatornew(size_t _size)
{
	ceil(log2(_size)) == (log2(_size)) ? 
		SetCapacity(_size) : 
		SetCapacity(_size << 1);
	return new char[GetCapacity()];
}


String_t String_t::operator()(int _start, unsigned int _len) const
{
	char *temp = new char[_len + 1];
	
	if(_start + _len > strlen(m_str))
	{
		return "";
	}
	strncpy(temp, &m_str[0] + _start, _len);
	temp[_len] = '\0';
	String_t res(temp);
	delete[] temp;
	return res; 
}
//##################################################################################################################
//#############################################FUNCTIONS############################################################
//##################################################################################################################

int String_t::Length() const
{
	return strlen(m_str);
}

int String_t::Compare(const String_t& _str) const
{
	int result = 0;
	s_caseSens ? 
		result =  strcmp(m_str, _str.m_str) : 
		result = strcasecmp(m_str, _str.m_str); 
	if(result > 0)
	{
		return 2;
	}
	else if(result < 0)
	{
		return 1;
	}
	return result;
}

void String_t::SetString(const char* _str)
{
	m_str = CreateFrom(_str);
}

char* String_t::CreateFrom(const char* _str)
{
	if(NULL == _str)
	{
		m_str = (char*)operatornew(s_capacity);
		m_str[0] = '\0';
		return m_str;
	}
	else
	{ 	
		if(m_capacity < strlen(_str) + 1)
		{
			if(m_capacity != 0)
			{
				delete[] m_str;
			}
			m_str = (char*)operatornew(strlen(_str) + 1);
		}
		strcpy(m_str, _str);
		return m_str;
	}
}

String_t& String_t::UpperCases()
{
	ConvertSring(toupper);
	return *this;
}
String_t& String_t::LowerCases()
{
	ConvertSring(tolower);
	return *this;
}
String_t& String_t::Prepend(const char* _str)
{
	ExtendString(_str, PRE);
	return *this;
}

String_t& String_t::Prepend(const String_t& _str)
{	
	ExtendString(_str.m_str, PRE);
	return *this;
}

char* String_t::ConvertSring(int(*_f)(int))
{
	int i = 0;
	for(i = 0; m_str[i] !='\0'; ++i)
	{
		m_str[i] = _f(m_str[i]);
	}
	return m_str;
}

char* String_t::ExtendString(const char* _str1, int _flag)
{
	int size = 0;
	char* tmp = NULL;

	size = strlen(_str1);

	tmp = new char[size + strlen(m_str) + 1];
	if(tmp == NULL)
	{
		return m_str;
	}

	if(!_flag)
	{
		strcpy(tmp, _str1);
		strcat(tmp, m_str);
	}
	else 
	{
		strcpy(tmp, m_str);
		strcat(tmp, _str1);
	}

	m_str = CreateFrom(tmp);
	delete[] tmp;
	return m_str;
}

bool String_t::Contains(const String_t& _str) const
{
	return (strstr(m_str, _str.m_str) != NULL);
}

int String_t::PosFirstOcc(char _letter) const
{
	char* tmp;
	tmp = strchr(m_str , _letter);
	return tmp ? tmp - m_str : -1;
}

int  String_t::PosLastOcc(char _letter) const
{
	char* tmp;
	tmp = strrchr(m_str, _letter);
	return tmp ? tmp - m_str: -1;
}


//##################################################################################################################
//############################################STATIC FUNCTIONS######################################################
//##################################################################################################################

bool String_t::SetCaseSens(bool _flag)
{
	bool flag = s_caseSens;
	s_caseSens = _flag ; 
	return flag;
}

unsigned int String_t::SetCapacity(unsigned int _capacity)
{
	unsigned int temp = s_capacity;

	ceil(log2(_capacity)) == (log2(_capacity)) ? 
		(s_capacity = _capacity) : 
		s_capacity =(_capacity << 1);
	return temp;
}

//##################################################################################################################
//#########################################IO OPERATOR##############################################################
//##################################################################################################################

ostream& operator<<(ostream& _os, const String_t& _str)
{
	_os << "String: "<< _str.GetString();
	return _os;
}

istream& operator>>(istream& _is, String_t& _str)
{
	char buff[BUFFER_SIZE];

	_is >> buff;
	_str.SetString(buff);
	return _is;
}

