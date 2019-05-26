#include "PrecompiledHeader.h"

#include <Windows.h>

#include "../Thread.h"

namespace tgon
{

void Thread::SetPriority(ThreadPriority threadPriority)
{
    constexpr int threadPriorityTable[] = {
        THREAD_PRIORITY_TIME_CRITICAL,
        THREAD_PRIORITY_HIGHEST,
        THREAD_PRIORITY_NORMAL,
        THREAD_PRIORITY_LOWEST
    };

    HANDLE threadHandle = OpenThread(THREAD_ALL_ACCESS, TRUE, GetCurrentThreadId());
    if (threadHandle != nullptr)
    {
        // Should we have to disable the boost option?
        //SetThreadPriorityBoost(threadHandle, TRUE);
        SetThreadPriority(threadHandle, threadPriorityTable[static_cast<int>(threadPriority)]);
    }
}

} /* namespace tgon */
