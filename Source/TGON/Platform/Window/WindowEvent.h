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
	kNone			= 0x0,
	kCreate			= WM_CREATE,
	kGetFocus		= WM_SETFOCUS,
	kLoseFocus		= WM_KILLFOCUS,
	kSize			= WM_SIZE,
	kMove			= WM_MOVE,
	kClose			= WM_CLOSE,
	kDestroy		= WM_DESTROY,
	kLMouseDown		= WM_LBUTTONDOWN,
	kLMouseUp		= WM_LBUTTONUP,
	kRMouseDown		= WM_RBUTTONDOWN,
	kRMouseUp		= WM_RBUTTONUP,
	kMouseMove		= WM_MOUSEMOVE,
#elif

#endif
};


}