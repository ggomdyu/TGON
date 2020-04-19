#include "PrecompiledHeader.h"

#include "Platform/Environment.h"

#include "TimeModule.h"

namespace tg
{

TimeModule::TimeModule() :
    m_lastRecordedTickTime(Environment::GetTickCount()),
    m_timeScale(1.0f),
    m_tickTime(0.0f)
{
}

void TimeModule::SetTimeScale(float timeScale) noexcept
{
    m_timeScale = timeScale;
}

float TimeModule::GetTimeScale() const noexcept
{
    return m_timeScale;
}

float TimeModule::GetTickTime() const noexcept
{
    return m_tickTime;
}

void TimeModule::Update()
{
    auto currTime = Environment::GetTickCount();

    m_tickTime = (static_cast<float>(currTime - m_lastRecordedTickTime) * 0.001f) * m_timeScale;
    m_lastRecordedTickTime = currTime;
}

}
