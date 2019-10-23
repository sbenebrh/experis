#include "ISBN.h"

namespace advcpp
{
ISBN::ISBN(const std::string& isbn)
: m_ISBN(isbn)
{

}   

const std::string& ISBN::GetISBN() const
{
    return m_ISBN;
}

std::ostream& operator<< (std::ostream& os, const ISBN& isbn )
{
    os << isbn.GetISBN();
    return os;
}

bool operator==(const ISBN& a, const ISBN& b)
{
    return a.GetISBN() == b.GetISBN();
}

bool operator<(const ISBN& a , const ISBN& b)
{
    return a.GetISBN() < b.GetISBN();
}

}