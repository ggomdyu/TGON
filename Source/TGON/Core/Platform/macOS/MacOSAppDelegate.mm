#import "PrecompiledHeader.pch"
#import "MacOSAppDelegate.h"

#import <memory>
#import <AppKit/NSOpenGLView.h>
#import <QuartzCore/CVDisplayLink.h>

#import "Core/Platform/MacOS/MacOSApplication.h"

namespace tgon
{
namespace platform
{

extern std::shared_ptr<BaseApplication> MakeApplication();

} /* namespace platform */
} /* namespace tgon */

namespace
{

std::shared_ptr<tgon::platform::macos::MacOSApplication> g_application;

CVReturn DisplayLinkCallback(CVDisplayLinkRef displayLink, const CVTimeStamp* now, const CVTimeStamp* outputTime, CVOptionFlags flagsIn, CVOptionFlags* flagsOut, void* displayLinkContext)
{
    // There is no autorelease pool when this method is called
    // because it will be called from a background thread.
    // It's important to create one or app can leak objects.
    @autoreleasepool
    {
        g_application->OnUpdate();
        g_application->OnDraw();
    }
    return kCVReturnSuccess;
}

} /* namespace */

@implementation MacOSAppDelegate
- (void)InitializeDisplayLink
{
    // Create a display link capable of being used with all active displays
    CVDisplayLinkCreateWithActiveCGDisplays(&_displayLink);

    // Set the update callback function
    CVDisplayLinkSetOutputCallback(_displayLink, &DisplayLinkCallback, (__bridge void*)self);
}

- (void)StartDisplayLink
{
    CVDisplayLinkStart(_displayLink);
}

- (void)StopDisplayLink
{
    CVDisplayLinkStop(_displayLink);
}

- (void)applicationWillFinishLaunching:(NSNotification*)aNotification
{
    using namespace tgon::platform;

    g_application = std::static_pointer_cast<macos::MacOSApplication>(MakeApplication());

    [self InitializeDisplayLink];
    [self StartDisplayLink];
}

- (void)applicationWillTerminate:(NSNotification*)aNotification
{
    g_application->OnTerminate();

    [self StopDisplayLink];
}
//
//- (void)OnUpdate
//{
//    g_application->OnUpdate();
//    g_application->OnDraw();
//}
@end
