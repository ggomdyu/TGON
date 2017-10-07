#import "PrecompiledHeader.pch"

#import <AppKit/NSApplication.h>

#import "Core/Platform/MacOS/MacOSAppDelegate.h"

int main(int argc, const char* argv[])
{
    @autoreleasepool
    {
        // Initialize NSApp.
        id sharedApplication = [NSApplication sharedApplication];

        id appDelegate = [MacOSAppDelegate alloc];
        [sharedApplication setDelegate:appDelegate];
        [sharedApplication setActivationPolicy:NSApplicationActivationPolicyRegular];
        [sharedApplication activateIgnoringOtherApps:YES];

        [sharedApplication run];
    }
    return 0;
}
