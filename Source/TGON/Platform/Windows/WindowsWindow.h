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
#    define NOMINMAX
#endif
#include <Windows.h>

#include "Core/NonCopyable.h"

namespace tgon
{

class TGON_API WindowsWindow :
    private NonCopyable
{
/**@section Constructor */
protected:
    explicit WindowsWindow(HWND wndHandle) noexcept;
    WindowsWindow(WindowsWindow&& rhs) noexcept;

/**@section Operator */
public:
    WindowsWindow& operator=(WindowsWindow&& rhs) noexcept;

/**@section Method */
public:
    void SetRawWindowStyle(DWORD rawWindowStyle);
    void SetRawWindowStyleEx(DWORD rawWindowStyleEx);
    LONG_PTR GetRawWindowStyle() const;
    LONG_PTR GetRawWindowStyleEx() const;

private:
    void SetUserData(void* data);

/**@section Event handler */
public:
    LRESULT OnHandleMessage(HWND wndHandle, UINT msg, WPARAM wParam, LPARAM lParam);

/**@section Variable */
protected:
    HWND m_wndHandle;
};

using PlatformWindow = WindowsWindow;

} /* namespace tgon */