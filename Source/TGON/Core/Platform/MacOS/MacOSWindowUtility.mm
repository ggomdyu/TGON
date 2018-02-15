#import "PrecompiledHeader.pch"

#import "MacOSWindowUtility.h"

#import "../WindowType.h"

#import <AppKit/NSWindow.h>
#import <AppKit/NSScreen.h>
#import <AppKit/NSButton.h>
#import <AppKit/NSColor.h>

namespace tgon
{
namespace core
{
namespace
{

void PreApplyWindowStyle(const WindowStyle& windowStyle, NSWindow* applyTargetWindow)
{
    NSWindowStyleMask nativeWindowStyleMask = static_cast<NSWindowStyleMask>(0);

    // Set window style
    {
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
    }

    // Set window rect
    {
        NSScreen* mainScreen = [NSScreen mainScreen];
        NSRect mainScreenRect = [mainScreen visibleFrame];
        
        NSPoint newWindowPosition = (windowStyle.showMiddle == true) ? NSMakePoint(
            (mainScreenRect.size.width * 0.5f) - (static_cast<CGFloat>(windowStyle.width) * 0.5f),
            (mainScreenRect.size.height * 0.5f) - (static_cast<CGFloat>(windowStyle.height) * 0.5f)) :
        NSMakePoint(windowStyle.x, windowStyle.y);
        
        NSRect currentWindowFrameRect = [applyTargetWindow frame];
        [applyTargetWindow setFrameOrigin:NSMakePoint(newWindowPosition.x,(mainScreenRect.origin.y + mainScreenRect.size.height - currentWindowFrameRect.size.height) - newWindowPosition.y)];
    }

    // Set window title
    {
        [applyTargetWindow setTitle:[NSString stringWithUTF8String:windowStyle.title.c_str()]];
    }

    [applyTargetWindow setStyleMask:nativeWindowStyleMask];
}

void PostApplyWindowStyle(const WindowStyle& windowStyle, NSWindow* applyTargetWindow)
{
    if (windowStyle.enableSystemButton == false)
    {
        [[applyTargetWindow standardWindowButton:NSWindowZoomButton] setEnabled:NO];
    }
}

} /* namespace */

NSWindow* MakeNativeWindow(const WindowStyle& windowStyle)
{
    NSScreen* mainScreen = [NSScreen mainScreen];

    NSWindow* window = [[NSWindow alloc] initWithContentRect:NSMakeRect(0, 0, static_cast<CGFloat>(windowStyle.width), static_cast<CGFloat>(windowStyle.height))
                                                   styleMask:NSWindowStyleMaskTitled
                                                     backing:NSBackingStoreBuffered
                                                       defer:NO
                                                      screen:mainScreen];
    [window setAcceptsMouseMovedEvents:YES];
    [window makeKeyAndOrderFront:[NSApplication sharedApplication]];
    [window setBackgroundColor:[NSColor whiteColor]];
    [window setReleasedWhenClosed:YES];
    [window setLevel:NSMainMenuWindowLevel];

    PreApplyWindowStyle(windowStyle, window);
    PostApplyWindowStyle(windowStyle, window);

    return window;
}

} /* namespace core */
} /* namespace tgon */
