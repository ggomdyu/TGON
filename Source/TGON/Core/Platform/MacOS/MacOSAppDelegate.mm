#import "PrecompiledHeader.h"

#import "Core/Platform/Application.h"
#import "Core/Object/Engine.h"

#import "MacOSAppDelegate.h"

namespace tgon
{
    
extern std::unique_ptr<Engine> MakeEngine();

} /* namespace tgon */

@implementation AppDelegate
- (void)applicationWillFinishLaunching:(NSNotification*)aNotification
{
    using namespace tgon;
    
    // Initialize singleton objects.
    decltype(auto) application = Application::GetInstance();
    decltype(auto) engine = Engine::GetInstance();
    
    application->OnDidLaunch();
}

- (void)applicationDidFinishLaunching:(NSNotification*)aNotification
{
    using namespace tgon;
    
    decltype(auto) engine = Engine::GetInstance();
    
    // If launch has been completed, then start the message loop.
    Application::GetInstance()->MessageLoop([engine]()
    {
        engine->Update();
    });
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
