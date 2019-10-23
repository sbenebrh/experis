#include "Consumer.h"
#include "Thread.h"

namespace advcpp
{

Consumer::Consumer(int start, int end)
: m_start(start)
, m_end(end)
, m_result(0)
{

}

Consumer::~Consumer()
{

}

void Consumer::run()
{
    m_result = 0;

    for(int i = m_start; i <= m_end; ++i)
    {
        m_result++;
    }
    Thread::Sleep(1000000);
    return ;
}

int Consumer::Result()
{
    return m_result;
}

}