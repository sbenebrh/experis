#ifndef AUTHOR_H
#define AUTHOR_H

#include "owner.h"
namespace advcpp {

class Author:public Owner
{
public:
    Author(const std::string& name);
};
bool operator==(const Author& a, const Author& b);
std::ostream& operator<<(std::ostream& os, const Author& author);
}

#endif