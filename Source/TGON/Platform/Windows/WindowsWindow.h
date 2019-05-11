/**
 * @file    WindowsWindow.h
 * @author  ggomdyu
 * @since   01/09/2016
 * @brief   The platform specific window class implementation.
 */

#pragma once
#ifndef WIN32_LEAN_AND_MEAN
#    define WIN32_LEAN_AND_MEAN
#endif
#ifndef NOMINMAX
#	define NOMINMAX
#endif
#include <Windows.h>
#include <boost/noncopyable.hpp>

#include "Platform/Config.h"
#include "Core/DelegateChain.h"

#include "../WindowType.h"

namespace tgon
{

class TGON_API WindowsWindow :
    private boost::noncopyable
{
/**@section Constructor */
public:
    explicit WindowsWindow(const WindowStyle& windowStyle);

/**@section Method */
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
    void SetRawWindowStyle(DWORD rawWindowStyle);
    void SetRawWindowStyleEx(DWORD rawWindowStyleEx);
    LONG_PTR GetRawWindowStyle() const;
    LONG_PTR GetRawWindowStyleEx() const;

private:
    void SetUserData(void* data);

/**@section Event handler */
public:
    LRESULT OnHandleMessage(HWND wndHandle, UINT msg, WPARAM wParam, LPARAM lParam);

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

/**@section Variable */
private:
    HWND m_wndHandle;
    bool m_isDwmCompositionEnabled;
};

using PlatformWindow = WindowsWindow;

} /* namespace tgon */
