#pragma once

#include "Core/NonCopyable.h"
#include "Platform/Config.h"

@class NSWindow;
@class WindowDelegate;

namespace tg
{

class MacOSWindow :
    private NonCopyable
{
/**@section Constructor */
protected:
    MacOSWindow(const struct WindowStyle& windowStyle) noexcept;
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

}
