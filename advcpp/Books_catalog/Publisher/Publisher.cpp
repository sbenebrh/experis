#include "Publisher.h"

namespace advcpp
{

Publisher::Publisher(const std::string& name)
: Owner(name)
{

}

std::ostream& operator<<(std::ostream& os, const Publisher& publisher)
{
    os << publisher.GetName();
    return os;
}

bool operator==(const Publisher& a, const Publisher& b)
{
    return a.GetName() == b.GetName();
}

}