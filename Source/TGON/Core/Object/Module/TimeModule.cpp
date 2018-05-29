#include "PrecompiledHeader.h"

#include "Core/Time/Time.h"

#include "TimeModule.h"

namespace tgon
{

TimeModule::TimeModule() :
    m_prevTime(GetTickCount()),
    m_timeScale(1.0f),
    m_tickTime(0.0f)
{
}

void TimeModule::Update()
{
    auto currTime = GetTickCount();

    m_tickTime = (static_cast<float>(currTime - m_prevTime) * 0.001f) * m_timeScale;
    m_prevTime = currTime;
}

void TimeModule::SetTimeScale(float timeScale)
{
    m_timeScale = timeScale;
}

float TimeModule::GetTimeScale() const
{
    return m_timeScale;
}

float TimeModule::GetTickTime() const
{
    return m_tickTime;
}

} /* namespace tgon */
