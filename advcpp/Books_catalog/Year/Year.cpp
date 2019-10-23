#include "Year.h"
#include "ctime"

namespace advcpp
{
    
Year::Year(size_t year)
: m_year(year)
{
    try
    {
        time_t t = time(NULL);
        tm* timePtr = localtime(&t);
        if(m_year == 0 || m_year > size_t(timePtr -> tm_year + 1900))
        {
            throw std::out_of_range("the date is incorrect");
        }
    }
    catch(const std::out_of_range& e)
    {
        m_year = 0;
    }
    
    
}

size_t Year::year() const 
{
    return m_year;
}

bool operator==(const Year& a, const Year& b)
{
    return a.year() == b.year();
}

std::ostream& operator<<(std::ostream& os, const Year& year)
{
    os << year.year(); 
    return os;
}

bool operator<(const Year& a, const Year& b)
{
    return a.year() < b.year();
}
} // advcpp
