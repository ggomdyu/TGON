/**
 * @file    MacOSApplication.h
 * @author  ggomdyu
 * @since   07/21/2017
 */

#pragma once
#import <AppKit/NSEvent.h>
#import <AppKit/NSApplication.h>
#import <string_view>

#import "Platform/Config.h"

#import "MacOSApplicationType.h"

namespace tgon
{

class TGON_API MacOSApplication
{
/**@section Public destructor */
public:
    virtual ~MacOSApplication() = default;
        
/**@section Public method */
public:
    template <typename _FunctionType>
    void MessageLoop(const _FunctionType& onUpdateFrame);
    void Terminate();
    void ShowMessageBox(const std::string_view& title, const std::string_view& message, MessageBoxIcon messageBoxIcon) const;
    void EnableCrashHandler() {}
    
/**@section Public event handler */
public:
    void OnHandleMessage(NSEvent* message);
};

using PlatformApplication = MacOSApplication;
    
template <typename _FunctionType>
inline void MacOSApplication::MessageLoop(const _FunctionType& onUpdateFrame)
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
        
        onUpdateFrame();
    }
}

} /* namespace tgon */
