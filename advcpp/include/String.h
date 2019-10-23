#ifndef STRING_H
#define STRING_H

#include "utilString.h"
#include "Buffer.h"
#include<string>
#include<iostream> 
namespace advcpp{

template<typename T>
class String;

template< typename T>
bool operator == (const String<T>& a, const String<T>& b);
template< typename T>
bool operator== (const String<T>& a, const T* b );
template<typename T>
String<T> ToUpper(const String<T>&   str);
template<typename T>
String<T> operator+(const String<T> & a, const String<T> & b);
template<typename T>
bool operator<(const String<T> & a, const String<T>& b);
template<typename T>

class String
{
    friend bool operator==<T>(const String<T>& a, const String<T>& b);
    friend String<T> ToUpper<T>(const String<T>&  str);
    friend bool operator< <T>(const String<T> & a, const String<T>& b);
    friend bool operator== <T>(const String<T>& a, const T* b );

public:
    typedef T Type_value;
    String(const Type_value* str = "");

    size_t Size() const;

    String& operator+=(const String& _str);
    String& operator+=(const Type_value* _str);

    const Type_value& operator[](size_t _index) const;
    Type_value& operator[](size_t _index);

    operator std::string ();

private:
    size_t m_size; 
    Buffer<Type_value> m_buff;
};
template< typename T>
bool operator == (const String<T>& a, const String<T>& b);
template< typename T>
bool operator == (const String<T>& a, const T* b);
template< typename T>
bool operator == (const T* a, const String<T>& b);

template<typename T>
String<T> ToUpper(const String<T>&   str);

template<typename T>
String<T> operator+(const String<T> & a, const String<T> & b);
template<typename T>
String<T> operator+(const String<T> & a, const T* & b);

template<typename T>
bool operator<(const String<T> & a, const String<T>& b);





template<typename U>
class Fill
{
    size_t i;
    Buffer<U>& m_buff;
    const U* m_str;
public:
    Fill(Buffer<U>& buff, const  U* str)
    : i(0)
    , m_buff(buff)
    , m_str(str)
    {
        
    }
    void operator()(U& obj)
    {
        m_buff.Put(m_str[i], i);
        ++i;
    }

};

template<typename T>
String<T>::String(const Type_value* str )
: m_size(UtilString<T>::Getlength(str))
, m_buff(m_size + 1)
{
    typename Buffer<T>::Iter it = m_buff.Begin();
    typename Buffer<T>::Iter end = m_buff.End();
    std::for_each(it, end, Fill<T>(m_buff, str));    
}

template <typename T>
size_t String<T>::Size() const
{
    return m_size;
}

template <typename T>
String<T>& String<T>::operator+=(const String& str)
{
    if(m_size + str.m_size  + 1> m_buff.Capacity())
    {
        m_buff.Grow(str.m_size);
    }

    size_t newSize = m_size + str.m_size + 1;
    for(size_t i = m_size ; i < newSize ; ++i)
    {
        m_buff.Put(str.m_buff[i - m_size], i);
    }
    m_size = newSize - 1;

    return *this;
}

template <typename T>
String<T>& String<T>::operator+=(const T* str)
{
    String<T> temp(str);
    return String<T>::operator+= (temp);
}

template<typename T>
const T & String<T>::operator[](size_t index) const
{
    return m_buff[index];
}

template<typename T>
T & String<T>::operator[](size_t index)
{
    return m_buff[index];
}

template <typename T>
bool operator== (const String<T>& a, const String<T>& b )
{
    return UtilString<T>::Compare(a.m_buff.Begin(), b.m_buff.Begin()) == 0;
}

template <typename T>
bool operator== (const String<T>& a, const T* b )
{
    return UtilString<T>::Compare(a.m_buff.Begin(), b) == 0;
}

template <typename T>
bool operator!= (const String<T>& a, const String<T>& b )
{
    return !(a == b);
}

template<typename T>
String<T> ToUpper(const String<T>&   str)

{   
    String<T> temp(str);
    std::for_each(temp.m_buff.Begin(), temp.m_buff.End(), UtilString<T>::Toupper);
    return str;

}

template<typename T>
String<T> operator+(const String<T> & a, const String<T> & b)
{
    String<T> temp = a;
    temp+= b;
    return temp;
}

template<typename T>
String<T> operator+(const String<T>& a, const T*  b)
{
    String<T> temp = a;
    temp+= b;
    return temp;
}

template<typename T>
bool operator<(const String<T> & a, const String<T>& b)
{
    return UtilString<T>::Compare(a.m_buff.Begin(), b.m_buff.Begin()) < 0 ;
}

std::ostream& operator<<(std::ostream& os, const String<char> & str)
{
    int i = 0;
    while(str[i]!= char(0))
    {
        os << str[i];
        ++i;
    }
    return os;
}

std::wostream& operator<<(std::wostream& os, const String<wchar_t> & str)
{
    int i = 0;
    while(str[i]!= wchar_t(0))
    {
        os << str[i];
        ++i;
    }
    return os;
}

template<typename T>
String<T>::operator std::string ()
{
    return string(m_buff.Begin());
}

}




#endif // STRING_H
