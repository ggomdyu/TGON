#import "PrecompiledHeader.pch"

#import <AppKit/NSApplication.h>

#import "MacOSAppDelegate.h"

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
