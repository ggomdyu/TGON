#include "PrecompiledHeader.h"

#include "Timer.h"
#include "Time.h"

namespace tgon
{
    
Timer::Timer() noexcept :
    Timer(false)
{
}
    
Timer::Timer(bool isAutoReset) noexcept :
    Timer(0, isAutoReset)
{
}

Timer::Timer(int64_t interval, bool isAutoReset) noexcept :
    m_interval(interval),
    m_prevTime(0),
    m_isAutoReset(isAutoReset),
    m_isEnabled(false)
{
}
    
void Timer::Start()
{
    m_isEnabled = true;
    m_prevTime = tgon::GetTickCount();
}

void Timer::Stop()
{
    m_isEnabled = false;
}

void Timer::SetAutoReset(bool isAutoReset)
{
    m_isAutoReset = isAutoReset;
}

bool Timer::IsAutoReset() const noexcept
{
    return m_isAutoReset;
}

void Timer::SetInterval(int64_t interval)
{
    m_interval = interval;
}

int64_t Timer::GetInterval() const noexcept
{
    return m_interval;
}

void Timer::Update()
{
    if (m_isEnabled == false)
    {
        return;
    }
    
    using tgon::GetTickCount;
    
    auto currTime = GetTickCount();
    if ((currTime - m_prevTime) > m_interval)
    {
        if (OnTimeElapsed != nullptr)
        {
            OnTimeElapsed();
        }
        
        if (m_isAutoReset)
        {
            m_prevTime = currTime;
        }
        else
        {
            this->Stop();
        }
    }
}

}
