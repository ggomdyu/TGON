/**
 * @filename    WindowsWindow.h
 * @author      ggomdyu
 * @since       01/09/2016
 * @brief       The platform specific window class implementation.
 */

#pragma once
#ifndef WIN32_LEAN_AND_MEAN
#    define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>
#include <boost/noncopyable.hpp>

#include "Core/Platform/Config.h"

namespace tgon
{

class Window;
struct WindowStyle;

class WindowImpl final :
    private boost::noncopyable
{
/* @section Public constructor */
public:
    WindowImpl(Window* owner);
    WindowImpl(Window* owner, const WindowStyle& windowStyle);

/* @section Public method */
public:
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

/* @section Public event handler */
public:
    LRESULT OnHandleMessage(HWND wndHandle, UINT msg, WPARAM wParam, LPARAM lParam);

/* @section Private method */
private:
    void SetUserData(void* data);

/* @section Private variable */
private:
    Window* m_owner;

    HWND m_wndHandle;
    bool m_isDwmCompositionEnabled;
};

} /* namespace tgon */