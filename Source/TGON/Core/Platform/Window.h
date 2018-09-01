/**
 * @file    Window.h
 * @author  ggomdyu
 * @since   02/15/2018
 * @brief   The platform agnostic window class implement.
 */

#pragma once
#include "Core/Object/CoreObject.h"
#include "Core/Math/Point.h"
#include "Core/Math/Extent.h"

#if TGON_PLATFORM_WINDOWS
#   include "Windows/WindowsWindow.h"
#elif TGON_PLATFORM_MACOS
#   import "MacOS/MacOSWindow.h"
#elif TGON_PLATFORM_ANDROID
#   include "Android/AndroidWindow.h"
#elif BOOST_OS_IOS
#   import "IOS/IOSWindow.h"
#endif

namespace tgon
{

class TGON_API Window final :
    private PlatformWindow
{
public:
    TGON_RUNTIME_OBJECT(Window);

/* @section Private constructor */
public:
    using PlatformWindow::PlatformWindow;

/* @section Public method */
public:
    using PlatformWindow::Show;
    using PlatformWindow::Hide;
    using PlatformWindow::Close;
    using PlatformWindow::Maximize;
    using PlatformWindow::Minimize;
    using PlatformWindow::BringToFront;
    using PlatformWindow::SetPosition;
    using PlatformWindow::SetSize;
    using PlatformWindow::SetTitle;
    using PlatformWindow::SetTopMost;
    using PlatformWindow::SetTransparency;
    using PlatformWindow::GetPosition;
    using PlatformWindow::GetSize;
    using PlatformWindow::GetTitle;
    I32Point GetPosition() const;
    I32Extent2D GetSize() const;
    using PlatformWindow::GetTransparency;
    using PlatformWindow::GetNativeWindow;
    using PlatformWindow::HasCaption;
    using PlatformWindow::IsResizable;
    using PlatformWindow::IsMaximized;
    using PlatformWindow::IsMinimized;
    using PlatformWindow::IsTopMost;

/* @section Public event handler */
public:
    using PlatformWindow::OnWindowMove;
    using PlatformWindow::OnWindowResize;
    using PlatformWindow::OnWindowMaximize;
    using PlatformWindow::OnWindowMinimize;
    using PlatformWindow::OnWindowEnterFullScreen;
    using PlatformWindow::OnWindowExitFullScreen;
    using PlatformWindow::OnWindowWillClose;
    using PlatformWindow::OnWindowDidClose;
    using PlatformWindow::OnWindowGetFocus;
    using PlatformWindow::OnWindowLoseFocus;
};

} /* namespace tgon */
