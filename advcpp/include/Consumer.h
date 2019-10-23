#ifndef CONSUMER_H
#define CONSUMER_H

#include "IRunnable.h"

namespace advcpp
{

class Consumer:public IRunnable
{
public:
    Consumer(int start, int end);
    ~Consumer();
    
    virtual void run();
    int Result();

private:
    int m_start;
    int m_end;
    int m_result;
};

}


#endif