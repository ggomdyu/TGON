/*
* 작성자 : 차준호
* 작성일 : 2015-12-07
* 최종 수정 :
* 최종 수정일 :
*/

#pragma once
#include <functional>
#include <System\TickSystem.h>

namespace tgon
{
	namespace System
	{
		inline void	AddEventCallback( unsigned int evType, std::function<void()> evProc )
		{
			abort( );
			//::GetInstance( )->GetWindow( )->AddEventCallback( evType, evProc );
		}
	}

	namespace Time
	{
		inline float	GetElapsedTime( )
		{
			return GetTickSystem( )->GetElapsedTime( );
		}
	}
}