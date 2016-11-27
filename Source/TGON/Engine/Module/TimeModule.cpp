#include "PrecompiledHeader.h"
#include "TimeModule.h"

#include "../../Core/Platform/OSAL/PlatformTime.h"

namespace tgon
{

TimeModule::TimeModule( ) :
    m_oldTime( Time::GetAppExecutionTime( ))
{
}

void TimeModule::Update( )
{
    uint32_t currTime = Time::GetAppExecutionTime( );

    m_elapsedTime = static_cast<float>( currTime - m_oldTime ) * 0.001f;

    m_oldTime = currTime;
}

float TimeModule::GetElapsedTime( ) const
{
    return m_elapsedTime;
}

} /* namespace tgon */