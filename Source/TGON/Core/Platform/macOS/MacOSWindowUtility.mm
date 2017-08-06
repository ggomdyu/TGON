#include "PrecompiledHeader.pch"
#include "MacOSWindowUtility.h"

#include "MacOSWindow.h"

namespace tgon
{
namespace platform
{
namespace macos
{

void ConvertToNativeWindowStyle(const WindowStyle& windowStyle, NSPoint* destWindowPosition, NSWindowStyleMask* destWindowStyleMask)
{
    *destWindowStyleMask = static_cast<NSWindowStyleMask>(0);

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

    if (windowStyle.showMiddle == true)
    {
        NSRect mainScreenFrameRect = [[NSScreen mainScreen] visibleFrame];

        float newWindowXPos = (mainScreenFrameRect.size.width * 0.5f) - (static_cast<CGFloat>(windowStyle.width) * 0.5f);
        float newWindowYPos = (mainScreenFrameRect.size.height * 0.5f) - (static_cast<CGFloat>(windowStyle.height) * 0.5f);
        *destWindowPosition = NSMakePoint(newWindowXPos, newWindowYPos);
    }
    else
    {
        *destWindowPosition = NSMakePoint(windowStyle.x, windowStyle.y);
    }
}

NSWindow* CreateNativeWindow(const WindowStyle& windowStyle)
{
    NSWindowStyleMask windowStyleMask;
    NSPoint windowPosition;
    ConvertToNativeWindowStyle(windowStyle, &windowPosition, &windowStyleMask);

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
    [window setLevel:NSMainMenuWindowLevel];

    NSRect mainScreenFrameRect = [mainScreen visibleFrame];
    NSRect currentWindowFrameRect = [window frame];
    [window setFrameOrigin:NSMakePoint(windowPosition.x,(mainScreenFrameRect.origin.y + mainScreenFrameRect.size.height - currentWindowFrameRect.size.height) - windowPosition.y)];

    return window;
}

} /* namespace macos */
} /* namespace platform */
} /* namespace tgon */
