#ifndef NON_COPYABLE_H
#define NON_COPYABLE_H

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