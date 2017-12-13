/**
 * @filename    Window.h
 * @author      ggomdyu
 * @since       01/09/2016
 * @brief       The platform-agnostic Window class.
 */

#pragma once
#include <boost/predef/os.h>
#include <boost/noncopyable.hpp>
#include <string>
#include <cstdint>

#if BOOST_OS_WINDOWS
#   ifndef WIN32_LEAN_AND_MEAN
#       define WIN32_LEAN_AND_MEAN
#   endif
#   include <Windows.h>
#elif BOOST_OS_ANDROID
#elif BOOST_OS_IOS
#endif

#include "Config.h"

#if BOOST_OS_MACOS
@class NSWindow;
@class WindowDelegate;
#endif

namespace tgon
{
namespace platform
{

class TGON_API Window :
    private boost::noncopyable
{
/* @section Public constructor */
public:
    Window() = default;
    explicit Window(const struct WindowStyle& windowStyle);
    Window(Window&& rhs);

/* @section Public operator */
public:
    Window& operator=(Window&& rhs);

/* @section Public destructor */
public:
    virtual ~Window();

/* @section Public method */
public:
    void Initialize(const struct WindowStyle& windowStyle);

    void Show();
    void Hide();
    void Close();
    void Maximize();
    void Minimize();
    void BringToFront();
    void Flash();

    void SetPosition(int32_t x, int32_t y);
    void SetSize(int32_t width, int32_t height);
    void SetTitle(const char* title);
    void SetFullScreen(bool isFullScreen);
    void SetTopMost(bool setTopMost);
    void GetPosition(int32_t* x, int32_t* y) const;
    void GetSize(int32_t* width, int32_t* height) const;
    void GetTitle(char* destCaptionTitle) const;
    void* GetNativeWindow() noexcept;
    bool HasCaption() const;
    bool IsResizable() const;
    bool IsMaximized() const;
    bool IsMinimized() const;
    bool IsTopMost() const;
    bool IsClosed() const noexcept;

#if BOOST_OS_WINDOWS
    LRESULT OnHandleMessage(HWND wndHandle, UINT msg, WPARAM wParam, LPARAM lParam);
#elif BOOST_OS_MACOS
#endif

    virtual void OnMove(int32_t x, int32_t y) {}
    virtual void OnResize(int32_t width, int32_t height) {}
    virtual void OnMaximize() {}
    virtual void OnMinimize() {}
    virtual void OnEnterFullScreen() {}
    virtual void OnExitFullScreen() {}
    virtual void OnGetFocus() {}
    virtual void OnLoseFocus() {}

/* @section Protected variable */
protected:
    bool m_isClosed;

#if BOOST_OS_WINDOWS
    HWND m_wndHandle;
#elif BOOST_OS_MACOS
    NSWindow* m_nsWindow;
    WindowDelegate* m_windowDelegate;
#elif BOOST_OS_ANDROID
#elif BOOST_OS_IOS
#endif
};

} /* namespace platform */
} /* namespace tgon */