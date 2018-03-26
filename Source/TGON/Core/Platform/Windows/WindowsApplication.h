/**
 * @filename    WindowsApplication.h
 * @author      ggomdyu
 * @since       02/13/2018
 */

#pragma once
#include "../Generic/GenericApplication.h"

#include "WindowsApplicationFwd.h"

namespace tgon
{

class TGON_API WindowsApplication :
    public GenericApplication
{
public:
    TGON_RUNTIME_OBJECT(WindowsApplication)

/* @section Public constructor */
public:
    WindowsApplication() = default;
    explicit WindowsApplication(const WindowStyle& windowStyle);

/* @section Public destructor */
public:
    virtual ~WindowsApplication() override = default;

/* @section Public method */
public:
    virtual void MessageLoop() final override;
    virtual void Terminate() final override;
    virtual void ShowMessageBox(const char* title, const char* message, MessageBoxIconType iconType) const final override;

    static LRESULT CALLBACK OnHandleMessage(HWND wndHandle, UINT message, WPARAM wParam, LPARAM lParam);

    using GenericApplication::ShowMessageBox;
};

} /* namespace tgon */