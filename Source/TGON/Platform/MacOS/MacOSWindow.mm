#import "PrecompiledHeader.h"

#import <memory>
#import <cstdint>
#import <cstring>
#import <AppKit/NSWindow.h>
#import <Cocoa/Cocoa.h>

#import "MacOSWindow.h"
#import "MacOSWindowUtility.h"

@interface WindowDelegate : NSObject<NSWindowDelegate>
{
}

@property (readonly, assign) tgon::MacOSWindow* window;

- (id)initWithWindow:(tgon::MacOSWindow*)window;

@end

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

namespace tgon
{

MacOSWindow::MacOSWindow(const WindowStyle& windowStyle) :
    m_window(CreateNativeWindow(windowStyle)),
    m_windowDelegate([[WindowDelegate alloc] initWithWindow:this])
{
    m_window.delegate = m_windowDelegate;
}

MacOSWindow::MacOSWindow(MacOSWindow&& rhs) noexcept :
    m_window(rhs.m_window)
{
    rhs.m_window = nullptr;
}

MacOSWindow::~MacOSWindow()
{
    this->Close();
}

void MacOSWindow::Show()
{
    [m_window display];
}

void MacOSWindow::Hide()
{
    [m_window miniaturize:nullptr];
}

void MacOSWindow::Close()
{
    [m_window close];

    m_window = nullptr;
}

void MacOSWindow::Maximize()
{
    [m_window zoom:nullptr];
}

void MacOSWindow::Minimize()
{
    [m_window miniaturize:nullptr];
}
    
void MacOSWindow::BringToFront()
{
    [NSApp activateIgnoringOtherApps:YES];
    [NSApp activateIgnoringOtherApps:NO];
}

void MacOSWindow::SetPosition(int32_t x, int32_t y)
{
    NSRect mainScreenRect = [[NSScreen mainScreen] visibleFrame];
    NSRect windowRect = [m_window frame];

    [m_window setFrameOrigin:NSMakePoint(static_cast<CGFloat>(x),(mainScreenRect.origin.y + mainScreenRect.size.height - windowRect.size.height) - y)];
}

void MacOSWindow::SetContentSize(int32_t width, int32_t height)
{
    NSRect windowRect = [m_window frame];
    windowRect.size.width = static_cast<CGFloat>(width);
    windowRect.size.height = static_cast<CGFloat>(height);
    
    NSRect clientRect = [m_window frameRectForContentRect:windowRect];
    clientRect.origin.y += clientRect.size.height - static_cast<CGFloat>(height);
    
    [m_window setContentSize:NSMakeSize(clientRect.size.width, clientRect.size.height)];
}

void MacOSWindow::SetTitle(const char* title)
{
    [m_window setTitle:[NSString stringWithUTF8String:title]];
}

void MacOSWindow::SetFullScreen(bool isFullScreen)
{
    [m_window toggleFullScreen:nil];
}

void MacOSWindow::SetTopMost(bool setTopMost)
{
    NSWindowLevel windowLevel = (setTopMost) ? NSStatusWindowLevel : NSMainMenuWindowLevel;
    [m_window setLevel:windowLevel];
}

bool MacOSWindow::IsTopMost() const
{
    return [m_window level] == NSStatusWindowLevel;
}

void MacOSWindow::SetTransparency(float transparency)
{
    [m_window setAlphaValue:transparency];
}

void MacOSWindow::GetPosition(int32_t* destX, int32_t* destY) const
{
    NSRect mainScreenRect = [[NSScreen mainScreen] visibleFrame];
    NSRect windowRect = [m_window frame];

    *destX = static_cast<int32_t>(windowRect.origin.x);
    *destY = static_cast<int32_t>((mainScreenRect.origin.y + mainScreenRect.size.height - windowRect.size.height) - windowRect.origin.y);
}

void MacOSWindow::GetExtent(int32_t* destWidth, int32_t* destHeight) const
{
    auto windowRect = [m_window frame];
    
    *destWidth = static_cast<int32_t>(windowRect.size.width);
    *destHeight = static_cast<int32_t>(windowRect.size.height);
}

void MacOSWindow::GetTitle(char* destTitle) const
{
    const char* str = [[m_window title] UTF8String];
    size_t strBytes = [[m_window title] lengthOfBytesUsingEncoding:NSUTF8StringEncoding];

    memcpy(destTitle, str, strBytes + 1);
}

void* MacOSWindow::GetNativeWindow() const
{
    return (__bridge void*)(m_window);
}

float MacOSWindow::GetTransparency() const
{
    return static_cast<float>([m_window alphaValue]);
}

bool MacOSWindow::HasCaption() const
{
    return static_cast<bool>([m_window hasTitleBar]);
}

bool MacOSWindow::IsResizable() const
{
    return static_cast<bool>([m_window isResizable]);
}

bool MacOSWindow::IsMaximized() const
{
    return static_cast<bool>([m_window isZoomed]);
}

bool MacOSWindow::IsMinimized() const
{
    return static_cast<bool>([m_window isMiniaturized]);
}

} /* namespace tgon */
