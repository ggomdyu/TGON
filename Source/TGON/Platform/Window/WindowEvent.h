/*
* Author : Junho-Cha
* Date : 11/12/2015
* Latest author :
* Latest date :
*/

#pragma once


namespace tgon
{


enum struct WindowEvent
{
#if BOOST_OS_WINDOWS
	kNone = 0x0,
	kCreate = WM_CREATE,
	kGetFocus = WM_SETFOCUS,
	kLoseFocus = WM_KILLFOCUS,
	kSize = WM_SIZE,
	kMove = WM_MOVE,
	kClose = WM_CLOSE,
	kDestroy = WM_DESTROY,
	kLMouseDown = WM_LBUTTONDOWN,
	kLMouseUp = WM_LBUTTONUP,
	kRMouseDown = WM_RBUTTONDOWN,
	kRMouseUp = WM_RBUTTONUP,
	kMouseMove = WM_MOUSEMOVE,
#elif

#endif
};


}