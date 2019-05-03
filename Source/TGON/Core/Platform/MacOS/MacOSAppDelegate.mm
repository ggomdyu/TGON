#import "PrecompiledHeader.h"

#import "Core/Platform/Application.h"

#import "MacOSAppDelegate.h"

@implementation AppDelegate
- (void)applicationWillFinishLaunching:(NSNotification*)aNotification
{
    // Initialize singleton objects.
    tgon::Application::GetInstance()->OnLaunch();
}

- (void)applicationDidFinishLaunching:(NSNotification*)aNotification
{
    // If launch has been completed, then start the message loop.
    tgon::Application::GetInstance()->MessageLoop();
}

- (void)applicationWillTerminate:(NSNotification*)aNotification
{
    tgon::Application::GetInstance()->OnTerminate();
}

- (BOOL)applicationShouldTerminateAfterLastWindowClosed: (NSApplication *)sender
{
    return YES;
}
@end
