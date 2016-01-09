/*
* 작성자 : 차준호
* 작성일 : 2015-12-07
* 최종 수정 :
* 최종 수정일 :
*/

#pragma once
#include <functional>
#include <System\WindowSystem.h>
#include <System\TickSystem.h>

namespace tgon
{
	namespace System
	{
		inline void AddWindowEventCallback( const uint32_t evType, std::function<void()> evProc )
		{
			WindowSystem::GetInstance( )->AddWindowEventCallback( evType, evProc );
		}
	}

	namespace Time
	{
		inline float GetElapsedTime( )
		{
			return TickSystem::GetInstance( )->GetElapsedTime( );
		}
	}
}