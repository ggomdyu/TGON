#include "PrecompiledHeader.h"

#include "Platform/Environment.h"

#include "Time.h"

namespace tg
{

Time::Time() :
    m_lastRecordedTickTime(Environment::GetTickCount()),
    m_timeScale(1.0f),
    m_deltaTime(0.0f),
    m_smoothDeltaTime(0.0f)
{
}

void Time::SetTimeScale(float timeScale) noexcept
{
    m_timeScale = timeScale;
}

float Time::GetTimeScale() const noexcept
{
    return m_timeScale;
}

float Time::GetDeltaTime() const noexcept
{
    return m_deltaTime * m_timeScale;
}

float Time::GetUnscaledDeltaTime() const noexcept
{
    return m_deltaTime;
}

float Time::GetSmoothDeltaTime() const noexcept
{
    return m_smoothDeltaTime * m_timeScale;
}

int32_t Time::GetFrameCount() const noexcept
{
    return m_frameCount;
}

void Time::Update()
{
    const auto currTime = Environment::GetTickCount();

    m_deltaTime = static_cast<float>(currTime - m_lastRecordedTickTime) * 0.001f;
    m_smoothDeltaTime = SmoothDeltaTimeFactor * m_deltaTime + (1.0f - SmoothDeltaTimeFactor) * m_smoothDeltaTime;

    ++m_frameCount;

    m_lastRecordedTickTime = currTime;
}

}
