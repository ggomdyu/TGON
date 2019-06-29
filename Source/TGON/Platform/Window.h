/**
 * @file    Window.h
 * @author  ggomdyu
 * @since   02/15/2018
 * @brief   The platform agnostic window class implement.
 */

#pragma once
#include "Platform/Config.h"
#include "Math/Point.h"
#include "Math/Extent.h"

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
/**@section Constructor */
public:
    using PlatformWindow::PlatformWindow;

/**@section Method */
public:
    I32Point GetPosition() const;
    I32Extent2D GetExtent() const;
    PlatformWindow* GetPlatformDependency() noexcept;
    const PlatformWindow* GetPlatformDependency() const noexcept;
    
    using PlatformWindow::Show;
    using PlatformWindow::Hide;
    using PlatformWindow::Close;
    using PlatformWindow::Maximize;
    using PlatformWindow::Minimize;
    using PlatformWindow::BringToFront;
    using PlatformWindow::SetPosition;
    using PlatformWindow::SetContentSize;
    using PlatformWindow::SetTitle;
    using PlatformWindow::SetTopMost;
    using PlatformWindow::SetTransparency;
    using PlatformWindow::GetPosition;
    using PlatformWindow::GetExtent;
    using PlatformWindow::GetTitle;
    using PlatformWindow::GetTransparency;
    using PlatformWindow::GetNativeWindow;
    using PlatformWindow::HasCaption;
    using PlatformWindow::IsResizable;
    using PlatformWindow::IsMaximized;
    using PlatformWindow::IsMinimized;
    using PlatformWindow::IsTopMost;

/**@section Event handler */
public:
    using PlatformWindow::OnMove;
    using PlatformWindow::OnResize;
    using PlatformWindow::OnMaximize;
    using PlatformWindow::OnMinimize;
    using PlatformWindow::OnEnterFullScreen;
    using PlatformWindow::OnExitFullScreen;
    using PlatformWindow::OnWillClose;
    using PlatformWindow::OnDidClose;
    using PlatformWindow::OnGetFocus;
    using PlatformWindow::OnLoseFocus;
};

} /* namespace tgon */
