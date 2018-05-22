/**
 * @filename    MacOSApplication.h
 * @author      ggomdyu
 * @since       07/21/2017
 */

#pragma once
#include "MacOSApplicationFwd.h"

#include "../Generic/GenericApplication.h"

namespace tgon
{

class TGON_API MacOSApplication :
    public GenericApplication
{
public:
    TGON_RUNTIME_OBJECT(MacOSApplication)

/* @section Public constructor */
public:
    using GenericApplication::GenericApplication;

    explicit MacOSApplication(const WindowStyle& windowStyle);

/* @section Public destructor */
public:
    virtual ~MacOSApplication() override = default;

/* @section Public method */
public:
    virtual void MessageLoop() final override;
    virtual void Terminate() final override;
    virtual void ShowMessageBox(const char* title, const char* message, MessageBoxIcon iconType) const final override;

    void OnHandleMessage(NSEvent* message);

    using GenericApplication::ShowMessageBox;
};

} /* namespace tgon */
