#ifndef __ASCII_IO_T_H__
#define __ASCII_IO_T_H__

#include <string>
#include <cstdio>
#include "VirtIO_t.h"
class AsciiIO_t:public VirtIO_t
{
public:
    AsciiIO_t():VirtIO_t()                                                      {}
    AsciiIO_t(const string& _path, const string _mode ):VirtIO_t(_path, _mode)  {}
//          virtual                 ~AsciiIO_t(){};
//TODO:not VirtIO_t but ASCIIIO_t
    virtual AsciiIO_t&       operator<<(int _value) ;
    virtual AsciiIO_t&       operator<<(unsigned int _value) ;
    virtual AsciiIO_t&       operator<<(char _value) ;
    virtual AsciiIO_t&       operator<<(unsigned char _value) ;
    virtual AsciiIO_t&       operator<<(short _value) ; 
    virtual AsciiIO_t&       operator<<(unsigned short _value); 
    virtual AsciiIO_t&       operator<<(long _value)  ;
    virtual AsciiIO_t&       operator<<(unsigned long _value); 
    virtual AsciiIO_t&       operator<<(float _value) ;
    virtual AsciiIO_t&       operator<<(double _value) ;

    virtual AsciiIO_t&       operator>>(int& _pvalue)  ;  
    virtual AsciiIO_t&       operator>>(unsigned int& _pvalue)  ; 
    virtual AsciiIO_t&       operator>>(double& _pvalue)  ;  
    virtual AsciiIO_t&       operator>>(float& _pvalue)  ;   
    virtual AsciiIO_t&       operator>>(long& _value)        ;
    virtual AsciiIO_t&       operator>>(unsigned long& _value);
    virtual AsciiIO_t&       operator>>(short& _value)        ;
    virtual AsciiIO_t&       operator>>(unsigned short& _value);
    virtual AsciiIO_t&       operator>>(char& _value)        ;
    virtual AsciiIO_t&       operator>>(unsigned char& _value);
    
protected:
                  template<class T>
                  void            WriteOnFile( T& _value,  const string& _str, int (*func)(FILE*,const  char*, ...));


private:
    AsciiIO_t(const AsciiIO_t&);
    AsciiIO_t operator=(const AsciiIO_t&);
};


template<class T>
void AsciiIO_t::WriteOnFile( T& _value,const string& _str,int (*func)(FILE*, const char*, ...))
{
   
    if(func == fscanf)
    {
        if(func(GetFILE(), _str.c_str(), &_value) == EOF)
        {
            SetStatus(readErr_e);
            throw string("impossible to read");
        }
    }
    else
    {
        if(func(GetFILE(), _str.c_str(), _value) < 0)
        {
            SetStatus(writeErr_e);
            throw string("impossible to write");
        }
        fflush(GetFILE());
    }
}


#endif // __ASCII_IO_T_H__