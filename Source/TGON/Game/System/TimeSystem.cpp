#include "PrecompiledHeader.pch"

#include "Core/Time/Time.h"

#include "TimeSystem.h"

namespace tgon
{

TimeSystem::TimeSystem() :
    m_prevTime(GetTickCount()),
    m_timeScale(1.0f),
    m_tickTime(0.0f)
{
}

void TimeSystem::Update()
{
    auto currTime = GetTickCount();

    m_tickTime = (static_cast<float>(currTime - m_prevTime) * 0.001f) * m_timeScale;
    m_prevTime = currTime;
}

void TimeSystem::SetTimeScale(float timeScale)
{
    m_timeScale = timeScale;
}

float TimeSystem::GetTimeScale() const
{
    return m_timeScale;
}

float TimeSystem::GetTickTime() const
{
    return m_tickTime;
}

} /* namespace tgon */