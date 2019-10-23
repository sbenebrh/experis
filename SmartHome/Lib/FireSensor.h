#ifndef FIRE_SENSOR_H
#define FIRE_SENSOR_H


#include "CommonSensor.h"
#include "IAgent.h"
#include"Thread.h"

#include <vector>

namespace smartHome
{

class Task;

class FireSensor:public IAgent
{
public:
    FireSensor(const std::string& , const std::string&,const std::string&, shared_ptr<Location> pLocation);
    ~FireSensor();

private:
    virtual bool init(shared_ptr<ISubscribe> , shared_ptr<IEnQ>,shared_ptr<LiveLogger> ) ;
    void Stop();
    virtual bool IsSensor() ;
    virtual bool IsControler() ;
    
private:
    shared_ptr<CommonSensor> m_common;
    shared_ptr<IEnQ> m_enQ; 
    shared_ptr<Task> m_pTask;
    std::vector<shared_ptr<advcpp::Thread> > m_threads;
    std::string m_Log;
    shared_ptr<LiveLogger> m_pLog;
};
}

#endif
