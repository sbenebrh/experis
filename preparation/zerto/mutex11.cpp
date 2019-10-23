#include <mutex>
#include <thread>
#include <unistd.h>
#include <iostream>

namespace preparation
{

class TestMutex
{
public:
    TestMutex(int x)
    : m_x(x)
    {

    }

    void CriticalSection()
    {
        mux.lock();
        sleep(2);
        ++m_x;
        std::cout<< m_x <<std::endl; 
        mux.unlock();
    }
    
    ~TestMutex()
    {
        std::cout << "Destroy" << std::endl;
    }

private:
    std::mutex mux;
    int m_x;

};

class ThreadMutex
{
public:
    ThreadMutex(preparation::TestMutex& a)
    :m_mux(a)
    {

    }
    void operator()(int x)
    {
        std::cout <<"Thread Create " << x<<  std::endl;
        m_mux.CriticalSection();
    }

private:
    preparation::TestMutex& m_mux;
};

}


void foo(preparation::TestMutex& t)
{
    std::cout <<"Thread Create" << std::endl;
    t.CriticalSection();
}

int main()
{
    preparation::TestMutex a(10);
    preparation::TestMutex& b(a);
    std::thread c(preparation::ThreadMutex(a) ,10);
    std::thread d(preparation::ThreadMutex(a), 11);
    c.join();
    d.join();


}