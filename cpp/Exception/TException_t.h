#ifndef __EXCEPTION_T_H__
#define __EXCEPTION_T_H__

#include <string>
#include <stddef.h>

#include <iostream>

using namespace std;

#define GETLINE __LINE__
#define GETFILE __FILE__



template<class T>
class TException_t
{
//TODO get functions
public:
    TException_t(T _exception, string _file , size_t _line, string _context = "" ): m_exception(_exception), m_file(_file), m_line(_line), m_context(_context) {}
    virtual ~TException_t() {};
    void TException_Handler() const;
    const T& GetException() const {return m_exception;}
    
private:
    T m_exception;
    string m_file;
    size_t m_line;
    string m_context;
};

template<class T>
void TException_t<T>:: TException_Handler() const
{
    cout << "*********************************************" << endl;
    if(typeid(*this).name() == typeid(TException_t<int>).name())
    {
        cout << "arithmetic exception" << endl;
    }
    if(typeid(*this).name() == typeid(TException_t<string>).name())
    {
        cout << "file name error" << endl;
        cout << m_exception << endl;
    }
    cout << "the file is :" << m_file << endl;
    cout << "the line is : "<< m_line << endl;
    if (m_context.empty())
    {
       return ; 
    }
    cout << m_context<< endl;

    cout << "*********************************************" << endl;

}

#endif // __EXCEPTION_T_H__
