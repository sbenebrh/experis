#include "SmokeSensor.h"


#include <unistd.h>

#include "SmokeEvent.h"
#include "IEnQ.h"
#include "Thread.h"
#include "LiveLogger.h"


namespace smartHome
{

class Task:public advcpp::IRunnable
{
public:
    Task(shared_ptr<Location> pLocation, shared_ptr<IEnQ> penQ, shared_ptr<LiveLogger> pLog, const std::string& Logpath) NOEXCEPT;
    ~Task();

    virtual void run() ;

    void SetOff();
private:
    void sendEvent() const NOEXCEPT;
private:
    shared_ptr<Location> m_pLocation;
    shared_ptr<IEnQ> m_penQ;
    bool m_IsON;
    shared_ptr<LiveLogger> m_pLog;
    std::string m_Log;
};

SmokeSensor::SmokeSensor(const std::string& name, const std::string& type,const std::string& log, shared_ptr<Location> pLocation)
: m_common(new CommonSensor( name ,type, pLocation))
, m_Log(log)
{

}

SmokeSensor::~SmokeSensor()
{
    std::vector<shared_ptr<advcpp::Thread> >::iterator it  = 
                                        m_threads.begin();
                                        
    for(size_t i = 0 ; it != m_threads.end(); ++it, ++i)
    {
        dynamic_cast<Task* >(m_pTask.get()) -> SetOff();
        m_threads[i] -> Join();
    }
}

bool SmokeSensor::init(shared_ptr<ISubscribe> pSub , shared_ptr<IEnQ> penQ,shared_ptr<LiveLogger> logger)
{
    m_enQ = penQ;
    m_pLog = logger;
    (void)pSub;

    try
    {
        m_pTask = shared_ptr<Task>(new Task(m_common -> location(),penQ, m_pLog, m_Log));
        shared_ptr<advcpp::Thread> t(new advcpp::Thread(m_pTask));
        m_threads.push_back(t);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
      
    return true;
}

void SmokeSensor::Stop()
{
    m_pTask -> SetOff();
}


Task::Task(shared_ptr<Location> pLocation, shared_ptr<IEnQ> penQ, shared_ptr<LiveLogger> pLog, const std::string& Logpath) NOEXCEPT
: m_pLocation(pLocation)
, m_penQ(penQ)
, m_IsON(true)
, m_pLog(pLog)
, m_Log(Logpath)
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
        int time = rand() % 10 + 1;
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
        std::string info= "new Smoke event is created";
        m_pLog -> Write(m_Log,  info + asctime(curtime) );
        shared_ptr<SmokeEvent> event(new SmokeEvent(m_pLocation, asctime(curtime)));
        m_penQ -> enQ(event);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
}

bool SmokeSensor::IsSensor() 
{
    return true;
}
bool SmokeSensor::IsControler()
{
    return false;
}

extern "C" shared_ptr<IAgent> Maker(const std::string& name, const std::string& type,const std::string& Log, shared_ptr<Location> pLocation )
{
    shared_ptr<IAgent> pAgent;
    try
    {
       pAgent = shared_ptr<IAgent>(new SmokeSensor(name, type, Log,pLocation));
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    return pAgent;
}



}