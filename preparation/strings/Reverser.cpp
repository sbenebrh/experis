#include "Reverser.h"
#include<cstring>
#include <algorithm>
#include <iostream>

namespace preparation
{

Reverser::Reverser(char*  str)
{
    int size = strlen(str);
    std::cout << size<<std::endl;
    m_str = new char[size + 1];
    strcpy(m_str, str); 
    m_str[size]='\0';
}

char*  Reverser::ReverserIt()
{
    typedef char* Iter;
    Iter first = m_str;
    Iter last = m_str + strlen(m_str) - 1;

    for(; first < last; ++first, ++last)
    {
        char temp = *first;
        *first = *last;
        *last = temp;
    }
    return m_str;
}

}