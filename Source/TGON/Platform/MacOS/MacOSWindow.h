/**
 * @file    MacOSWindow.h
 * @author  ggomdyu
 * @since   07/16/2017
 * @brief   The platform specific window class implementation.
 */

#pragma once
#import "Core/CoreObject.h"
#import "Core/DelegateChain.h"

#import "Platform/Config.h"

@class NSWindow;
@class WindowDelegate;

namespace tgon
{

class TGON_API MacOSWindow :
    private boost::noncopyable
{
/**@section Constructor */
protected:
    MacOSWindow(NSWindow* window, WindowDelegate* windowDelegate) noexcept;
    MacOSWindow(MacOSWindow&& rhs) noexcept;

/**@section Destructor */
public:
    virtual ~MacOSWindow();
    
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
