#import "PrecompiledHeader.pch"

#import "../Window.h"
#import "../WindowType.h"

#import "MacOSWindowUtility.h"
#import "MacOSWindowDelegate.h"

#import <AppKit/NSWindow.h>
#import <Cocoa/Cocoa.h>
#import <memory>
#import <cstdint>
#import <cstring>

namespace tgon
{
namespace core
{

Window::Window(const WindowStyle& windowStyle) :
    m_nsWindow(MakeNativeWindow(windowStyle)),
    m_windowDelegate([[WindowDelegate alloc] initWithWindow:this])
{
    m_nsWindow.delegate = m_windowDelegate;
}

Window::Window(Window&& rhs) noexcept :
    m_nsWindow(rhs.m_nsWindow),
    m_windowDelegate(rhs.m_windowDelegate)
{
    rhs.m_nsWindow = nil;
    rhs.m_windowDelegate = nil;
}

Window::~Window()
{
    [m_nsWindow close];

    m_isClosed = true;
    m_nsWindow = nil;
    m_windowDelegate = nil;
}

Window& Window::operator=(Window&& rhs) noexcept
{
    m_nsWindow = rhs.m_nsWindow;
    m_windowDelegate = rhs.m_windowDelegate;

    rhs.m_nsWindow = nil;
    rhs.m_windowDelegate = nil;

    return *this;
}

void Window::Initialize(const WindowStyle& windowStyle)
{
    new (this) Window(windowStyle);
}

void Window::Show()
{
//    [m_nsWindow display];
}

void Window::Hide()
{
}

void Window::Maximize()
{
    [m_nsWindow zoom:nil];
}

void Window::Minimize()
{
    [m_nsWindow miniaturize:nil];
}

void Window::SetPosition(int32_t x, int32_t y)
{
    NSRect visibleFrame = [[NSScreen mainScreen] visibleFrame];
    NSRect currentFrameSize = [m_nsWindow frame];

    [m_nsWindow setFrameOrigin:NSMakePoint(static_cast<CGFloat>(x),(visibleFrame.origin.y + visibleFrame.size.height - currentFrameSize.size.height) - y)];
}

void Window::SetSize(int32_t width, int32_t height)
{
    NSRect currentFrameSize = [m_nsWindow frame];
    currentFrameSize.origin.y += currentFrameSize.size.height - static_cast<CGFloat>(height);
    currentFrameSize.size.width = static_cast<CGFloat>(width);
    currentFrameSize.size.height = static_cast<CGFloat>(height);

    [m_nsWindow setFrame:currentFrameSize display:YES animate:NO];
}

void Window::SetTitle(const char* title)
{
    [m_nsWindow setTitle:[NSString stringWithUTF8String:title]];
}

void Window::SetFullScreen(bool isFullScreen)
{
    [m_nsWindow toggleFullScreen:nil];
}

void Window::SetTransparency(float transparency)
{
    [m_nsWindow setAlphaValue:transparency];
}

void Window::GetPosition(int32_t* destX, int32_t* destY) const
{
    NSRect visibleMainScreenFrameRect = [[NSScreen mainScreen] visibleFrame];
    NSRect currentWindowFrameRect = [m_nsWindow frame];

    *destX = static_cast<int32_t>(currentWindowFrameRect.origin.x);
    *destY = static_cast<int32_t>((visibleMainScreenFrameRect.origin.y + visibleMainScreenFrameRect.size.height - currentWindowFrameRect.size.height) - currentWindowFrameRect.origin.y);
}

void Window::GetSize(int32_t* destWidth, int32_t* destHeight) const
{
    NSRect currentFrameSize = [m_nsWindow frame];

    *destWidth = static_cast<int32_t>(currentFrameSize.size.width);
    *destHeight = static_cast<int32_t>(currentFrameSize.size.height);
}

void Window::GetTitle(char* destCaptionTitle) const
{
    const char* utf8Str = [[m_nsWindow title] UTF8String];
    std::size_t utf8StrLen = strlen(utf8Str) + 1;

    std::memcpy(destCaptionTitle, utf8Str, utf8StrLen + 1);
}

void* Window::GetNativeWindow()
{
    return (__bridge void*)(m_nsWindow);
}

float Window::GetTransparency() const
{
    return static_cast<float>([m_nsWindow alphaValue]);
}

bool Window::HasCaption() const
{
    return static_cast<bool>([m_nsWindow hasTitleBar]);
}

bool Window::IsResizable() const
{
    return static_cast<bool>([m_nsWindow isResizable]);
}

bool Window::IsMaximized() const
{
    return static_cast<bool>([m_nsWindow isZoomed]);
}

bool Window::IsMinimized() const
{
    return static_cast<bool>([m_nsWindow isMiniaturized]);
}

} /* namespace core */
} /* namespace tgon */
