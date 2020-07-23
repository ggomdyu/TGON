#pragma once

#include <AppKit/NSApplication.h>
#include <objc/NSObject.h>

#include "../Application.h"

@interface AppDelegate : NSObject<NSApplicationDelegate>
{
    tg::Application* _application;
}
-(id)initWithApp:(tg::Application*)application;
@end

@implementation AppDelegate
-(id)initWithApp:(tg::Application*)application
{
    self = [super init];
    if (self != nil)
    {
        _application = application;
    }

    return self;
}

-(void)applicationWillFinishLaunching:(NSNotification*)aNotification
{
    _application->Initialize();
}

-(void)applicationWillTerminate:(NSNotification*)aNotification
{
}

-(void)applicationDidFinishLaunching:(NSNotification*)aNotification
{
    _application->MessageLoop();
}

-(BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication *)sender
{
    return YES;
}
@end

#define TGON_ENGINE(className)\
    int main(int argc, const char* argv[])\
    {\
        @autoreleasepool\
        {\
            id sharedApplication = [NSApplication sharedApplication];\
            id appDelegate = [AppDelegate alloc];\
            [sharedApplication setDelegate:appDelegate];\
            [sharedApplication setActivationPolicy:NSApplicationActivationPolicyRegular];\
            [sharedApplication activateIgnoringOtherApps:YES];\
            [sharedApplication run];\
        }\
        return 0;\
    }