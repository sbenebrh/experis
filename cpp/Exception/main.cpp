#include "TException_t.h"
#include<string>
#include <exception>
FILE* OpenFile(const char* filepath)
{
  FILE * file = NULL;

    file = fopen(filepath, "r");
    if (file == NULL)
    {
        throw TException_t<string>(filepath, GETFILE, GETLINE, "");
    }
    return file;   
}
template<class num, class denom, class result>
result divide(const num& a , const  denom& b)
{
    if(b == 0)
    {
        throw TException_t<int>(b, GETFILE, GETLINE, "impossible to devide by 0");
    }
    return a/b;
}


int main()
{
    try
    {
        OpenFile("hello.txt");
    }
    catch(TException_t<string> ex)
    {
        ex.TException_Handler(); 
    }
    catch(TException_t<int> ex1)
    {
        ex1.TException_Handler();
    }
    catch(...)
    {
        cout << "exception"<< endl;
    }

    try
    {
        divide<int, float, int >(10, 9.2);
        divide<int, float, int >(10, 0);

    }
    catch(TException_t<string> ex)
    {
        ex.TException_Handler(); 
    }
    catch(TException_t<int> ex1)
    {
        ex1.TException_Handler();
    }
    catch(...)
    {
        cout << "exception"<< endl;
    }
    
    try
    {
        throw TException_t<char>('\0', GETFILE, GETLINE, "");
    }
    catch(TException_t<string> ex)
    {
        ex.TException_Handler(); 
    }
    catch(TException_t<int> ex1)
    {
        ex1.TException_Handler();
    }
    catch(...)
    {
        cout << "exception"<< endl;
    }

    return 0;
}