#include "PrecompiledHeader.h"

#include <pthread.h>

#include "../Thread.h"

namespace tgon
{

void Thread::SetPriority(ThreadPriority threadPriority)
{
    static auto maxPriority = sched_get_priority_max(SCHED_FIFO);
    static auto minPriority = sched_get_priority_min(SCHED_FIFO);
    auto priorityInterval = (maxPriority - minPriority) / 3;
    
    int threadPriorityTable[] = {
        maxPriority,
        minPriority + priorityInterval * 2,
        minPriority + priorityInterval,
        minPriority
    };

    sched_param schedParam;
    schedParam.sched_priority = threadPriorityTable[static_cast<int>(threadPriority)];
    pthread_setschedparam(this->native_handle(), SCHED_FIFO, &schedParam);
}

} /* namespace tgon */
