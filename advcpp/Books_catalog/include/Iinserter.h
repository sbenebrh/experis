#ifndef IINSERTER_H
#define IINSERTER_H

#include <cstddef>
#include <string>

#include "BookDetails.h"

namespace advcpp
{
    
class Iinserter
{
public:
    virtual void insert(const BookDetails& bd) = 0;
};

}

#endif
