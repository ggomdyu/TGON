#import "PrecompiledHeader.pch"
#import "MacOSApplication.h"

#import <AppKit/NSAlert.h>

namespace tgon
{
namespace platform
{
namespace macos
{

void MacOSApplication::ShowMessageBox(const char* title, const char* message, MessageBoxType messageBoxType)
{
    static constexpr const NSAlertStyle nativeNSAlertStyleArray[3] =
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

} /* namespace macos */
} /* namespace platform */
} /* namespace tgon */