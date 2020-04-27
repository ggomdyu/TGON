#include "PrecompiledHeader.h"

#include <AppKit/NSApplication.h>
#include <objc/NSObject.h>

#include "Platform/Application.h"

@interface AppDelegate : NSObject<NSApplicationDelegate>
{
}
@end

@implementation AppDelegate
- (void)applicationWillFinishLaunching:(NSNotification*)aNotification
{
    tg::Application::GetInstance().Initialize();
}

- (void)applicationWillTerminate:(NSNotification*)aNotification
{
    tg::Application::GetInstance().Destroy();
}

- (void)applicationDidFinishLaunching:(NSNotification*)aNotification
{
    tg::Application::GetInstance().MessageLoop();
}

- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)sender
{
    return YES;
}
@end

int main(int argc, const char* argv[])
{
    @autoreleasepool
    {
        id sharedApplication = [NSApplication sharedApplication];

        id appDelegate = [AppDelegate alloc];
        [sharedApplication setDelegate:appDelegate];
        [sharedApplication setActivationPolicy:NSApplicationActivationPolicyRegular];
        [sharedApplication activateIgnoringOtherApps:YES];

        [sharedApplication run];
    }
    return 0;
}
