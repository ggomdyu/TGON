#include "PrecompiledHeader.h"

#include <AppKit/NSApplication.h>
#include <objc/NSObject.h>

#include "Platform/Application.h"

@interface AppDelegate : NSObject<NSApplicationDelegate>
{
    tg::Application* _app;
}
-(id)initWithApp:(tg::Application*)app;
@end

@implementation AppDelegate
-(id)initWithApp:(tg::Application*)app
{
    self = [super init];
    if (self != nil)
    {
        _app = app;
    }

    return self;
}

-(void)applicationWillFinishLaunching:(NSNotification*)aNotification
{
    _app->Initialize();
}

-(void)applicationWillTerminate:(NSNotification*)aNotification
{
}

-(void)applicationDidFinishLaunching:(NSNotification*)aNotification
{
    _app->MessageLoop();
}

-(BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)sender
{
    return YES;
}
@end

int main(int argc, const char* argv[])
{
    @autoreleasepool
    {
        id sharedApplication = [NSApplication sharedApplication];

        id appDelegate = [[AppDelegate alloc] initWithApp:&tg::Application::GetInstance()];
        [sharedApplication setDelegate:appDelegate];
        [sharedApplication setActivationPolicy:NSApplicationActivationPolicyRegular];
        [sharedApplication activateIgnoringOtherApps:YES];

        [sharedApplication run];
    }
    return 0;
}
