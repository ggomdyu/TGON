#pragma once

#include "Module.h"

namespace tg
{

class TimeModule final :
	public Module
{
public:
    TGON_RTTI(TimeModule)

/**@section Constructor */
public:
    TimeModule();

/**@section Method */
public:
    void Update() override;
    void SetTimeScale(float timeScale) noexcept;
    [[nodiscard]] float GetTimeScale() const noexcept;
    [[nodiscard]] float GetDeltaTime() const noexcept;
    [[nodiscard]] float GetUnscaledDeltaTime() const noexcept;
    [[nodiscard]] float GetSmoothDeltaTime() const noexcept;
    [[nodiscard]] int32_t GetFrameCount() const noexcept;

/**@section Variable */
public:
    static constexpr auto ModuleStage = ModuleStage::Update;

private:
    int64_t m_lastRecordedTickTime;
    float m_timeScale;
    float m_deltaTime;
    float m_smoothDeltaTime;
    int32_t m_frameCount = 0;
    static constexpr float SmoothDeltaTimeFactor = 0.2f;
};

}
