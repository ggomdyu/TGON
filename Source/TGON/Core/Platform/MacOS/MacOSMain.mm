#import "PrecompiledHeader.pch"

#import "MacOSAppDelegate.h"

#import <AppKit/NSApplication.h>

int main(int argc, const char* argv[])
{
    @autoreleasepool
    {
        // Initialize NSApp.
        id sharedApplication = [NSApplication sharedApplication];

        id appDelegate = [AppDelegate alloc];
        [sharedApplication setDelegate:appDelegate];
        [sharedApplication setActivationPolicy:NSApplicationActivationPolicyRegular];
        [sharedApplication activateIgnoringOtherApps:YES];

        [sharedApplication run];
    }
    return 0;
}