/**
 * @file    MacOSWindow.h
 * @author  ggomdyu
 * @since   07/16/2017
 * @brief   The platform specific window class implementation.
 */

#pragma once
#include <boost/noncopyable.hpp>

#include "Core/Platform/Config.h"
#include "Core/Math/Point.h"
#include "Core/Math/Extent.h"

@class NSWindow;
@class WindowDelegate;

namespace tgon
{
    
class Window;
struct WindowStyle;

class TGON_API MacOSWindow final :
    private boost::noncopyable
{
/* @section Public constructor */
public:
    MacOSWindow(Window* owner);
    explicit MacOSWindow(Window* owner, const WindowStyle& windowStyle);
    MacOSWindow(MacOSWindow&& rhs) noexcept;
    
/* @section Public operator */
public:
    MacOSWindow& operator=(MacOSWindow&& rhs) noexcept;
    
/* @section Public destructor */
public:
    ~MacOSWindow();
    
/* @section Public method */
public:
    void Show();
    void Hide();
    void Close();
    void Maximize();
    void Minimize();
    void BringToFront();
    void SetPosition(int32_t x, int32_t y);
    void SetSize(int32_t width, int32_t height);
    void SetTitle(const char* title);
    void SetFullScreen(bool isFullScreen);
    void SetTopMost(bool setTopMost);
    void SetTransparency(float transparency);
    void GetPosition(int32_t* x, int32_t* y) const;
    void GetSize(int32_t* width, int32_t* height) const;
    void GetTitle(char* destStr) const;
    float GetTransparency() const;
    void* GetNativeWindow() const;
    bool HasCaption() const;
    bool IsResizable() const;
    bool IsMaximized() const;
    bool IsMinimized() const;
    bool IsTopMost() const;
    
/* @section Private variable */
private:
    NSWindow* m_nsWindow;
};
    
using PlatformWindow = MacOSWindow;

} /* namespace tgon */
