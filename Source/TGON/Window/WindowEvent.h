/*
* 작성자 : 차준호
* 작성일 : 2015-11-12
* 최종 수정 :
* 최종 수정일 :
*/

#pragma once
#include <iostream>
#include "../Config/Platform/Platform.h"

#ifdef TGON_PLATFORM_WINDOWS
	#define WIN32_LEAN_AND_MEAN
	#include <windows.h>
	#undef WIN32_LEAN_AND_MEAN
#endif

namespace tgon {


enum class WindowEvent
{
#ifdef TGON_PLATFORM_WINDOWS
	None			= 0x0000,
	Create			= WM_CREATE,
	GetFocus		= WM_SETFOCUS,
	LoseFocus		= WM_KILLFOCUS,
	Size			= WM_SIZE,
	Move			= WM_MOVE,
	Destroy			= WM_QUIT,
	LMouseDown		= WM_LBUTTONDOWN,
	LMouseUp		= WM_LBUTTONUP,
	RMouseDown		= WM_RBUTTONDOWN,
	RMouseUp		= WM_RBUTTONUP,
	MouseMove		= WM_MOUSEMOVE,
#elif



#endif
};


}