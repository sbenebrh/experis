#ifndef PUBLISHER_H
#define PUBLISHER_H

#include <string>
#include <vector>
#include <tr1/memory>

#include "owner.h"

namespace advcpp
{
    


class Publisher:public Owner
{
public:
    Publisher(const std::string& name);
    
};

bool operator==(const Publisher& a, const Publisher & b);
std::ostream& operator<<(std::ostream& os, const Publisher& Publisher);

}



#endif
