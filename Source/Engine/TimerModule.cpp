#include "PrecompiledHeader.h"

#include "Platform/Environment.h"

#include "TimerModule.h"

namespace tg
{

TimerModule::TimerModule() noexcept :
    m_prevTickTime(Environment::GetTickCount())
{
}

TimerHandle TimerModule::SetTimer(Delegate<void()> callback, float interval, bool isLoop)
{
    const auto timerHandle = CreateTimerHandle();

    m_timerInfos.push_back(TimerInfo{
        .timerHandle = timerHandle,
        .callback = std::move(callback),
        .elapsedTime = 0.0f,
        .interval = interval,
        .isLoop = isLoop,
        .isDeleteReserved = false
    });
    
    return timerHandle;
}

float TimerModule::GetTimerElapsed(TimerHandle timerHandle) const noexcept
{
    auto predicate = [&](const TimerInfo& timerInfo)
    {
        return timerInfo.timerHandle == timerHandle;
    };

    const auto iterator = std::find_if(m_timerInfos.cbegin(), m_timerInfos.cend(), predicate);
    if (iterator == m_timerInfos.cend())
    {
        return 0.0f;
    }
    
    return iterator->interval - iterator->elapsedTime;
}

bool TimerModule::ClearTimer(TimerHandle timerHandle)
{
    auto predicate = [&](const TimerInfo& timerInfo)
    {
        return timerInfo.timerHandle == timerHandle;
    };

    const auto iterator = std::find_if(m_timerInfos.begin(), m_timerInfos.end(), predicate);
    if (iterator != m_timerInfos.end())
    {
        iterator->isDeleteReserved = true;
        return true;
    }

    return false;
}

TimerHandle TimerModule::CreateTimerHandle() noexcept
{
    static int64_t rawTimerHandle;
    return TimerHandle(++rawTimerHandle);
}

void TimerModule::Update()
{
    const auto tempTickTime = Environment::GetTickCount();

    const auto tickTime = static_cast<float>(tempTickTime - m_prevTickTime) * 0.001f;
    m_prevTickTime = tempTickTime;
    
    for (auto iterator = m_timerInfos.begin(); iterator != m_timerInfos.end();)
    {
        auto& timerInfo = *iterator;
        if (timerInfo.elapsedTime >= timerInfo.interval)
        {
            if (timerInfo.isDeleteReserved == false)
            {
                timerInfo.callback();

                if (timerInfo.isLoop)
                {
                    timerInfo.elapsedTime = 0.0f;
                }
                else
                {
                    iterator = m_timerInfos.erase(iterator);
                    continue;
                }
            }
            else
            {
                iterator = m_timerInfos.erase(iterator);
                continue;
            }
        }
        else
        {
            timerInfo.elapsedTime += tickTime;
        }
        
        ++iterator;
    }
}

}
