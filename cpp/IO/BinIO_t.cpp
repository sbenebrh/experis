#include "BinIO_t.h"


BinIO_t::IO_Mode BinIO_t::GetMode() const
{
    return m_mode;
}


BinIO_t& BinIO_t::operator<<(int _value)
{
    CheckReadMode();
    return Write<int>(_value, sizeof(int));
}        

BinIO_t& BinIO_t::operator<<(unsigned int _value)
{
    CheckReadMode();
    return Write<unsigned int>(_value, sizeof(unsigned int));
}

BinIO_t& BinIO_t::operator<<(char _value)
{
    CheckReadMode();
    return Write<char>(_value, sizeof(char));
}

BinIO_t& BinIO_t::operator<<(unsigned char _value)
{
    CheckReadMode();
    return Write<unsigned char>(_value, sizeof(unsigned char));
}

BinIO_t& BinIO_t::operator<<(short _value)
{   
    CheckReadMode();
    return Write<short>(_value, sizeof(short));

}

BinIO_t& BinIO_t::operator<<(unsigned short _value)
{   
    CheckReadMode();
    return Write<unsigned short>(_value, sizeof(unsigned short));

}

BinIO_t& BinIO_t::operator<<(unsigned long _value)
{
    CheckReadMode();
    return Write<unsigned long>(_value, sizeof(unsigned long));   
}

BinIO_t& BinIO_t::operator<<(float _value)
{   
    CheckReadMode();
    return Write<float>(_value, sizeof(float));

}

BinIO_t& BinIO_t::operator<<(long _value)
{
    CheckReadMode();
    return Write<long>(_value, sizeof(long));   
}

BinIO_t& BinIO_t::operator<<(double _value)
{
    CheckReadMode();
    return Write<double>(_value, sizeof(double));   
}

BinIO_t& BinIO_t::operator>>(unsigned int& _value)
{
    CheckWriteMode();
    return Read<unsigned int>(_value, sizeof(unsigned int)); 
}

BinIO_t& BinIO_t::operator>>(int& _value)
{
    CheckWriteMode();
    return Read<int>(_value, sizeof(int));
}

BinIO_t& BinIO_t::operator>>(double& _value)
{
    CheckWriteMode();
    return Read<double>(_value, sizeof(double));
}

BinIO_t& BinIO_t::operator>>(float& _value)
{
    CheckWriteMode();
    return Read<float>(_value, sizeof(float));
}

BinIO_t& BinIO_t::operator>>(long& _value)
{
    CheckWriteMode();
    return Read<long>(_value, sizeof(long));
}

BinIO_t& BinIO_t::operator>>(unsigned long& _value)
{
    CheckWriteMode();
    return Read<unsigned long>(_value, sizeof(unsigned long));
}

BinIO_t& BinIO_t::operator>>(unsigned short& _value)
{
    CheckWriteMode();
    return Read<unsigned short>(_value, sizeof(unsigned short));
}

BinIO_t& BinIO_t::operator>>(short& _value)
{
    CheckWriteMode();
    return Read<short>(_value, sizeof(short));
}

BinIO_t& BinIO_t::operator>>(unsigned char& _value)
{
    CheckWriteMode();
    return Read<unsigned char>(_value, sizeof(unsigned char));
}

BinIO_t& BinIO_t::operator>>(char& _value)
{
    CheckWriteMode();
    return Read<char>(_value, sizeof(char));
}

BinIO_t& BinIO_t::operator<<(const void* _buff)
{
    CheckReadMode();
    m_buff = (void*)_buff;
    m_mode = WRITER;
    return *this;
}

BinIO_t& BinIO_t::operator>>(void* _buff)
{
    CheckReadMode();
    m_buff = _buff;
    m_mode = READER;
    return *this;
}

void BinIO_t::operator,(size_t _size)
{
    m_mode == READER ? Read<char>(*(char*)m_buff, _size): Write<char>(*(char*)m_buff, _size); 
}