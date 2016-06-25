/*
* Author : Junho-Cha
* Date : 02/16/2016
* Latest author :
* Latest date :
*/

#pragma once


namespace tgon
{


#if BOOST_OS_WINDOWS
	using WindowImpl = class WindowsWindow;
	using ApplicationImpl = class WindowsApplication;
	using CursorImpl = class WindowsCursor;
	using ConsoleImpl = class WindowsConsole;
	using TimeImpl = class WindowsTime;
	using GraphicsImpl = class D3D9Graphics;
#elif BOOST_OS_ANDROID
	using WindowImpl = class AndroidWindow;
	using ApplicationImpl = class AndroidApplication;
	using CursorImpl = class AndroidCursor;
	using ConsoleImpl = class AndroidConsole;
	using TimeImpl = class AndroidTime;
	using GraphicsImpl = class D3D9Graphics;
#endif

using TWindow = WindowImpl;
using TApplication = ApplicationImpl;
using TCursor = CursorImpl;
using TConsole = ConsoleImpl;
using TTime = TimeImpl;
using TGraphics = GraphicsImpl;

using SpTWindow = std::shared_ptr<TWindow>;
using WpTWindow = std::weak_ptr<TWindow>;
using SpTGraphics = std::shared_ptr<TGraphics>;
using WpTGraphics = std::weak_ptr<TGraphics>;


}