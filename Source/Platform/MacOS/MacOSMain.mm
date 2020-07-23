#include "PrecompiledHeader.h"

#include <AppKit/NSApplication.h>
#include <objc/NSObject.h>

#include "Platform/Application.h"


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
