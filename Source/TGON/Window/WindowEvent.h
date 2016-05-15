/*
* Author : Junho-Cha
* Date : 11/12/2015
* Latest author :
* Latest date :
*/

#pragma once
#include "../Config/Platform.h"


#ifdef TGON_PLATFORM_WINDOWS
	#define WIN32_LEAN_AND_MEAN
	#include <windows.h>
	#undef WIN32_LEAN_AND_MEAN
#endif


namespace tgon
{


enum struct WindowEvent
{
#ifdef TGON_PLATFORM_WINDOWS
	None			= 0x0,
	Create			= WM_CREATE,
	GetFocus		= WM_SETFOCUS,
	LoseFocus		= WM_KILLFOCUS,
	Size			= WM_SIZE,
	Move			= WM_MOVE,
	Close			= WM_CLOSE,
	Destroy			= WM_DESTROY,
	LMouseDown		= WM_LBUTTONDOWN,
	LMouseUp		= WM_LBUTTONUP,
	RMouseDown		= WM_RBUTTONDOWN,
	RMouseUp		= WM_RBUTTONUP,
	MouseMove		= WM_MOUSEMOVE,
#elif



#endif
};


}