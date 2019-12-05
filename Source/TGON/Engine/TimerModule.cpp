#include "PrecompiledHeader.h"

#include "Diagnostics/Debug.h"
#include "Platform/Environment.h"

#include "TimerModule.h"

namespace tgon
{

TimerModule::TimerModule() noexcept :
    m_lastRecordedTickTime(Environment::GetTickCount())
{
}

TimerHandle TimerModule::SetTimer(const Delegate<void()>& callback, float interval, bool isLoop)
{
    auto timerHandle = CreateTimerHandle();
    m_timerInfos.push_back(TimerInfo{timerHandle, callback, 0.0f, interval, isLoop, false});
    
    return timerHandle;
}

TimerHandle TimerModule::SetTimer(Delegate<void()>&& callback, float interval, bool isLoop)
{
    auto timerHandle = CreateTimerHandle();
    m_timerInfos.push_back(TimerInfo{timerHandle, callback, 0.0f, interval, isLoop, false});
    
    return timerHandle;
}

float TimerModule::GetTimerElapsed(TimerHandle timerHandle) const noexcept
{
    auto iter = this->FindTimerInfo(timerHandle);
    if (iter == m_timerInfos.end())
    {
        return 0.0f;
    }
    
    return iter->interval - iter->elapsedTime;
}

bool TimerModule::ClearTimer(TimerHandle timerHandle)
{
    auto iter = this->FindTimerInfo(timerHandle);
    if (iter != m_timerInfos.end())
    {
        iter->isDeleteReserved = true;
        return true;
    }
    else
    {
        return false;
    }
}

std::vector<TimerModule::TimerInfo>::iterator TimerModule::FindTimerInfo(TimerHandle timerHandle) noexcept
{
    return std::lower_bound(m_timerInfos.begin(), m_timerInfos.end(), timerHandle, [&](const TimerInfo& lhs, TimerHandle rhs)
    {
        return lhs.timerHandle < rhs;
    });
}

std::vector<TimerModule::TimerInfo>::const_iterator TimerModule::FindTimerInfo(TimerHandle timerHandle) const noexcept
{
    return const_cast<TimerModule*>(this)->FindTimerInfo(timerHandle);
}

TimerHandle TimerModule::CreateTimerHandle() noexcept
{
    static int64_t rawTimerHandle;
    return TimerHandle(++rawTimerHandle);
}

void TimerModule::Update()
{
    auto currTime = Environment::GetTickCount();

    auto tickTime = static_cast<float>(currTime - m_lastRecordedTickTime) * 0.001f;
    m_lastRecordedTickTime = currTime;
    
    for (auto iter = m_timerInfos.begin(); iter != m_timerInfos.end();)
    {
        auto& timerInfo = *iter;
        if (timerInfo.elapsedTime >= timerInfo.interval)
        {
            timerInfo.callback();
            if (timerInfo.isLoop && timerInfo.isDeleteReserved == false)
            {
                timerInfo.elapsedTime = 0.0f;
            }
            else
            {
                iter = m_timerInfos.erase(iter);
                continue;
            }
        }
        else
        {
            timerInfo.elapsedTime += tickTime;
        }
        
        ++iter;
    }
}

} /* namespace tgon */
