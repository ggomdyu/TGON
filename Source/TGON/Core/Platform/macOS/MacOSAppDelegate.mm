#import "PrecompiledHeader.pch"
#import "MacOSAppDelegate.h"

#import <memory>
#import <AppKit/NSOpenGLView.h>
#import <QuartzCore/CVDisplayLink.h>

#import "MacOSApplication.h"

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
    ::CVDisplayLinkCreateWithActiveCGDisplays(&_displayLink);

    // Set the update callback function
    ::CVDisplayLinkSetOutputCallback(_displayLink, &DisplayLinkCallback, (__bridge void*)self);

    ::CVDisplayLinkStart(_displayLink);
}

- (void)ReleaseDisplayLink
{
    // Stop the display link BEFORE releasing anything in the view
    // otherwise the display link thread may call into the view and crash
    // when it encounters something that has been release
    ::CVDisplayLinkStop(_displayLink);

    ::CVDisplayLinkRelease(_displayLink);
}

- (void)applicationWillFinishLaunching:(NSNotification*)aNotification
{
    using namespace tgon::platform;

    g_application = std::static_pointer_cast<macos::MacOSApplication>(MakeApplication());
    g_application->OnWillLaunch();
    {
        [self InitializeDisplayLink];
    }
    g_application->OnDidLaunch();
}

- (void)applicationWillTerminate:(NSNotification*)aNotification
{
    g_application->OnWillTerminate();
    {
        [self ReleaseDisplayLink];
    }
    g_application->OnDidTerminate();
    g_application.reset();
}
@end
