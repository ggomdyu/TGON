#import "PrecompiledHeader.pch"

#import "MacOSAppDelegate.h"

#import "../Application.h"

#import <AppKit/NSOpenGLView.h>
#import <QuartzCore/CVDisplayLink.h>

namespace tgon
{
namespace core
{

extern std::shared_ptr<Application> MakeApplication();

} /* namespace core */
} /* namespace tgon */

namespace
{

std::shared_ptr<tgon::core::Application> g_application;

} /* namespace */

@implementation AppDelegate
- (void)applicationWillFinishLaunching:(NSNotification*)aNotification
{
    using namespace tgon::core;

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
