/**
 * @file    WindowsApplication.h
 * @author  ggomdyu
 * @since   02/13/2018
 */

#pragma once
#ifndef WIN32_LEAN_AND_MEAN
#    define WIN32_LEAN_AND_MEAN
#endif
#include <Windows.h>
#include <thread>
#include <boost/noncopyable.hpp>

#include "Core/Object/CoreObject.h"

#include "../ApplicationType.h"

namespace tgon
{

class TGON_API WindowsApplication :
    public CoreObject
{
public:
    TGON_DECLARE_RTTI(WindowsApplication);

/**@section Constructor */
public:
    WindowsApplication();

/**@section Method */
public:
    /**@brief   Processes the message stacked in queue. */
    template <typename _FunctionType>
    void MessageLoop(const _FunctionType& onUpdate);

    /**@brief   Terminates the program forcibly. */
    void Terminate();

    /**
     * @brief   Displays a message box.
     * @param [in] title            The message to show in title area.
     * @param [in] message          The message to show in description area.
     * @param [in] messageBoxIcon   The type of icon appears in the message box.
     */
    void ShowMessageBox(const char* title, const char* message, MessageBoxIcon messageBoxIcon) const;

    /**@brief   Enables a crash handler which handled when the crash ocurred. 
     * @warn    You can not disable this function after invoked this.
     * @todo    I think it should be moved to Debug.h
     */
    void EnableCrashHandler();

/**@section Event Handler */
private:
    static LRESULT CALLBACK OnHandleMessage(HWND wndHandle, UINT message, WPARAM wParam, LPARAM lParam);

private:
    /**@brief   Register default WNDCLASS to window class table. */
    bool RegisterWindowClass();

/**@section Variable */
private:
    bool m_doCrashReport;
};

using PlatformApplication = WindowsApplication;

template <typename _FunctionType>
inline void WindowsApplication::MessageLoop(const _FunctionType& onUpdate)
{
    MSG msg {};
    while (msg.message != WM_QUIT)
    {
        if (PeekMessageW(&msg, nullptr, 0, 0, PM_REMOVE) == TRUE)
        {
            ::DispatchMessageW(&msg);
        }
        else
        {
            onUpdate();
        }
    }
}

} /* namespace tgon */                               