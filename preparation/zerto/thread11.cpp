
#include <iostream>
#include <thread>

namespace preparation
{

class Thread
    {
        public:
            void operator()(int x)
            {
                for(int i = 0; i < x ;++i)
                {
                    std::cout << i << " ";
                }
                std::cout <<std::endl;
            }
    };
    
class Threadtest
{
public:
    Threadtest(int x)
    :m_x(x)
    {
       
    }
    
    void CreateThread() 
    {
        m_th1 = std::thread(Thread(),m_x);
    }

    ~Threadtest()
    {
        m_th1.join();
    }

private:
    

private:
    int m_x;
    std::thread m_th1;
};
} // namespace preparation


int main()
{
    preparation::Threadtest a(7);
    a.CreateThread();
    preparation::Threadtest b(9);
    b.CreateThread();
    //std::thread th1(preparation::Thread(), 1000);
    //std::thread th2(preparation::Thread(), 200);
   // th1.join();
   // th2.join();
    return 0;
}

