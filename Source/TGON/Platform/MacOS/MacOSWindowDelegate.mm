#import "PrecompiledHeader.h"

#import "MacOSWindowDelegate.h"
#import "MacOSWindow.h"

@implementation WindowDelegate

- (id)initWithWindow:(tgon::MacOSWindow*)window
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
    if (_window->OnResize != nullptr)
    {
        int32_t width, height;
        _window->GetExtent(&width, &height);

        _window->OnResize(width, height);
    }
}

- (void)windowDidMove:(NSNotification*)notification
{
    if (_window->OnMove != nullptr)
    {
        int32_t x, y;
        _window->GetPosition(&x, &y);
        
        _window->OnMove(x, y);
    }
}

- (void)windowWillMiniaturize:(NSNotification*)notification
{
    if (_window->OnMinimize != nullptr)
    {
        _window->OnMinimize();
    }
}

- (void)windowDidDeminiaturize:(NSNotification*)notification
{
    if (_window->OnMaximize != nullptr)
    {
        _window->OnMaximize();
    }
}

- (void)windowDidEnterFullScreen:(NSNotification *)notification
{
    if (_window->OnEnterFullScreen != nullptr)
    {
        _window->OnEnterFullScreen();
    }
}

- (void)windowDidExitFullScreen:(NSNotification *)notification
{
    if (_window->OnExitFullScreen != nullptr)
    {
        _window->OnExitFullScreen();
    }
}
@end
