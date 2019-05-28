#include "PrecompiledHeader.h"

#include "Thread.h"

namespace tgon
{
namespace
{

std::thread::id g_mainThreadId = std::this_thread::get_id();

} /* namespace */

void Thread::Detach()
{
    this->detach();
}

void Thread::Join()
{
    this->join();
}

bool Thread::Joinable() const
{
    return this->joinable();
}

Thread::ThreadId Thread::GetId() const noexcept
{
    return this->get_id();
}

const void* Thread::GetNativeHandle() const
{
    return const_cast<Thread*>(this)->native_handle();
}

void* Thread::GetNativeHandle()
{
    return this->native_handle();
}

void Thread::Swap(Thread& rhs)
{
    this->swap(rhs);
}

int32_t Thread::GetHardwareConcurrency() noexcept
{
    return static_cast<int32_t>(std::thread::hardware_concurrency());
}

bool Thread::IsMainThread(ThreadId threadId) noexcept
{
    return threadId == g_mainThreadId;
}

} /* namespace tgon */
