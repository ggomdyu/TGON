#import "PrecompiledHeader.pch"
#import "../Application.h"
#import "../ApplicationType.h"

#import <AppKit/NSAlert.h>
#import <AppKit/NSEvent.h>
#import <AppKit/NSApplication.h>

#include "../Window.h"

namespace tgon
{
namespace platform
{

Application::Application(const WindowStyle& windowStyle) :
    m_mainWindow(std::make_shared<Window>(windowStyle))
{
}

void Application::Initialize(const WindowStyle& windowStyle)
{
    new (this) Application(windowStyle);
}

void Application::MessageLoop()
{
    NSEvent* message = nil;
    while (true)
    {
        while((message = [NSApp nextEventMatchingMask:NSEventMaskAny
                                            untilDate:nil
                                               inMode:NSDefaultRunLoopMode
                                              dequeue:YES]) != nil)
        {
            this->OnHandleMessage(message);
        }

        this->OnUpdate();
    }
}

void Application::ShowMessageBox(const char* title, const char* message, MessageBoxIconType iconType) const
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

void Application::Terminate()
{
    [NSApp terminate:nil];
}

void Application::OnHandleMessage(NSEvent* message)
{
    NSEventType messageType = [message type];
    switch (messageType)
    {
        default:
            [NSApp sendEvent:message];
            break;
    }
}

} /* namespace platform */
} /* namespace tgon */
