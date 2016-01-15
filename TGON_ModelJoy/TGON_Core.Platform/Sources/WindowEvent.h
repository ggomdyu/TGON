#pragma once
/*
* 작성자 : 차준호
* 작성일 : 2015-11-12
* 최종 수정 : 차준호
* 최종 수정일 : 2016-01-09
*/

#include <iostream>
#include <windows.h>

namespace tgon
{

struct WindowEvent
{
private:
	enum PrivateEventTable : unsigned int
	{
	#ifdef PLATFORM_WINDOWS_OS
		TGET_NONE = 0,
		TGET_CREATE = WM_CREATE,
		TGET_SIZE = WM_SIZE,
		TGET_GETFOCUS = WM_SETFOCUS,
		TGET_LOSEFOCUS = WM_KILLFOCUS,
		TGET_MOVE = WM_MOVE,
		TGET_DESTROY = WM_DESTROY,
	#else
		#error	 "You're platform is not supported."
	#endif
	};

public:
	WindowEvent( unsigned int _ev = WindowEvent::None ) :
		ev( _ev ) {};
	~WindowEvent( ) {};

	enum WindowEventTable : unsigned int
	{
		None = TGET_NONE,
		Create = TGET_CREATE,
		GetFocus = TGET_GETFOCUS,
		LoseFocus = TGET_LOSEFOCUS,
		Size = TGET_SIZE,
		Move = TGET_MOVE,
		Destroy = TGET_DESTROY,
	};


	operator unsigned int( ) const	{ return ev; }

private:
	unsigned int ev = 0;
};

}