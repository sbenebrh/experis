#ifndef SERIALPUB_H
#define SERIALPUB_H


#include "CommonRefs.h"
#include "IpubImpl.h"

namespace smartHome
{

class SerialPub:public IpubImpl
{
public:
    virtual void pub(shared_ptr<Event> pEvent, Iter beg, Iter end) NOEXCEPT;
};
}


#endif