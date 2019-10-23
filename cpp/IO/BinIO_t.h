#ifndef __BINIO_T_H__
#define __BINIO_T_H__
#include <string>

#include "VirtIO_t.h"
#include <cstdio>
class BinIO_t:public VirtIO_t
{
public:
enum IO_Mode
{
    READER, 
    WRITER
};
    BinIO_t() { m_buff = NULL;}
    BinIO_t(string _path, string _mode): VirtIO_t(_path, _mode), m_mode(GetMode()), m_buff(NULL) {}

    virtual BinIO_t& operator<<(int _value)           ;
    virtual BinIO_t& operator<<(unsigned int _value)  ;
    virtual BinIO_t& operator<<(char _value)          ;
    virtual BinIO_t& operator<<(unsigned char _value) ;
    virtual BinIO_t& operator<<(short _value)         ; 
    virtual BinIO_t& operator<<(unsigned short _value); 
    virtual BinIO_t& operator<<(long _value)          ;
    virtual BinIO_t& operator<<(unsigned long _value) ; 
    virtual BinIO_t& operator<<(float _value)         ;
    virtual BinIO_t& operator<<(double _value)        ;
     
    virtual BinIO_t& operator>>(int& _value)          ; 
    virtual BinIO_t& operator>>(unsigned int& _value) ; 
    virtual BinIO_t& operator>>(double& _value)       ;    
    virtual BinIO_t& operator>>(float& _value)        ;
    virtual BinIO_t& operator>>(long& _value)         ;
    virtual BinIO_t& operator>>(unsigned long& _value);
    virtual BinIO_t& operator>>(short& _value)        ;
    virtual BinIO_t& operator>>(unsigned short& _value);
    virtual BinIO_t& operator>>(char& _value)         ;
    virtual BinIO_t& operator>>(unsigned char& _value);

            void operator,(size_t _size);
            BinIO_t& operator<<(const void* _buff);
            BinIO_t& operator>>(void* _buff);
protected:
    IO_Mode GetMode() const;
    void    SetMode(IO_Mode _mode) {m_mode = _mode;}

    template<class T>
    BinIO_t& Write(const T& _value, long unsigned int _size);
    template<class T>
    BinIO_t& Read(T& _value, long unsigned int _size);


private:
    void* m_buff;
    IO_Mode m_mode;

    BinIO_t(const BinIO_t& _binIO);
    BinIO_t& operator=(const BinIO_t& _binIO);
    
};

template<class T>
BinIO_t& BinIO_t::Write(const T& _value, long unsigned int _size)
{
    if(fwrite(&_value, _size, 1, GetFILE())!= 1)
    {
        throw string("impossible to write/read");
    }
    
    return *this;
}

template<class T>
BinIO_t& BinIO_t::Read( T& _value, long unsigned int _size)
{
    if(fread(&_value, _size, 1, GetFILE())!= 1)
    {
        throw string("impossible to write/read");
    }
    
    return *this;
}





#endif //__BINIO_T_H__