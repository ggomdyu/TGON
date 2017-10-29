#import "PrecompiledHeader.pch"
#import "MacOSWindow.h"

#import <Cocoa/Cocoa.h>
#import <memory>
#import <cstdint>
#import <cstring>

#import "MacOSWindowUtility.h"
#import "MacOSWindowDelegate.h"

namespace tgon
{
namespace platform
{
namespace macos
{

MacOSWindow::MacOSWindow(const WindowStyle& windowStyle) :
    m_nsWindow(CreateNativeWindow(windowStyle)),
    m_windowDelegate([[MacOSWindowDelegate alloc] initWithWindow:this])
{
    m_nsWindow.delegate = m_windowDelegate;
}

MacOSWindow::MacOSWindow(NSWindow* nsWindow) noexcept :
    m_nsWindow(nsWindow)
{
}

MacOSWindow::MacOSWindow(MacOSWindow&& window) :
    m_nsWindow(window.m_nsWindow),
    m_windowDelegate(window.m_windowDelegate)
{
    window.m_nsWindow = nil;
    window.m_windowDelegate = nil;
}

MacOSWindow::~MacOSWindow()
{
    m_nsWindow = nil;
    m_windowDelegate = nil;
}

MacOSWindow& MacOSWindow::operator=(MacOSWindow&& rhs)
{
    m_nsWindow = rhs.m_nsWindow;
    m_windowDelegate = rhs.m_windowDelegate;

    rhs.m_nsWindow = nil;
    rhs.m_windowDelegate = nil;

    return *this;
}

void MacOSWindow::InitWithWindowStyle(const WindowStyle& windowStyle)
{
    new (this) MacOSWindow(windowStyle);
}

void MacOSWindow::Show()
{
//    [m_nsWindow display];
}

void MacOSWindow::Hide()
{
}

void MacOSWindow::Maximize()
{
    [m_nsWindow zoom:nil];
}

void MacOSWindow::Minimize()
{
    [m_nsWindow miniaturize:nil];
}

void MacOSWindow::SetPosition(int32_t x, int32_t y)
{
    NSRect visibleFrame = [[NSScreen mainScreen] visibleFrame];
    NSRect currentFrameSize = [m_nsWindow frame];

    [m_nsWindow setFrameOrigin:NSMakePoint(static_cast<CGFloat>(x),(visibleFrame.origin.y + visibleFrame.size.height - currentFrameSize.size.height) - y)];
}

void MacOSWindow::SetSize(int32_t width, int32_t height)
{
    NSRect currentFrameSize = [m_nsWindow frame];
    currentFrameSize.origin.y += currentFrameSize.size.height - static_cast<CGFloat>(height);
    currentFrameSize.size.width = static_cast<CGFloat>(width);
    currentFrameSize.size.height = static_cast<CGFloat>(height);

    [m_nsWindow setFrame:currentFrameSize display:YES animate:NO];
}

void MacOSWindow::SetTitle(const char* title)
{
    [m_nsWindow setTitle:[NSString stringWithUTF8String:title]];
}

void MacOSWindow::SetFullScreen(bool isFullScreen)
{
    [m_nsWindow toggleFullScreen:nil];
}

void MacOSWindow::GetPosition(int32_t* destX, int32_t* destY) const
{
    NSRect visibleMainScreenFrameRect = [[NSScreen mainScreen] visibleFrame];
    NSRect currentWindowFrameRect = [m_nsWindow frame];

    *destX = static_cast<int32_t>(currentWindowFrameRect.origin.x);
    *destY = static_cast<int32_t>((visibleMainScreenFrameRect.origin.y + visibleMainScreenFrameRect.size.height - currentWindowFrameRect.size.height) - currentWindowFrameRect.origin.y);
}

void MacOSWindow::GetSize(int32_t* destWidth, int32_t* destHeight) const
{
    NSRect currentFrameSize = [m_nsWindow frame];

    *destWidth = static_cast<int32_t>(currentFrameSize.size.width);
    *destHeight = static_cast<int32_t>(currentFrameSize.size.height);
}

void MacOSWindow::GetTitle(char* destCaptionTitle) const
{
    const char* utf8Str = [[m_nsWindow title] UTF8String];
    std::size_t utf8StrLen = strlen(utf8Str) + 1;

    std::memcpy(destCaptionTitle, utf8Str, utf8StrLen + 1);
}

void* MacOSWindow::GetNativeWindow() noexcept
{
    return (__bridge void*)(m_nsWindow);
}

bool MacOSWindow::HasCaption() const
{
    return static_cast<bool>([m_nsWindow hasTitleBar]);
}

bool MacOSWindow::IsResizable() const
{
    return static_cast<bool>([m_nsWindow isResizable]);
}

bool MacOSWindow::IsMaximized() const
{
    // todo: 잘 되는지 확인 필요
    return static_cast<bool>([m_nsWindow isZoomed]);
}

bool MacOSWindow::IsMinimized() const
{
    return static_cast<bool>([m_nsWindow isMiniaturized]);
}

} /* namespace macos */
} /* namespace platform */
} /* namespace tgon */
