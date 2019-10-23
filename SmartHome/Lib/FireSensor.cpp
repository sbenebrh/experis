#include "FireSensor.h"

#include <unistd.h>
#include <cassert>
#include <iostream>

#include "FireEvent.h"
#include "IEnQ.h"
#include "Thread.h"


namespace smartHome
{

class Task:public advcpp::IRunnable
{
public:
    Task(shared_ptr<Location> pLocation, shared_ptr<IEnQ> penQ) NOEXCEPT;
    ~Task();

    virtual void run() ;

    void SetOff();
private:
    void sendEvent() const NOEXCEPT;
private:
    shared_ptr<Location> m_pLocation;
    shared_ptr<IEnQ> m_penQ;
    bool m_IsON;
};

FireSensor::FireSensor(const std::string& name, const std::string& type, const std::string& Log,shared_ptr<Location> pLocation)
: m_common(new CommonSensor( name ,type, pLocation))
, m_Log(Log)
{

}
FireSensor::~FireSensor()
{
    std::vector<shared_ptr<advcpp::Thread> >::iterator it  = 
                                        m_threads.begin();
                                        
    for(size_t i = 0 ; it != m_threads.end(); ++it, ++i)
    {
        dynamic_cast<Task* >(m_pTask.get()) -> SetOff();
        m_threads[i] -> Join();
    }
}

bool FireSensor::init(shared_ptr<ISubscribe> pSub , shared_ptr<IEnQ> penQ,shared_ptr<LiveLogger> log)
{
    m_enQ = penQ;
    m_pLog = log;
    (void)pSub;

    try
    {
        m_pTask = shared_ptr<Task>(new Task(m_common -> location(),penQ));
        shared_ptr<advcpp::Thread> t(new advcpp::Thread(m_pTask));
        m_threads.push_back(t);
    }
    catch(const std::exception& e)
    {
        
    }
      
    return true;
}
Task::Task(shared_ptr<Location> pLocation, shared_ptr<IEnQ> penQ) NOEXCEPT
: m_pLocation(pLocation)
, m_penQ(penQ)
, m_IsON(true)
{

}

Task:: ~Task()
{
    
}

void Task::SetOff()
{
    m_IsON = false;
}

void Task::run()
{

    while(1)
    { 
        srand (static_cast<unsigned int>(time(0)));
        int time = rand() % 20 + 1;
        sleep(time);
        sendEvent();
        if(!m_IsON)
        {
            break;
        }
    }
    
}


void Task::sendEvent() const NOEXCEPT
{
    try
    {
        time_t _tm = time(0);
        struct tm * curtime = localtime(&_tm);
        shared_ptr<FireEvent> event(new FireEvent(m_pLocation,asctime(curtime)));
        m_penQ -> enQ(event);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
}

void FireSensor::Stop()
{
    m_pTask -> SetOff();
}

bool FireSensor::IsSensor() 
{
    return true;
}
bool FireSensor::IsControler()
{
    return false;
}

extern "C" shared_ptr<IAgent> Maker(const std::string& name, const std::string& type, const std::string& log, shared_ptr<Location> pLocation )
{
    try
    {
        shared_ptr<IAgent> pAgent(new FireSensor(name, type, log,pLocation));
        return pAgent; 
    }
    catch(const std::exception& e)
    {
        assert(false and " error in allocation into firecontrolerMAker");
    } 
}


}