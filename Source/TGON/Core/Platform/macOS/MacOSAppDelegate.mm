#import "PrecompiledHeader.pch"
#import "MacOSAppDelegate.h"

#import <QuartzCore/CVDisplayLink.h>
#import <AppKit/NSOpenGLView.h>

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

} /* namespace */

@implementation MacOSAppDelegate
- (void)applicationWillFinishLaunching:(NSNotification*)aNotification
{
    using namespace tgon::platform;

    g_application = std::static_pointer_cast<macos::MacOSApplication>(MakeApplication());
    g_application->OnWillLaunch();
}

- (void)applicationDidFinishLaunching:(NSNotification*)aNotification
{
    g_application->OnDidLaunch();

    // If launch is over, then start the message loop.
    g_application->MessageLoop();
}

- (void)applicationWillTerminate:(NSNotification*)aNotification
{
    g_application->OnWillTerminate();
    g_application.reset();
}
@end
