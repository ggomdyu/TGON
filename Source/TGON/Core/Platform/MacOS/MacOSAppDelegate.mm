#import "PrecompiledHeader.h"

#import <AppKit/NSOpenGLView.h>

#import "../Application.h"

#import "MacOSAppDelegate.h"

namespace tgon
{

extern std::shared_ptr<Application> MakeApplication();

} /* namespace tgon */

namespace
{

std::shared_ptr<tgon::Application> g_application;

} /* namespace */

@implementation AppDelegate
- (void)applicationWillFinishLaunching:(NSNotification*)aNotification
{
    using namespace tgon;

    g_application = std::static_pointer_cast<Application>(MakeApplication());
    g_application->OnWillLaunch();
}

- (void)applicationDidFinishLaunching:(NSNotification*)aNotification
{
    g_application->OnDidLaunch();

    // If launch has been completed, then start the message loop.
    g_application->MessageLoop();
}

- (void)applicationWillTerminate:(NSNotification*)aNotification
{
    g_application->OnWillTerminate();
    g_application.reset();
}

- (BOOL) applicationShouldTerminateAfterLastWindowClosed: (NSApplication *)sender
{
    return YES;
}
@end
