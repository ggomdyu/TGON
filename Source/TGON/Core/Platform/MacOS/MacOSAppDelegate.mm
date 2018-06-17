#import "PrecompiledHeader.h"

#import "Core/Platform/Application.h"

#import "MacOSAppDelegate.h"

namespace
{
    
std::shared_ptr<tgon::Application> g_application;
    
} /* namespace */

namespace tgon
{
    
extern std::unique_ptr<Engine> MakeEngine();

std::shared_ptr<Application> Application::GetInstance()
{
    return g_application;
}

} /* namespace tgon */

@implementation AppDelegate
- (void)applicationWillFinishLaunching:(NSNotification*)aNotification
{
    g_application = std::make_shared<tgon::Application>(tgon::MakeEngine());
    g_application->OnDidLaunch();
}

- (void)applicationDidFinishLaunching:(NSNotification*)aNotification
{
    // If launch has been completed, then start the message loop.
    g_application->MessageLoop();
}

- (void)applicationWillTerminate:(NSNotification*)aNotification
{
    g_application->OnWillTerminate();
}

- (BOOL) applicationShouldTerminateAfterLastWindowClosed: (NSApplication *)sender
{
    return YES;
}
@end
