#include "PrecompiledHeader.h"
#include "TimeModule.h"

#include "../../Core/Platform/TTime.h"

namespace tgon
{

TimeModule::TimeModule() :
    m_oldTime(platform::GetProcessExecutionTime())
{
}

void TimeModule::Update()
{
    std::size_t currTime = platform::GetProcessExecutionTime();

    m_elapsedTime = static_cast<float>(currTime - m_oldTime) * 0.001f;
    m_oldTime = currTime;
}

float TimeModule::GetElapsedTime() const
{
    return m_elapsedTime;
}

} /* namespace tgon */
