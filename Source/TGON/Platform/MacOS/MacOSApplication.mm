#import "PrecompiledHeader.h"

#import <AppKit/NSAlert.h>

#import "../Application.h"

namespace tgon
{
namespace
{
    
constexpr NSAlertStyle ConvertMessageBoxIconToNative(MessageBoxIcon messageBoxIcon) noexcept
{
    constexpr NSAlertStyle nativeMessageBoxIcons[] = {
        NSAlertStyle(-1),
        NSAlertStyleInformational,
        NSAlertStyleCritical,
    };
    
    return nativeMessageBoxIcons[static_cast<int32_t>(messageBoxIcon)];
}

void OnHandleMessage(NSEvent* event)
{
    NSEventType eventType = [event type];
    switch (eventType)
    {
    case NSEventTypeKeyDown:
    case NSEventTypeKeyUp:
        break;
        
    default:
        [NSApp sendEvent:event];
        break;
    }
}

} /* namespace */

void Application::ShowMessageBox(const std::string_view& title, const std::string_view& message, MessageBoxIcon messageBoxIcon)
{
    NSAlert *alert = [[NSAlert alloc] init];
    [alert setMessageText:[NSString stringWithUTF8String:title.data()]];
    [alert setInformativeText:[NSString stringWithUTF8String:message.data()]];
    
    if (messageBoxIcon != MessageBoxIcon::No)
    {
        [alert setAlertStyle:ConvertMessageBoxIconToNative(messageBoxIcon)];
    }

    [alert runModal];
}

void Application::Terminate()
{
    [NSApp terminate:nil];
}
    
void Application::MessageLoop()
{
    NSEvent* event = nil;
    while (true)
    {
        while((event = [NSApp nextEventMatchingMask:NSEventMaskAny
                                          untilDate:nil
                                             inMode:NSDefaultRunLoopMode
                                            dequeue:YES]) != nil)
        {
            OnHandleMessage(event);
        }
        
        m_engine->Update();
    }
}

} /* namespace tgon */
