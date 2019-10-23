#include "CondVariable.h"

#include <iostream>
#include <cassert>

#include "Mutex.h"
#include "CreationFailureException.h"

namespace advcpp
{

CondVariableException::CondVariableException(int errornumber)
{
    std::cerr << strerror(errornumber) << __FILE__ << " " << __LINE__ << std::endl;
}

CondVariable::CondVariable() throw (CondVariableException)
{
    int result = 0;
    if((result = pthread_cond_init(& m_id, 0))!= 0)
    {
        throw CondVariableException(result);
    }
}

CondVariable::~CondVariable() NOEXCEPT
{
    if(pthread_cond_destroy(&m_id))
    {
        assert(false );
    }
}




void CondVariable::CondSignal() throw (CondVariableException)
{
    int result = 0;
    if((result = pthread_cond_signal(& m_id))!= 0)
    {
        throw CondVariableException(result);
    }
}

void CondVariable::CondBroadcast() throw (CondVariableException)
{
    int result = 0;
    if((result = pthread_cond_broadcast(& m_id))!= 0)
    {
        throw CondVariableException(result);
    }
}


}