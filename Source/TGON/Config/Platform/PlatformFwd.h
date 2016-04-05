/*
* 작성자 : 차준호
* 작성일 : 2016-02-16
* 최종 수정 :
* 최종 수정일 :
*/

#pragma once
#include "Platform.h"
#include <memory>


namespace tgon
{

#ifdef TGON_PLATFORM_WINDOWS
	class WindowsCursor;
	using CursorImpl = WindowsCursor;
	class WindowsWindow;
	using WindowImpl = WindowsWindow;
	class WindowsApplication;
	using ApplicationImpl = WindowsApplication;
	class WindowsMath;
	using MathImpl = WindowsMath;
	class WindowsConsole;
	using ConsoleImpl = WindowsConsole;

#elif TGON_PLATFORM_ANDROID
	class AndroidCursor;
	using CursorImpl = AndroidCursor;
	class AndroidWindow;
	using WindowImpl = AndroidWindow;
	class AndroidApplication;
	using ApplicationImpl = AndroidApplication;
	class AndroidPlatformMath;
	using MathImpl = AndroidPlatformMath;

#elif TGON_PLATFORM_LINUX

#endif

	class TWindow;
	using SpTWindow = std::shared_ptr<TWindow>;

	class TGraphicsDevice;
	using SpTGraphicsDevice = std::shared_ptr<TGraphicsDevice>;
}