#ifndef ISBN_H
#define ISBN_H

#include <iostream>
#include <cstddef>

#include "NonCopyable.h"

namespace advcpp
{

class ISBN 
{
public:
    ISBN(const std::string& isbn);
    const std::string & GetISBN() const ;

private:
    std::string m_ISBN;
};
bool operator==(const ISBN& a, const ISBN& b);
bool operator<(const ISBN& a , const ISBN& b);
std::ostream& operator<< (std::ostream& os, const ISBN& isbn );
}

#endif