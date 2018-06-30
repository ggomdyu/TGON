#import "PrecompiledHeader.h"

#import "MacOSApplication.h"

namespace tgon
{

void ApplicationImpl::ShowMessageBox(const char* title, const char* message, MessageBoxIcon messageBoxIcon) const
{
    NSAlert *alert = [[NSAlert alloc] init];
    [alert setMessageText:[NSString stringWithUTF8String:title]];
    [alert setInformativeText:[NSString stringWithUTF8String:message]];
    
    if (messageBoxIcon != MessageBoxIcon::No)
    {
        [alert setAlertStyle:static_cast<NSAlertStyle>(messageBoxIcon)];
    }

    [alert runModal];
}

void ApplicationImpl::Terminate()
{
    [NSApp terminate:nil];
}

void ApplicationImpl::OnHandleMessage(NSEvent* event)
{
    NSEventType eventType = [event type];
    switch (eventType)
    {
    default:
        [NSApp sendEvent:event];
        break;
    }
}

} /* namespace tgon */
