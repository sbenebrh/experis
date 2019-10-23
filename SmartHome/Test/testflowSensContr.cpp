#include "mu_test.h"

#include <unistd.h>

#include "Server.h"


#include "ConfigurationAgent.h"

using namespace advcpp;
using namespace smartHome;
UNIT(test_flow1)

Server test("./config1.cfg");
test.start();
sleep(10);
test.stop();

END_UNIT


TEST_SUITE(first series of test step 1 project)
    TEST(test_flow1)
END_SUITE


