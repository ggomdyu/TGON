#include "PrecompiledHeader.h"

#include "Platform/Environment.h"

#include "Timer.h"

namespace tg
{

WorldTimer::WorldTimer() noexcept :
    m_prevTickTime(Environment::GetTickCount())
{
}

TimerHandle WorldTimer::SetTimer(Delegate<void(TimerHandle)> callback, float interval, bool isLoop)
{
    const auto timerHandle = CreateTimerHandle();
    m_timerInfos.push_back(TimerInfo{timerHandle, std::move(callback), 0.0f, interval, isLoop, false});
    
    return timerHandle;
}

float WorldTimer::GetTimerElapsed(TimerHandle timerHandle) const noexcept
{
    auto iter = std::find_if(m_timerInfos.begin(), m_timerInfos.end(), [&](const TimerInfo& timerInfo)
    {
        return timerInfo.timerHandle == timerHandle;
    });
    if (iter == m_timerInfos.end())
    {
        return 0.0f;
    }
    
    return iter->interval - iter->elapsedTime;
}

bool WorldTimer::ClearTimer(TimerHandle timerHandle)
{
    auto iter = std::find_if(m_timerInfos.begin(), m_timerInfos.end(), [&](const TimerInfo& timerInfo)
    {
        return timerInfo.timerHandle == timerHandle;
    });
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

TimerHandle WorldTimer::CreateTimerHandle() noexcept
{
    static int64_t rawTimerHandle;
    return TimerHandle(++rawTimerHandle);
}

void WorldTimer::Update()
{
    const auto tempTickTime = Environment::GetTickCount();

    const auto tickTime = static_cast<float>(tempTickTime - m_prevTickTime) * 0.001f;
    m_prevTickTime = tempTickTime;
    
    for (auto iter = m_timerInfos.begin(); iter != m_timerInfos.end();)
    {
        auto& timerInfo = *iter;
        if (timerInfo.elapsedTime >= timerInfo.interval)
        {
            if (timerInfo.isDeleteReserved == false)
            {
                timerInfo.callback(timerInfo.timerHandle);

                if (timerInfo.isLoop)
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

}
