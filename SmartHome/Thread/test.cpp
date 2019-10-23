#include <unistd.h>
#include <iostream>

#include "mu_test.h"
#include "Thread.h"
#include "Consumer.h"

UNIT(test_thread1_creation_and_join)
std::tr1::shared_ptr<advcpp::Consumer> c(new advcpp::Consumer(1, 1000));
advcpp::Thread test(c);
test.Join();
ASSERT_THAT(c -> Result() == 1000);
std::tr1::shared_ptr<advcpp::Consumer> d(new advcpp::Consumer(1, 1000000));
advcpp::Thread test2(d);
test2.Join();
ASSERT_EQUAL_INT(d -> Result() , 1000000);
std::tr1::shared_ptr<advcpp::Consumer> e(new advcpp::Consumer(1, 1000000000));
advcpp::Thread test3(e);
test3.Join();
ASSERT_THAT(e -> Result() == 1000000000);

END_UNIT


UNIT(test_thread2_on_same_consumer)
std::tr1::shared_ptr<advcpp::Consumer> c(new advcpp::Consumer(1, 100000));
advcpp::Thread test(c);
advcpp::Thread test2(c);
//advcpp::Thread test3(c);
test.Join();
test2.Join();
//test3.Join();
ASSERT_THAT(c -> Result() >= 100000);
END_UNIT

UNIT(test_number_of_cores)
ASSERT_EQUAL_INT(advcpp::Thread::Cpu_cores(), 4);
END_UNIT

UNIT(test_thread_detach)
std::tr1::shared_ptr<advcpp::Consumer> c(new advcpp::Consumer(1, 10000));
advcpp::Thread test(c);
sleep(0);
ASSERT_THAT(c -> Result() > 1);
int result = c -> Result();
test.Detach();
sleep(5);
ASSERT_THAT(c -> Result() >= result);

END_UNIT


UNIT(test_thread_detach_and_join)
std::tr1::shared_ptr<advcpp::Consumer> c(new advcpp::Consumer(1, 100000));
advcpp::Thread test(c);
test.Detach();
test.Join();
END_UNIT

class Sleeper: public advcpp::IRunnable
{
public:
    Sleeper(unsigned int t):sleeptime(t){}
    void run(){ advcpp::Thread::Sleep(sleeptime * 100000);}
private:
    unsigned int sleeptime;
    int result;
};
UNIT(test_sleep)
std::tr1::shared_ptr<Sleeper> s(new Sleeper(5));
advcpp::Thread test(s);
test.Join();
END_UNIT

TEST_SUITE(thread test)
    TEST(test_thread1_creation_and_join)
    TEST(test_thread2_on_same_consumer)
    TEST(test_number_of_cores)
    TEST(test_thread_detach)
    TEST(test_sleep)
    IGNORE_TEST(test_thread_detach_and_join)
END_SUITE