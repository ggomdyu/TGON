/**
 * @filename    GenericApplication.h
 * @author      ggomdyu
 * @since       04/01/2016
 * @brief       The abstracted application class which is Plaform-agnostic.
 */

#pragma once
#include "MacOSApplicationFwd.h"

#include "../Generic/GenericApplication.h"

namespace tgon
{
namespace core
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
    virtual void ShowMessageBox(const char* title, const char* message, MessageBoxIconType iconType) const final override;

    void OnHandleMessage(NSEvent* message);

    using GenericApplication::ShowMessageBox;
};

} /* namespace core */
} /* namespace tgon */
