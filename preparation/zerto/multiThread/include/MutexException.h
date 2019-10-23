#ifndef MUTEX_EXCEPTION_H
#define MUTEX_EXCEPTION_H

#include <stdexcept>
#include <cstring>
#include <iostream>



namespace advcpp
{

class MutexException: public std::exception
{

public:
    MutexException(int errornum){std::cerr<< strerror(errornum);}

};
}

#endif 
