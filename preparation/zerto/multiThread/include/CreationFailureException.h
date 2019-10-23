#ifndef CREATION_FAILURE_EXCEPTION_H
#define CREATION_FAILURE_EXCEPTION_H

#include <exception>
#include <iostream>
#include <cstring>

namespace advcpp
{

class CreationFailureException: public std::exception
{
public:
    CreationFailureException(int ernoError){std::cerr << strerror(ernoError)<< std::endl;}
};

}


#endif