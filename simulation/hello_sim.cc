#include "hello_sim.h"

bool SimHelloMonitor::_sleep(int DURATION_MS)
{
    waitSimulatedTime(DURATION_MS);

    return true;
}

uint32_t SimHelloMonitor::getCurrentTimeMS()
{
    return getSimulatedTime();
}