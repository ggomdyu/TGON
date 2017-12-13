#import "PrecompiledHeader.pch"
#import "MacOSAppDelegate.h"

#import <QuartzCore/CVDisplayLink.h>
#import <AppKit/NSOpenGLView.h>

#import "../Application.h"

namespace tgon
{
namespace platform
{

extern std::shared_ptr<Application> MakeApplication();

} /* namespace platform */
} /* namespace tgon */

namespace
{

std::shared_ptr<tgon::platform::Application> g_application;

} /* namespace */

@implementation AppDelegate
- (void)applicationWillFinishLaunching:(NSNotification*)aNotification
{
    using namespace tgon::platform;

    g_application = std::static_pointer_cast<Application>(MakeApplication());
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
