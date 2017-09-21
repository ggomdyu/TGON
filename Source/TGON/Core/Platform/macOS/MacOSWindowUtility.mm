#import "PrecompiledHeader.pch"
#import "MacOSWindowUtility.h"

#import <AppKit/NSWindow.h>
#import <AppKit/NSScreen.h>
#import <AppKit/NSColor.h>

#import "Core/Platform/Base/BaseWindowType.h"

namespace tgon
{
namespace platform
{
namespace macos
{
namespace
{

void ConvertWindowStyleToNative(const WindowStyle& windowStyle, NSPoint* destWindowPosition, NSWindowStyleMask* destWindowStyleMask)
{
    *destWindowStyleMask = static_cast<NSWindowStyleMask>(0);

    // Set window position
    {
        NSRect mainScreenRect = [[NSScreen mainScreen] visibleFrame];

        if (windowStyle.showMiddle == true)
        {
            float newWindowXPos = (mainScreenRect.size.width * 0.5f) - (static_cast<CGFloat>(windowStyle.width) * 0.5f);
            float newWindowYPos = (mainScreenRect.size.height * 0.5f) - (static_cast<CGFloat>(windowStyle.height) * 0.5f);
            *destWindowPosition = NSMakePoint(newWindowXPos, newWindowYPos);
        }
        else
        {
            *destWindowPosition = NSMakePoint(windowStyle.x, windowStyle.y);
        }
    }

    // Set window style
    {
        if (windowStyle.borderless == false)
        {
            *destWindowStyleMask |= NSWindowStyleMaskTitled;

            if (windowStyle.enableSystemButton == true)
            {
                *destWindowStyleMask |= NSWindowStyleMaskClosable | NSWindowStyleMaskMiniaturizable;
            }
        }

        if (windowStyle.resizeable == true)
        {
            *destWindowStyleMask |= NSWindowStyleMaskResizable;
        }
    }
}

} /* namespace */

NSWindow* CreateNativeWindow(const WindowStyle& windowStyle)
{
    NSWindowStyleMask windowStyleMask;
    NSPoint windowPosition;
    ConvertWindowStyleToNative(windowStyle, &windowPosition, &windowStyleMask);

    NSScreen* mainScreen = [NSScreen mainScreen];

    NSWindow* window = [NSWindow alloc];
    [window initWithContentRect:NSMakeRect(0, 0, static_cast<CGFloat>(windowStyle.width), static_cast<CGFloat>(windowStyle.height))
                      styleMask:windowStyleMask
                        backing:NSBackingStoreBuffered
                          defer:NO
                         screen:mainScreen];
    [window setAcceptsMouseMovedEvents:YES];
    [window makeKeyAndOrderFront:nil];
    [window setTitle:[NSString stringWithUTF8String:windowStyle.caption.c_str()]];
    [window setBackgroundColor:[NSColor whiteColor]];
    [window setLevel:NSMainMenuWindowLevel + 1];

    NSRect mainScreenRect = [mainScreen visibleFrame];
    NSRect currentWindowFrameRect = [window frame];
    [window setFrameOrigin:NSMakePoint(windowPosition.x,(mainScreenRect.origin.y + mainScreenRect.size.height - currentWindowFrameRect.size.height) - windowPosition.y)];
    
    return window;
}

} /* namespace macos */
} /* namespace platform */
} /* namespace tgon */
