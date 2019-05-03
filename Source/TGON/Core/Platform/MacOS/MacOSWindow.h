/**
 * @file    MacOSWindow.h
 * @author  ggomdyu
 * @since   07/16/2017
 * @brief   The platform specific window class implementation.
 */

#pragma once
#import "Core/Object/CoreObject.h"
#import "Core/Object/DelegateChain.h"

#import "../WindowType.h"

@class NSWindow;
@class WindowDelegate;

namespace tgon
{

class TGON_API MacOSWindow :
    public CoreObject
{
public:
    TGON_DECLARE_RTTI(MacOSWindow);
    
/**@section Public constructor */
public:
    explicit MacOSWindow(const WindowStyle& windowStyle);
    MacOSWindow(MacOSWindow&& rhs) noexcept;
    
/**@section Public operator */
public:
    MacOSWindow& operator=(MacOSWindow&& rhs) noexcept;
    
/**@section Public destructor */
public:
    virtual ~MacOSWindow();
    
/**@section Public method */
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
    
/**@section Public event handler */
public:
    DelegateChain<void(int32_t, int32_t)> OnMove;
    DelegateChain<void(int32_t, int32_t)> OnResize;
    DelegateChain<void()> OnMaximize;
    DelegateChain<void()> OnMinimize;
    DelegateChain<void()> OnEnterFullScreen;
    DelegateChain<void()> OnExitFullScreen;
    DelegateChain<void()> OnWillClose;
    DelegateChain<void()> OnDidClose;
    DelegateChain<void()> OnGetFocus;
    DelegateChain<void()> OnLoseFocus;
    
/**@section Private variable */
private:
    NSWindow* m_window;
    WindowDelegate* m_windowDelegate;
};
    
using PlatformWindow = MacOSWindow;

} /* namespace tgon */
