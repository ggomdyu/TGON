/*
* Author : Junho-Cha
* Date : 02/16/2016
* Latest author :
* Latest date :
*/

#pragma once
#include "../Config/Platform.h"
#include <memory>


namespace tgon
{

#ifdef TGON_PLATFORM_WINDOWS
	class WindowsWindow;
	using WindowImpl = WindowsWindow;
	class WindowsApplication;
	using ApplicationImpl = WindowsApplication;
	class WindowsCursor;
	using CursorImpl = WindowsCursor;
	class WindowsPlatformMath;
	using MathImpl = WindowsPlatformMath;
	class WindowsConsole;
	using ConsoleImpl = WindowsConsole;

#elif TGON_PLATFORM_ANDROID
#elif TGON_PLATFORM_LINUX
#endif

	class TWindow;
	using SpTWindow = std::shared_ptr<TWindow>;
	using WpTWindow = std::weak_ptr<TWindow>;
	using TMsgCallback = int32_t(*)( TWindow*, enum class WindowEvent );

	class TGraphics;
	using SpTGraphics = std::shared_ptr<TGraphics>;
	using WpTGraphics = std::weak_ptr<TGraphics>;


}