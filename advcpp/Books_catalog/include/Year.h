#ifndef YEAR_H
#define YEAR_H

#include <cstddef>
#include <iostream>

namespace advcpp
{

class Year
{
public:
    Year(size_t year);
    size_t year() const;
private:
    size_t m_year;
};

bool operator==(const Year& a, const Year& b);
bool operator<(const Year& a, const Year& b);
std::ostream& operator<<(std::ostream& os, const Year& year);

} // advcpp


#endif