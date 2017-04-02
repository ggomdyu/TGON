#include "PrecompiledHeader.h"
#include "TimeModule.h"

#include "../../Core/Platform/TTime.h"

namespace tgon
{

TimeModule::TimeModule() :
    m_oldTime(TTime::GetAppExecutionTime())
{
}

void TimeModule::Update()
{
    uint32_t currTime = TTime::GetAppExecutionTime();

    m_elapsedTime = static_cast<float>(currTime - m_oldTime) * 0.001f;

    m_oldTime = currTime;
}

float TimeModule::GetElapsedTime() const
{
    return m_elapsedTime;
}

} /* namespace tgon */
