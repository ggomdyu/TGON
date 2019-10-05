/**
 * @file    Window.h
 * @author  ggomdyu
 * @since   02/15/2018
 * @brief   The platform agnostic window class implementation.
 */

#pragma once
#include "Platform/Config.h"
#include "Core/DelegateChain.h"
#include "Math/Point.h"
#include "Math/Extent.h"

#if TGON_PLATFORM_WINDOWS
#   include "Windows/WindowsWindow.h"
#elif TGON_PLATFORM_MACOS
#   include "MacOS/MacOSWindow.h"
#elif TGON_PLATFORM_ANDROID
#   include "Android/AndroidWindow.h"
#elif TGON_PLATFORM_IOS
#   include "IOS/IOSWindow.h"
#endif

namespace tgon
{

struct WindowStyle final
{
    std::string title = u8"Thousand Party";

    int32_t x = 100;
    int32_t y = 100;
    int32_t width = 838;
    int32_t height = 441;

    bool hasCaption = true;
    bool enableSystemButton = true;
    bool enableFullScreen = false;
    bool resizeable = true;
    bool topMost = false;
    bool showMiddle = true;
};

class TGON_API Window final :
    private PlatformWindow
{
/**@section Constructor */
public:
    explicit Window(const WindowStyle& windowStyle);
    Window(Window&& rhs) noexcept;

/**@section Destructor */
public:
    ~Window();

/**@section Operator */
public:
    bool operator==(const Window& rhs) const noexcept;
    bool operator!=(const Window& rhs) const noexcept;
    Window& operator=(Window&& rhs) noexcept;

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
    void SetTitle(const std::string_view& title);
    void SetTopMost(bool setTopMost);
    void SetTransparency(float transparency);
    void GetPosition(int32_t* x, int32_t* y) const;
    I32Point GetPosition() const;
    void GetExtent(int32_t* width, int32_t* height) const;
    I32Extent2D GetExtent() const;
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
