/**
 * @file    MacOSApplication.h
 * @author  ggomdyu
 * @since   07/21/2017
 */

#pragma once
#import <AppKit/NSEvent.h>
#import <AppKit/NSApplication.h>

#import "Core/Platform/Config.h"
#import "Core/Object/CoreObject.h"

#import "MacOSApplicationType.h"

namespace tgon
{

class TGON_API MacOSApplication :
    public CoreObject
{
public:
    TGON_DECLARE_RTTI(MacOSApplication);
        
/**@section Public destructor */
public:
    virtual ~MacOSApplication() = default;
        
/**@section Public method */
public:
    template <typename _FunctionType>
    void MessageLoop(const _FunctionType& onUpdate);
    
    void Terminate();
    
    void ShowMessageBox(const char* title, const char* message, MessageBoxIcon messageBoxIcon) const;
    
/**@section Public event handler */
public:
    void OnHandleMessage(NSEvent* message);
};

using PlatformApplication = MacOSApplication;
    
template <typename _FunctionType>
inline void MacOSApplication::MessageLoop(const _FunctionType& onUpdate)
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
        
        onUpdate();
    }
}

} /* namespace tgon */
