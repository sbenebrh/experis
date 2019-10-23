#ifndef IRUNNABLE_H
#define IRUNNABLE_H

namespace advcpp
{
class IRunnable
{
public:
    virtual void run() = 0;
    virtual ~IRunnable(){};
};

}

#endif