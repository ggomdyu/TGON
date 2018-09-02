#import "PrecompiledHeader.h"

#import "Core/Platform/Application.h"

#import "MacOSAppDelegate.h"

@implementation AppDelegate
- (void)applicationWillFinishLaunching:(NSNotification*)aNotification
{
    using namespace tgon;
    
    // Initialize singleton objects.
    decltype(auto) application = Application::GetInstance();

    application->OnDidLaunch();
}

- (void)applicationDidFinishLaunching:(NSNotification*)aNotification
{
    using namespace tgon;
    
    // If launch has been completed, then start the message loop.
    Application::GetInstance()->MessageLoop();
}

- (void)applicationWillTerminate:(NSNotification*)aNotification
{
    using namespace tgon;
    
    Application::GetInstance()->OnWillTerminate();
}

- (BOOL) applicationShouldTerminateAfterLastWindowClosed: (NSApplication *)sender
{
    return YES;
}
@end
