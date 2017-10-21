#import "PrecompiledHeader.pch"
#import "MacOSApplication.h"

#import <AppKit/NSAlert.h>

#import "Core/Platform/MacOS/MacOSWindow.h"
#import "Core/Platform/Base/BaseWindowType.h"

namespace tgon
{
namespace platform
{
namespace macos
{

void MacOSApplication::InitWithWindowStyle(const WindowStyle& windowStyle)
{
    m_mainWindow = std::make_shared<MacOSWindow>(windowStyle);
}

void MacOSApplication::ShowMessageBox(const char* title, const char* message, MessageBoxType messageBoxType)
{
    static constexpr const NSAlertStyle nativeNSAlertStyleArray[2] =
    {
        NSAlertStyleInformational,
        NSAlertStyleCritical,
    };

    NSAlert *alert = [[NSAlert alloc] init];
    [alert setMessageText:[NSString stringWithUTF8String:title]];
    [alert setInformativeText:[NSString stringWithUTF8String:message]];
    [alert setAlertStyle:nativeNSAlertStyleArray[static_cast<int32_t>(messageBoxType)]];
    [alert runModal];
}

void MacOSApplication::Terminate()
{
    [NSApp terminate:nil];
}

} /* namespace macos */
} /* namespace platform */
} /* namespace tgon */
