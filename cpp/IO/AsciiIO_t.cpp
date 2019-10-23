#include "AsciiIO_t.h"
#include <iostream>
using namespace std;




AsciiIO_t& AsciiIO_t::operator<<(int _value) 
{
    CheckWriteMode();
    AsciiIO_t::WriteOnFile<int>(_value, "%d",fprintf);
    
    return *this;
}

AsciiIO_t& AsciiIO_t::operator<<(unsigned int _value)
{
    CheckWriteMode();
    AsciiIO_t::WriteOnFile<unsigned int>(_value, "%ud",fprintf);
    
    return *this;
}

AsciiIO_t& AsciiIO_t::operator<<(char _value)
{
    CheckWriteMode();
    AsciiIO_t::WriteOnFile<char>(_value, "%c",fprintf);
    
    return *this;
}

AsciiIO_t& AsciiIO_t::operator<<(unsigned char _value)
{
    CheckWriteMode();
    AsciiIO_t::WriteOnFile<unsigned char>(_value, "%c",fprintf);
    
    return *this;
}

AsciiIO_t& AsciiIO_t::operator<<(short _value)
{
    CheckWriteMode();
    AsciiIO_t::WriteOnFile<short>(_value, "%h",fprintf);
    
    return *this;
}

AsciiIO_t& AsciiIO_t::operator<<(unsigned short _value)
{
    CheckWriteMode();
    AsciiIO_t::WriteOnFile<unsigned short>(_value,"%hu", fprintf);
    
    return *this;
}

AsciiIO_t& AsciiIO_t::operator<<(long _value)
{
    CheckWriteMode();
    AsciiIO_t::WriteOnFile<long>(_value, "%l",fprintf);
    
    return *this;
}

AsciiIO_t& AsciiIO_t::operator<<(unsigned long _value)
{
    CheckWriteMode();
    AsciiIO_t::WriteOnFile<unsigned long>(_value, "%ul",fprintf);
    
    return *this;
}

AsciiIO_t& AsciiIO_t::operator<<(float _value)
{
    CheckWriteMode();
    AsciiIO_t::WriteOnFile<float>(_value, "%f", fprintf);
    
    return *this;
}

AsciiIO_t& AsciiIO_t::operator<<(double _value)
{
    CheckWriteMode();
    AsciiIO_t::WriteOnFile<double>(_value,"%f", fprintf);
    
    return *this;
}

AsciiIO_t&  AsciiIO_t::operator>>(int& _pvalue)  
{
   CheckReadMode(); 

   AsciiIO_t::WriteOnFile<int>(_pvalue, "%d",fscanf);

   return *this;
}

AsciiIO_t&  AsciiIO_t::operator>>(unsigned int& _pvalue)  
{
   CheckReadMode(); 

   AsciiIO_t::WriteOnFile<unsigned int>(_pvalue, "%ud",fscanf);

   return *this;
}

AsciiIO_t& AsciiIO_t::operator>>(double& _value)
{
    CheckReadMode();
    AsciiIO_t::WriteOnFile<double>(_value,"%f", fprintf);
    
    return *this;
}

AsciiIO_t& AsciiIO_t::operator>>(float& _value)
{
    CheckReadMode();
    AsciiIO_t::WriteOnFile<float>(_value, "%f",fprintf);
    
    return *this;
}

AsciiIO_t&   AsciiIO_t::operator>>(long& _value) 
{   
    CheckReadMode();
    AsciiIO_t::WriteOnFile<long>(_value, "%l", fprintf);
    return *this;
}

AsciiIO_t&      AsciiIO_t:: operator>>(unsigned long& _value)
{
    CheckReadMode();
    AsciiIO_t::WriteOnFile<unsigned long>(_value, "%ul", fprintf);
    return *this;
}

AsciiIO_t&   AsciiIO_t::operator>>(short& _value) 
{   
    CheckReadMode();
    AsciiIO_t::WriteOnFile<short>(_value, "%h", fprintf);
    return *this;
}

AsciiIO_t&      AsciiIO_t:: operator>>(unsigned short& _value)
{
    CheckReadMode();
    AsciiIO_t::WriteOnFile<unsigned short>(_value, "%hu", fprintf);
    return *this;
}

AsciiIO_t&   AsciiIO_t::operator>>(char& _value) 
{   
    CheckReadMode();
    AsciiIO_t::WriteOnFile<char>(_value, "%h", fprintf);
    return *this;
}

AsciiIO_t&      AsciiIO_t:: operator>>(unsigned char& _value)
{
    CheckReadMode();
    AsciiIO_t::WriteOnFile<unsigned char>(_value, "%hu", fprintf);
    return *this;
}
