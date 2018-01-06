#include "PrecompiledHeader.pch"

#include "TimeModule.h"

#include "Core/Platform/Time.h"

namespace tgon
{
namespace game
{

TimeModule::TimeModule() :
    m_prevTime(core::GetTickCount()),
    m_timeScale(1.0f),
    m_deltaTime(0.0f)
{
}

void TimeModule::Update()
{
    auto currTime = core::GetTickCount();

    m_deltaTime = (static_cast<float>(currTime - m_prevTime) * 0.001f) * m_timeScale;
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

float TimeModule::GetDeltaTime() const
{
    return m_deltaTime;
}

} /* namespace game */
} /* namespace tgon */