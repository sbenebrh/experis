#ifndef NONCOPYABLE_H
#define NONCOPYABLE_H

namespace advcpp
{

class NonCopyable
{
public:
    NonCopyable(){}
private:
    NonCopyable(const NonCopyable& );
    NonCopyable& operator=(const NonCopyable&);
};

} // advcpp

#endif