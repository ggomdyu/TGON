#import "PrecompiledHeader.h"

#import <AppKit/NSScreen.h>
#import <AppKit/NSButton.h>
#import <AppKit/NSColor.h>

#import "MacOSWindowUtility.h"

namespace tgon
{

NSWindow* MacOSWindowUtility::CreateNativeWindow(const WindowStyle& windowStyle)
{
    NSScreen* mainScreen = [NSScreen mainScreen];
    NSRect mainScreenRect = [mainScreen visibleFrame];
    
    NSPoint windowPosition;
    if (windowStyle.showMiddle == true)
    {
        windowPosition = NSMakePoint((mainScreenRect.size.width * 0.5f) - (static_cast<CGFloat>(windowStyle.width) * 0.5f), ((mainScreenRect.origin.y + mainScreenRect.size.height) * 0.5f) - (static_cast<CGFloat>(windowStyle.height) * 0.5f));
    }
    else
    {
        // Convert coordinates that (0, 0) to be the left top side.
        windowPosition = NSMakePoint(windowStyle.x, (mainScreenRect.origin.y + mainScreenRect.size.height) - (windowStyle.height + windowStyle.y));
    }

    NSWindow* window = [[NSWindow alloc] initWithContentRect:NSMakeRect(windowPosition.x, windowPosition.y, static_cast<CGFloat>(windowStyle.width), static_cast<CGFloat>(windowStyle.height))
                                                   styleMask:ConvertWindowStyleToMask(windowStyle)
                                                     backing:NSBackingStoreBuffered
                                                       defer:NO
                                                      screen:mainScreen];
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

    return window;
}
    
NSWindowStyleMask MacOSWindowUtility::ConvertWindowStyleToMask(const WindowStyle& windowStyle)
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

} /* namespace tgon */
