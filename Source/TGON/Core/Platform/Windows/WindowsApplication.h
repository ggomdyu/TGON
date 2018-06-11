/**
 * @filename    WindowsApplication.h
 * @author      ggomdyu
 * @since       02/13/2018
 */

#pragma once
#include "WindowsApplicationType.h"

namespace tgon
{

class TGON_API ApplicationImpl final
{
/* @section Public constructor */
public:
    ApplicationImpl();

/* @section Public method */
public:
    /* @brief                       Loops the message queue and handle the message. */
    template <typename _FunctionType>
    void MessageLoop(const _FunctionType& onUpdate);

    /* @brief                       Terminates the program forcibly. */
    void Terminate();

    /**
     * @brief                       Shows a message box in front of screen.
     * @param [in] title            The message what you want to show in title area.
     * @param [in] message          The message what you want to show in description area.
     * @param [in] messageBoxIcon   The type of icon in message box.
     */
    void ShowMessageBox(const char* title, const char* message, MessageBoxIcon messageBoxIcon) const;

/* @section Private event handler */
private:
    static LRESULT CALLBACK OnHandleMessage(HWND wndHandle, UINT message, WPARAM wParam, LPARAM lParam);

/* @section Public method */
private:
    /* @brief   Register default WNDCLASS to window class table. */
    bool RegisterWindowClass();
};

template <typename _FunctionType>
inline void ApplicationImpl::MessageLoop(const _FunctionType& onUpdate)
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
