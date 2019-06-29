#import "PrecompiledHeader.h"

#import <AppKit/NSScreen.h>
#import <AppKit/NSButton.h>
#import <AppKit/NSColor.h>

#import "MacOSWindowUtility.h"

#include "../WindowType.h"

namespace tgon
{

constexpr NSWindowStyleMask ConvertWindowStyleToNative(const WindowStyle& windowStyle) noexcept
{
    NSWindowStyleMask nativeWindowStyleMask = static_cast<NSWindowStyleMask>(0);
    
    if (windowStyle.hasCaption == true)
    {
        nativeWindowStyleMask |= NSWindowStyleMaskTitled;
    }
    else
    {
        nativeWindowStyleMask = NSWindowStyleMaskBorderless;
    }
    
    if (windowStyle.resizeable == true)
    {
        nativeWindowStyleMask |= NSWindowStyleMaskResizable;
    }
    
    if (windowStyle.enableSystemButton == true)
    {
        nativeWindowStyleMask |= NSWindowStyleMaskClosable | NSWindowStyleMaskMiniaturizable;
    }
    
    return nativeWindowStyleMask;
}

NSWindow* CreateNativeWindow(const WindowStyle& windowStyle)
{
    NSScreen* mainScreen = [NSScreen mainScreen];
    
    // Create a window
    NSWindow* window = [[NSWindow alloc] initWithContentRect:NSMakeRect(0.0, 0.0, 100.0, 100.0)
                                                   styleMask:ConvertWindowStyleToNative(windowStyle)
                                                     backing:NSBackingStoreBuffered
                                                       defer:NO
                                                      screen:mainScreen];
    
    // Set window attribute
    {
        [window setAcceptsMouseMovedEvents:YES];
        [window makeKeyAndOrderFront:[NSApplication sharedApplication]];
        [window setBackgroundColor:[NSColor whiteColor]];
        [window setReleasedWhenClosed:YES];
        [window setLevel:NSMainMenuWindowLevel];
        [window setTitle:[NSString stringWithUTF8String:windowStyle.title.c_str()]];
        
        if (windowStyle.enableSystemButton == false)
        {
            [[window standardWindowButton:NSWindowZoomButton] setEnabled:NO];
        }
    }

    // Set window content size
    {
        NSRect windowRect = [window frame];
        windowRect.size.width = CGFloat(windowStyle.width);
        windowRect.size.height = CGFloat(windowStyle.height);
        
        NSRect clientRect = [window frameRectForContentRect:windowRect];
        clientRect.origin.y += clientRect.size.height - CGFloat(windowStyle.height);
        
        [window setContentSize:NSMakeSize(CGFloat(clientRect.size.width), CGFloat(clientRect.size.height))];
    }
    
    // Set window position
    {
        NSRect windowRect = [window frame];
        NSRect mainScreenRect = [[NSScreen mainScreen] visibleFrame];
        
        NSPoint windowPosition;
        if (windowStyle.showMiddle == true)
        {
            windowPosition = NSMakePoint((mainScreenRect.size.width * 0.5f) - (windowRect.size.width * 0.5f), ((mainScreenRect.origin.y + mainScreenRect.size.height) * 0.5f) - (windowRect.size.height * 0.5f));
        }
        else
        {
            windowPosition = NSMakePoint(CGFloat(windowStyle.x), (mainScreenRect.origin.y + mainScreenRect.size.height - windowRect.size.height) - CGFloat(windowStyle.y));
        }
        [window setFrameOrigin:windowPosition];
    }
    
    return window;
}

} /* namespace tgon */
