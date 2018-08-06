#include "PrecompiledHeader.h"

#include "Core/Time/Time.h"

#include "ResourceModule.h"

namespace tgon
{

ResourceModule::ResourceModule() :
    m_lastRecordedTickTime(GetTickCount()),
    m_timeScale(1.0f),
    m_tickTime(0.0f)
{
}

void ResourceModule::Update()
{
    auto currTime = GetTickCount();

    m_tickTime = (static_cast<float>(currTime - m_lastRecordedTickTime) * 0.001f) * m_timeScale;
    m_lastRecordedTickTime = currTime;
}

void ResourceModule::SetTimeScale(float timeScale) noexcept
{
    m_timeScale = timeScale;
}

float ResourceModule::GetTimeScale() const noexcept
{
    return m_timeScale;
}

float ResourceModule::GetTickTime() const noexcept
{
    return m_tickTime;
}

} /* namespace tgon */
