/*
* Author : Junho-Cha
* Date : 02/16/2016
* Latest author :
* Latest date :
*/

#pragma once
#include <memory>


namespace tgon
{


/*
	Forward declaration for Implemented
*/
using WindowImpl = class WindowsWindow;
using ApplicationImpl = class WindowsApplication;
using CursorImpl = class WindowsCursor;
using ConsoleImpl = class WindowsConsole;
using TimeImpl = class WindowsTime;
using GraphicsImpl = class D3d9Graphics;

/*
	Forward declaration for T series
*/
using TWindow = WindowImpl;
using TApplication = ApplicationImpl;
using TCursor = CursorImpl;
using TConsole = ConsoleImpl;
using TTime = TimeImpl;
using TGraphics = GraphicsImpl;

/*
	Forward declaration for T series's extension
*/
using SpTWindow = std::shared_ptr<WindowImpl>;
using WpTWindow = std::weak_ptr<WindowImpl>;
using SpTGraphics = std::shared_ptr<GraphicsImpl>;
using WpTGraphics = std::weak_ptr<GraphicsImpl>;


}