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
	using WindowImpl = class WindowsWindow;
	using ApplicationImpl = class WindowsApplication;
	using CursorImpl = class WindowsCursor;
	using MathImpl = class WindowsMath;
	using ConsoleImpl = class WindowsConsole;
	using TimeImpl = class WindowsTime;

#elif TGON_PLATFORM_ANDROID
#elif TGON_PLATFORM_LINUX
#endif

	using SpTWindow = std::shared_ptr<class TWindow>;
	using WpTWindow = std::weak_ptr<class TWindow>;
	using TMsgCallback = int32_t(*)( class TWindow*, enum class WindowEvent );

	using SpTGraphics = std::shared_ptr<class TGraphics>;
	using WpTGraphics = std::weak_ptr<class TGraphics>;


}