#include <iostream>
#include <tr1/memory>
#include <fstream>

#include "logger.h"

int main()
{
    std::ifstream is("hello.txt");
    
    std::tr1::shared_ptr<preparation::Logger> log(preparation::Logger::GetInstance(is));
    std::tr1::shared_ptr<preparation::Logger> log1(preparation::Logger::GetInstance(is));

    std::cout << ( log1.get() == log.get());

}