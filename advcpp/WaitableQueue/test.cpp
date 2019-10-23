#include "WaitableQueue.h"
#include "mu_test.h"

#include <iostream>
#include <tr1/memory>
#include <vector>

#include "IRunnable.h"
#include "Thread.h"


class Cat{
public:
friend bool operator<(const Cat& a, const Cat& b);
	Cat() { ++n;m_id = id; ++id;}
	Cat(Cat const& cat) {++n;++c; m_id = cat.m_id; }
	Cat& operator=(Cat const& cat) {++g;  m_id = cat.m_id; return *this;}
    bool operator==(const Cat& cat){ return m_id == cat.m_id;}
    friend std::ostream& operator<<(std::ostream& os, const Cat& cat);
    
	~Cat() {--n;}
    static int id ;
	static int n;
	static int c;
    static int g;
    size_t m_id;
};
int Cat::g = 0;
int Cat::n = 0;
int Cat::c = 0;
int Cat::id = 0;
using std::tr1::shared_ptr;


template<typename T>
class Consumer:public advcpp::IRunnable
{
public:

    typedef typename std::tr1::shared_ptr<advcpp::WaitableQueue<shared_ptr<T> > > pWQ;
    Consumer(size_t N, pWQ pqueue)
    :loopNumber(N)
    , m_queue(pqueue)
    {}
    virtual void run()
    {    
        for(size_t i = 0; i < loopNumber; ++i)
        {
            resultQueue.push(m_queue -> Dequeue());
        }
    }

    std::queue<shared_ptr<T > > Result(){return resultQueue;}


private:
    size_t loopNumber;
    pWQ m_queue;
    std::queue<shared_ptr<T > > resultQueue;
};

template<typename T>
class Producer:public advcpp::IRunnable
{
public:
    typedef typename std::tr1::shared_ptr<advcpp::WaitableQueue<shared_ptr<T> > > pWQ;
    Producer(size_t N, pWQ pqueue)
    :loopNumber(N)
    , m_queue(pqueue)
    {

    }
    virtual void run()
    {
        advcpp::Mutex m;

        for(size_t i = 0; i < loopNumber; ++i)
        {
            m.Lock();
            typename std::tr1::shared_ptr<T>  c(new T);
            resultQueue.push(c);
            m_queue -> Enqueue(c);
            m.Unlock(); 
        }
    }

    std::queue<shared_ptr<T > > Result(){return resultQueue;}


private:
    size_t loopNumber;
    pWQ m_queue;
    std::queue<shared_ptr<T > > resultQueue;
};
bool foo(int producers, int consumers, int producers_mess, int consumer_mess)
{
    std::tr1::shared_ptr<advcpp::WaitableQueue<shared_ptr<Cat> > > wq(new advcpp::WaitableQueue<shared_ptr<Cat> >);
    std::vector<shared_ptr<advcpp::Thread> > pThreadsP;
    std::vector<shared_ptr<advcpp::Thread> > pThreadsC;
    std::tr1::shared_ptr< Producer<Cat > >p(new Producer<Cat >(producers_mess,wq));
    std::tr1::shared_ptr< Consumer<Cat> > c(new Consumer<Cat >( consumer_mess,wq));

    for(int i = 0; i < producers; ++i )
    {
        pThreadsP.push_back(shared_ptr<advcpp::Thread>(new advcpp::Thread(p)));
        pThreadsP[i] ->Join();
    }
    for(int i = 0 ; i  < consumers ;++i)
    {
        pThreadsC.push_back( shared_ptr<advcpp::Thread>(new advcpp::Thread(c)));
        pThreadsC[i] ->Join();
    }

    if(wq -> Empty() && !wq -> Size())
    {
        return true;
    }
    return false;
}


UNIT(waitableQ_fifo)
advcpp::WaitableQueue<shared_ptr<Cat> > wq;
const int N = 1000;
ASSERT_THAT(wq.Empty() == true);
ASSERT_THAT(wq.Size() == 0);
for (size_t i = 0; i < N; ++i)
{
    shared_ptr<Cat> p(new Cat());
    wq.Enqueue(p);
}
ASSERT_THAT(wq.Empty() != true);
ASSERT_THAT(wq.Size() == N);
for(size_t i = 0; i < N; ++i)
{
    std::tr1::shared_ptr<Cat>  c(wq.Dequeue());
    ASSERT_THAT(c -> m_id == i);
}
ASSERT_THAT(wq.Empty() == true);
ASSERT_THAT(wq.Size() == 0);
END_UNIT


UNIT(waitableQ_thread)
const int N = 1000;
Cat::id = 0;
std::tr1::shared_ptr<advcpp::WaitableQueue<shared_ptr<Cat> > > wq(new advcpp::WaitableQueue<shared_ptr<Cat> >);
std::tr1::shared_ptr< Producer<Cat > > p(new Producer<Cat>(N,wq));
std::tr1::shared_ptr< Producer<Cat > > p2(new Producer<Cat>(N,wq));
std::tr1::shared_ptr< Consumer<Cat > > c(new Consumer<Cat >( 2 *N,wq));
advcpp::Thread test(p);
advcpp::Thread test2(p2);
advcpp::Thread test3(c);
test.Join();
test2.Join();
test3.Join();
ASSERT_THAT(wq -> Empty() == true);
ASSERT_EQUAL_INT(wq ->Size() , 0);

std::queue<shared_ptr<Cat > > result = c -> Result();
std::queue<shared_ptr < Cat> > res = p ->Result();
ASSERT_THAT(result.size() == 2 * N);
//ASSERT_THAT(result.size() == N);
//size_t res = 0;

for(size_t i =  0; i <N; ++i)
{
    ASSERT_EQUAL_INT(result.front()->m_id , res.front()->m_id);
    //ASSERT_EQUAL_INT(i, result.front() -> m_id);
    result.pop();
}

//ASSERT_EQUAL_INT(res ,((0 +  (3 * N) -1) * (2 *N))/2);
END_UNIT


UNIT(test_n_m)
int const N = 10;
int const M = 10;
ASSERT_THAT(foo(N,M , 1000, 1000) == true);

END_UNIT

TEST_SUITE(waitable queue unitest)
    TEST(waitableQ_fifo)
    TEST(waitableQ_thread)
    TEST(test_n_m)
END_SUITE