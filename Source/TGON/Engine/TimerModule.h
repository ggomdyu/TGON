/**
 * @file    TimerModule.h
 * @author  ggomdyu
 * @since   12/02/2019
 */

#pragma once
#include <vector>
#include <mutex>

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
    /**@section Constructor */
    public:
        template <typename _CallbackType>
        TimerInfo(TimerHandle timerHandle, _CallbackType&& callback, float elapsedTime, float interval, bool isLoop) noexcept(std::is_nothrow_move_constructible_v<_CallbackType>);
        
    /**@section Variable */
    public:
        TimerHandle timerHandle;
        Delegate<void()> callback;
        float elapsedTime;
        float interval;
        bool isLoop;
    };

/**@section Constructor */
public:
    TimerModule() noexcept;

/**@section Method */
public:
    TimerHandle SetTimer(const Delegate<void()>& callback, float interval, bool isLoop);
    TimerHandle SetTimer(Delegate<void()>&& callback, float interval, bool isLoop);
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

template <typename _CallbackType>
inline TimerModule::TimerInfo::TimerInfo(TimerHandle timerHandle, _CallbackType&& callback, float elapsedTime, float interval, bool isLoop) noexcept(std::is_nothrow_move_constructible_v<_CallbackType>) :
   timerHandle(timerHandle),
   callback(std::move(callback)),
   elapsedTime(elapsedTime),
   interval(interval),
   isLoop(isLoop)
{
}


} /* namespace tgon */
