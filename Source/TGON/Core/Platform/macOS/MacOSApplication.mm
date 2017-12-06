#import "PrecompiledHeader.pch"
#import "MacOSApplication.h"

#import <AppKit/NSAlert.h>
#import <AppKit/NSEvent.h>
#import <AppKit/NSApplication.h>

namespace tgon
{
namespace platform
{
namespace macos
{

void MacOSApplication::MessageLoop()
{
    NSEvent* message = nil;
    while (true)
    {
        while (message = [NSApp nextEventMatchingMask:NSEventMaskAny
                                            untilDate:nil
                                               inMode:NSDefaultRunLoopMode
                                              dequeue:YES])
        {
            this->OnHandleMessage(message);
        }

        this->OnUpdate();
    }
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

void MacOSApplication::OnHandleMessage(NSEvent* message)
{
    NSEventType messageType = [message type];
    switch (messageType)
    {
    default:
        [NSApp sendEvent: message];
        break;
    }
}

} /* namespace macos */
} /* namespace platform */
} /* namespace tgon */
