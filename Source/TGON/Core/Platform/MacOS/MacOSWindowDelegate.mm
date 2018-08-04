#import "PrecompiledHeader.h"

#import "MacOSWindowDelegate.h"

@implementation WindowDelegate

- (id)initWithWindow:(tgon::Window*)window
{
    self = [super init];
    if (self)
    {
        _window = window;
    }
    
    return self;
}

- (void)windowDidResize:(NSNotification*)notification
{
    if (_window->OnWindowResize != nullptr)
    {
        int32_t width, height;
        _window->GetSize(&width, &height);

        _window->OnWindowResize(width, height);
    }
}

- (void)windowDidMove:(NSNotification*)notification
{
    if (_window->OnWindowMove != nullptr)
    {
        int32_t x, y;
        _window->GetPosition(&x, &y);
        
        _window->OnWindowMove(x, y);
    }
}

- (void)windowWillMiniaturize:(NSNotification*)notification
{
    if (_window->OnWindowMinimize != nullptr)
    {
        _window->OnWindowMinimize();
    }
}

- (void)windowDidDeminiaturize:(NSNotification*)notification
{
    if (_window->OnWindowMaximize != nullptr)
    {
        _window->OnWindowMaximize();
    }
}

- (void)windowDidEnterFullScreen:(NSNotification *)notification
{
    if (_window->OnWindowEnterFullScreen != nullptr)
    {
        _window->OnWindowEnterFullScreen();
    }
}

- (void)windowDidExitFullScreen:(NSNotification *)notification
{
    if (_window->OnWindowExitFullScreen != nullptr)
    {
        _window->OnWindowExitFullScreen();
    }
}
@end
