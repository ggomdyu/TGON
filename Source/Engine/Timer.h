#pragma once

#include <vector>

#include "Core/Delegate.h"

#include "Module.h"

namespace tg
{

using TimerHandle = int64_t;

class WorldTimer :
	public Module
{
public:
    TGON_RTTI(WorldTimer)

/**@section Struct */
private:
    struct TimerInfo
    {
        TimerHandle timerHandle;
        Delegate<void(TimerHandle)> callback;
        float elapsedTime = 0.0f;
        float interval = 0.0f;
        bool isLoop = false;
        bool isDeleteReserved = false;
    };

/**@section Constructor */
public:
    WorldTimer() noexcept;

/**@section Method */
public:
    TimerHandle SetTimer(Delegate<void(TimerHandle)> callback, float interval, bool isLoop);
    bool ClearTimer(TimerHandle timerHandle);
    [[nodiscard]] float GetTimerElapsed(TimerHandle timerHandle) const noexcept;
    void Update() override;

private:
    static TimerHandle CreateTimerHandle() noexcept;
    
/**@section Variable */
public:
    static constexpr auto ModuleStage = ModuleStage::Update;

private:
    int64_t m_prevTickTime;
    std::vector<TimerInfo> m_timerInfos;
};

}
