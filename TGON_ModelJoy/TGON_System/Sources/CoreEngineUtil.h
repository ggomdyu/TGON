/*
* �ۼ��� : ����ȣ
* �ۼ��� : 2015-12-07
* ���� ���� :
* ���� ������ :
*/

#pragma once
#include <functional>
#include <System\WindowSystem.h>
#include <System\TickSystem.h>

namespace tgon
{
	namespace System
	{
		inline void	AddEventCallback( unsigned int evType, std::function<void()> evProc )	{ WindowSystem::GetInstance( )->AddEventCallback( evType, evProc ); }
	}

	namespace Time
	{
		inline float	GetElapsedTime( )	{ return TickSystem::GetInstance( )->GetElapsedTime( ); }
	}
}