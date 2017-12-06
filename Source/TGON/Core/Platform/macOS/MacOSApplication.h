/**
 * @filename    MacOSApplication.h
 * @author      ggomdyu
 * @since       09/22/2017
 */

#pragma once
#import "Core/Platform/Base/BaseApplication.h"

#import "MacOSApplicationFwd.h"

namespace tgon
{
namespace platform
{
namespace macos
{

class TGON_API MacOSApplication :
    public BaseApplication
{
/* @section public constructor */
public:
    using BaseApplication::BaseApplication;

/* @section public destructor */
public:
    virtual ~MacOSApplication() = default;

/* @section public method */
public:
    virtual void MessageLoop() override;

    virtual void ShowMessageBox(const char* title, const char* message, MessageBoxType messageBoxType) override;
    virtual void Terminate() override;

private:
    void OnHandleMessage(NSEvent* message);
};

} /* namespace macos */

using Application = macos::MacOSApplication;

} /* namespace platform */
} /* namespace tgon */
