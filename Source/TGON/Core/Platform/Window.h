/**
 * @file    Window.h
 * @author  ggomdyu
 * @since   02/15/2018
 * @brief   The platform agnostic window class implement.
 */

#pragma once
#include "Core/Platform/Config.h"
#include "Core/Object/DelegateChain.h"
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

#include "WindowType.h"

namespace tgon
{

class TGON_API Window final :
    private boost::noncopyable
{
/* @section Private constructor */
public:
    Window();
    Window(const WindowStyle& windowStyle);

/* @section Public constructor */
public:
    ~Window();
    
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
    void SetTopMost(bool setTopMost);
    void SetTransparency(float transparency);
    void GetPosition(int32_t* x, int32_t* y) const;
    void GetSize(int32_t* width, int32_t* height) const;
    void GetTitle(char* destStr) const;
    I32Point GetPosition() const;
    I32Extent2D GetSize() const;
    float GetTransparency() const;
    void* GetNativeWindow() const;
    bool HasCaption() const;
    bool IsResizable() const;
    bool IsMaximized() const;
    bool IsMinimized() const;
    bool IsTopMost() const;
    const WindowImpl& GetImpl() const noexcept;
    WindowImpl& GetImpl() noexcept;

/* @section Public event handler */
public:
    DelegateChain<void(int32_t, int32_t)> OnWindowMove;
    DelegateChain<void(int32_t, int32_t)> OnWindowResize;
    DelegateChain<void()> OnWindowMaximize;
    DelegateChain<void()> OnWindowMinimize;
    DelegateChain<void()> OnWindowEnterFullScreen;
    DelegateChain<void()> OnWindowExitFullScreen;
    DelegateChain<void()> OnWindowWillClose;
    DelegateChain<void()> OnWindowDidClose;
    DelegateChain<void()> OnWindowGetFocus;
    DelegateChain<void()> OnWindowLoseFocus;

/* @section Private variable */
private:
    WindowImpl m_windowImpl;
};

} /* namespace tgon */
