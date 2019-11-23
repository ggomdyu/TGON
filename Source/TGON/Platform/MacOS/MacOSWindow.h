/**
 * @file    MacOSWindow.h
 * @author  ggomdyu
 * @since   07/16/2017
 * @brief   The platform specific window class implementation.
 */

#pragma once
#include "Core/NonCopyable.h"
#include "Platform/Config.h"

@class NSWindow;
@class WindowDelegate;

namespace tgon
{

class MacOSWindow :
    private NonCopyable
{
/**@section Constructor */
protected:
    MacOSWindow(NSWindow* window, WindowDelegate* windowDelegate) noexcept;
    MacOSWindow(MacOSWindow&& rhs) noexcept;

/**@section Operator */
public:
    MacOSWindow& operator=(MacOSWindow&& rhs) noexcept;
  
/**@section Variable */
protected:
    NSWindow* m_window;
    WindowDelegate* m_windowDelegate;
};
    
using PlatformWindow = MacOSWindow;

} /* namespace tgon */
