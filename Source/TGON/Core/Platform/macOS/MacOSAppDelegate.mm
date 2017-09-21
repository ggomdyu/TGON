#import "PrecompiledHeader.pch"
#import "MacOSAppDelegate.h"

#import "Core/Platform/Base/BaseApplication.h"
#import "Core/Platform/Window.h"

namespace tgon
{
namespace platform
{

extern std::shared_ptr<BaseApplication> MakeApplication();

} /* namespace platform */
} /* namespace tgon */

namespace
{

static std::shared_ptr<tgon::platform::BaseApplication> g_application;

} /* namespace */

@implementation MacOSAppDelegate
- (void)InitializeUpdateTimer
{
    constexpr float maxFrame = 60.0f;
    constexpr float frameTimeInterval = 1.0f / maxFrame;

    _updateTimer = [NSTimer scheduledTimerWithTimeInterval:frameTimeInterval
                                                    target:self
                                                  selector:@selector(OnUpdate)
                                                  userInfo:nil
                                                   repeats:YES];
}

- (void)applicationWillFinishLaunching:(NSNotification*)aNotification
{
    using namespace tgon::platform;

    if (g_application == nullptr)
    {
        g_application = MakeApplication();
    }
    g_application->OnLaunch();

    [self InitializeUpdateTimer];
}

- (void)applicationWillTerminate:(NSNotification*)aNotification
{
    g_application->OnTerminate();
}

- (void)OnUpdate
{
    g_application->OnUpdate();
}
@end
