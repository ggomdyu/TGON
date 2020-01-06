/**
 * @file    TimerModule.h
 * @author  ggomdyu
 * @since   12/02/2019
 */

#pragma once
#include <vector>

#include "Core/Delegate.h"

#include "TimerHandle.h"
#include "Module.h"

namespace tgon
{

class TimerModule :
	public Module
{
public:
    TGON_DECLARE_RTTI(TimerModule)

/**@section Struct */
private:
    struct TimerInfo
    {
        TimerHandle timerHandle;
        Delegate<void(TimerHandle)> callback;
        float elapsedTime;
        float interval;
        bool isLoop;
        bool isDeleteReserved;
    };

/**@section Constructor */
public:
    TimerModule() noexcept;

/**@section Method */
public:
    TimerHandle SetTimer(const Delegate<void(TimerHandle)>& callback, float interval, bool isLoop);
    TimerHandle SetTimer(Delegate<void(TimerHandle)>&& callback, float interval, bool isLoop);
    float GetTimerElapsed(TimerHandle timerHandle) const noexcept;
    bool ClearTimer(TimerHandle timerHandle);
    void Update() override;
    
private:
    std::vector<TimerInfo>::iterator FindTimerInfo(TimerHandle timerHandle) noexcept;
    std::vector<TimerInfo>::const_iterator FindTimerInfo(TimerHandle timerHandle) const noexcept;
    static TimerHandle CreateTimerHandle() noexcept;
    
/**@section Variable */
private:
    int64_t m_lastRecordedTickTime;
    std::vector<TimerInfo> m_timerInfos;
};

} /* namespace tgon */
