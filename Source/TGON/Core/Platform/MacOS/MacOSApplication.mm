#import "PrecompiledHeader.h"

#import <AppKit/NSAlert.h>
#import <AppKit/NSEvent.h>
#import <AppKit/NSApplication.h>

#import "../Generic/GenericApplicationType.h"

#import "MacOSWindow.h"
#import "MacOSApplication.h"

namespace tgon
{

MacOSApplication::MacOSApplication(const WindowStyle& windowStyle) :
    GenericApplication(std::make_shared<MacOSWindow>(windowStyle))
{
}

void MacOSApplication::MessageLoop()
{
    NSEvent* event = nil;
    while (true)
    {
        while((event = [NSApp nextEventMatchingMask:NSEventMaskAny
                                            untilDate:nil
                                               inMode:NSDefaultRunLoopMode
                                              dequeue:YES]) != nil)
        {
            this->OnHandleMessage(event);
        }

        this->OnUpdate();
    }
}

void MacOSApplication::ShowMessageBox(const char* title, const char* message, MessageBoxIcon iconType) const
{
    static constexpr const NSAlertStyle nativeNSAlertStyleArray[2] =
    {
        NSAlertStyleInformational,
        NSAlertStyleCritical,
    };

    NSAlert *alert = [[NSAlert alloc] init];
    [alert setMessageText:[NSString stringWithUTF8String:title]];
    [alert setInformativeText:[NSString stringWithUTF8String:message]];
    [alert setAlertStyle:nativeNSAlertStyleArray[static_cast<int32_t>(iconType)]];
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
        [NSApp sendEvent:message];
        break;
    }
}

} /* namespace tgon */
