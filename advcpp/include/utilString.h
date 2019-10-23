#ifndef UTILSTRING_H
#define UTILSTRING_H

#include <cstring>
#include <cwchar>
#include <cctype>
#include <cstdio>
#include <cwctype>
#include "Buffer.h"
namespace advcpp
{

template<typename T>
class UtilString
{
public:
    typedef T const * Iter; 
    static size_t Getlength(const T* str);
    static T Toupper(T& letter) ;
    static int Compare(const Iter a,const Iter b );

};


template<>
size_t UtilString<char>::Getlength(const char* str)
{
    return strlen(str);
}

template<>
size_t UtilString<wchar_t>::Getlength(const wchar_t* str)
{
    return wcslen(str);
}

template<>
char  UtilString<char>::Toupper(char& letter) 
{
    return toupper(letter);
}

template<>
wchar_t  UtilString<wchar_t>::Toupper(wchar_t& letter) 
{
    return towupper(letter);
}

template<>
int UtilString<char>::Compare(const UtilString<char>::Iter a,const UtilString<char>::Iter b )
{
    return strcmp(a,b);
}

template<>
int UtilString<wchar_t>::Compare(const UtilString<wchar_t>::Iter a,const UtilString<wchar_t>::Iter b )
{
    return wcscmp(a, b);
}

}


#endif
