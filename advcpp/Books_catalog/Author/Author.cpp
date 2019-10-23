#include "Author.h"

namespace advcpp
{

Author::Author(const std::string& name)
: Owner(name)
{

}

std::ostream& operator<<(std::ostream& os, const Author& Author)
{
    os << Author.GetName();
    return os;
}

bool operator==(const Author& a, const Author& b)
{
    return a.GetName() == b.GetName();
}

}