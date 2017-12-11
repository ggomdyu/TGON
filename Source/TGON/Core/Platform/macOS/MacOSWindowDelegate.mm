#import "PrecompiledHeader.pch"
#import "MacOSWindowDelegate.h"

#import "Window.h"

@implementation WindowDelegate

- (id)initWithWindow:(tgon::platform::Window*)window
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
    int32_t width, height;
    _window->GetSize(&width, &height);

    _window->OnResize(width, height);
}

- (void)windowDidMove:(NSNotification*)notification                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 {
    int32_t x, y;
    _window->GetPosition(&x, &y);

    _window->OnMove(x, y);
}

- (void)windowWillMiniaturize:(NSNotification*)notification
{
    _window->OnMinimize();
}

- (void)windowDidDeminiaturize:(NSNotification*)notification
{
    _window->OnMaximize();
}

- (void)windowDidEnterFullScreen:(NSNotification *)notification
{
    _window->OnEnterFullScreen();
}

- (void)windowDidExitFullScreen:(NSNotification *)notification
{
    _window->OnExitFullScreen();
}
@end
