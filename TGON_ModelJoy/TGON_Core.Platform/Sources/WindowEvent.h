#pragma once
/*
* 작성자 : 차준호
* 작성일 : 2015-11-12
* 최종 수정 : 차준호
* 최종 수정일 : 2016-01-09
*/

#include <iostream>
#include <windows.h>

struct WindowEvent
{
private:
	enum PrivateEvTable
	{
	#ifdef PLATFORM_WINDOWS_OS
		TGET_NONE = 0,
		TGET_CREATE = WM_CREATE,
		TGET_SIZE = WM_SIZE,
		TGET_GETFOCUS = WM_SETFOCUS,
		TGET_LOSEFOCUS = WM_KILLFOCUS,
		TGET_MOVE = WM_MOVE,
		TGET_DESTROY = WM_DESTROY,

	#elif PLATFORM_ANDROID_OS

		
	#endif
	};

public:
	WindowEvent( uint32_t _msg = WindowEvent::None ) :
		msg( _msg ) {}

	enum WindowEventTable : uint32_t
	{
		None = TGET_NONE,
		Create = TGET_CREATE,
		GetFocus = TGET_GETFOCUS,
		LoseFocus = TGET_LOSEFOCUS,
		Size = TGET_SIZE,
		Move = TGET_MOVE,
		Destroy = TGET_DESTROY,
	};

	uint32_t msg = 0;
};