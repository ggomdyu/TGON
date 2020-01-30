/**
 * @file    Window.h
 * @author  ggomdyu
 * @since   02/15/2018
 * @brief   The platform agnostic window class implementation.
 */

#pragma once
#include "Core/DelegateChain.h"
#include "Math/Extent.h"
#include "Math/Vector2.h"

#if TGON_PLATFORM_WINDOWS
#   include "Windows/WindowsWindow.h"
#elif TGON_PLATFORM_MACOS
#   include "MacOS/MacOSWindow.h"
#elif TGON_PLATFORM_ANDROID
#   include "Android/AndroidWindow.h"
#elif TGON_PLATFORM_IOS
#   include "IOS/IOSWindow.h"
#endif

#include "WindowStyle.h"

namespace tgon
{

class Window final :
    private PlatformWindow
{
/**@section Constructor */
public:
    explicit Window(const WindowStyle& windowStyle);
    Window(Window&& rhs) noexcept = default;

/**@section Destructor */
public:
    ~Window();

/**@section Operator */
public:
    bool operator==(const Window& rhs) const noexcept;
    bool operator!=(const Window& rhs) const noexcept;
    Window& operator=(Window&& rhs) noexcept = default;

/**@section Method */
public:
    PlatformWindow& GetPlatformDependency() noexcept;
    const PlatformWindow& GetPlatformDependency() const noexcept;
    void Show();
    void Hide();
    void Close();
    void Maximize();
    void Minimize();
    void BringToFront();
    void Flash();
    void SetPosition(int32_t x, int32_t y);
    void SetContentSize(int32_t width, int32_t height);
    void SetTitle(const char* title);
    void SetTopMost(bool setTopMost);
    void SetTransparency(float transparency);
    void GetPosition(int32_t* x, int32_t* y) const;
    I32Vector2 GetPosition() const;
    void GetWindowSize(int32_t* destWidth, int32_t* destHeight) const;
    I32Extent2D GetWindowSize() const;
    void GetClientSize(int32_t* width, int32_t* height) const;
    I32Extent2D GetClientSize() const;
    int32_t GetTitle(char* destTitle, int32_t destTitleBufferLen) const;
    std::string GetTitle() const;
    float GetTransparency() const;
    void* GetNativeWindow() const;
    bool HasCaption() const;
    bool IsResizable() const;
    bool IsMaximized() const;
    bool IsMinimized() const;
    bool IsTopMost() const;

/**@section Event handler */
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
};

} /* namespace tgon */
