#import "PrecompiledHeader.h"

#import <memory>
#import <cstdint>
#import <cstring>
#import <AppKit/NSWindow.h>
#import <Cocoa/Cocoa.h>

#import "MacOSWindow.h"
#import "MacOSWindowUtility.h"
#import "MacOSWindowDelegate.h"

namespace tgon
{

WindowImpl::WindowImpl(Window* owner)
{
}
    
WindowImpl::WindowImpl(Window* owner, const WindowStyle& windowStyle) :
    m_nsWindow(MakeNativeWindow(windowStyle)),
    m_nsWindowDelegate([[WindowDelegate alloc] initWithWindow:owner])
{
    m_nsWindow.delegate = m_nsWindowDelegate;
}

WindowImpl::WindowImpl(WindowImpl&& rhs) noexcept :
    m_nsWindow(rhs.m_nsWindow)
{
    rhs.m_nsWindow = nullptr;
}

WindowImpl::~WindowImpl()
{
    this->Close();
}

void WindowImpl::Show()
{
    [m_nsWindow display];
}

void WindowImpl::Hide()
{
    [m_nsWindow miniaturize:nullptr];
}

void WindowImpl::Close()
{
    [m_nsWindow close];

    m_nsWindow = nullptr;
}

void WindowImpl::Maximize()
{
    [m_nsWindow zoom:nullptr];
}

void WindowImpl::Minimize()
{
    [m_nsWindow miniaturize:nullptr];
}
    
void WindowImpl::BringToFront()
{
    [NSApp activateIgnoringOtherApps:YES];
    [NSApp activateIgnoringOtherApps:NO];
}

void WindowImpl::SetPosition(int32_t x, int32_t y)
{
    NSRect visibleFrame = [[NSScreen mainScreen] visibleFrame];
    NSRect currentFrameSize = [m_nsWindow frame];

    [m_nsWindow setFrameOrigin:NSMakePoint(static_cast<CGFloat>(x),(visibleFrame.origin.y + visibleFrame.size.height - currentFrameSize.size.height) - y)];
}

void WindowImpl::SetSize(int32_t width, int32_t height)
{
    NSRect currentFrameSize = [m_nsWindow frame];
    currentFrameSize.origin.y += currentFrameSize.size.height - static_cast<CGFloat>(height);
    currentFrameSize.size.width = static_cast<CGFloat>(width);
    currentFrameSize.size.height = static_cast<CGFloat>(height);

    [m_nsWindow setFrame:currentFrameSize display:YES animate:NO];
}

void WindowImpl::SetTitle(const char* title)
{
    [m_nsWindow setTitle:[NSString stringWithUTF8String:title]];
}

void WindowImpl::SetFullScreen(bool isFullScreen)
{
    [m_nsWindow toggleFullScreen:nil];
}

void WindowImpl::SetTopMost(bool setTopMost)
{
    NSWindowLevel windowLevel = (setTopMost) ? NSStatusWindowLevel : NSMainMenuWindowLevel;
    [m_nsWindow setLevel:windowLevel];
}

bool WindowImpl::IsTopMost() const
{
    return [m_nsWindow level] == NSStatusWindowLevel;
}

void WindowImpl::SetTransparency(float transparency)
{
    [m_nsWindow setAlphaValue:transparency];
}

void WindowImpl::GetPosition(int32_t* destX, int32_t* destY) const
{
    NSRect visibleMainScreenFrameRect = [[NSScreen mainScreen] visibleFrame];
    NSRect currentWindowFrameRect = [m_nsWindow frame];

    *destX = static_cast<int32_t>(currentWindowFrameRect.origin.x);
    *destY = static_cast<int32_t>((visibleMainScreenFrameRect.origin.y + visibleMainScreenFrameRect.size.height - currentWindowFrameRect.size.height) - currentWindowFrameRect.origin.y);
}

void WindowImpl::GetSize(int32_t* destWidth, int32_t* destHeight) const
{
    NSRect currentFrameSize = [m_nsWindow frame];

    *destWidth = static_cast<int32_t>(currentFrameSize.size.width);
    *destHeight = static_cast<int32_t>(currentFrameSize.size.height);
}

void WindowImpl::GetTitle(char* destCaptionTitle) const
{
    const char* utf8Str = [[m_nsWindow title] UTF8String];
    std::size_t utf8StrLen = strlen(utf8Str) + 1;

    std::memcpy(destCaptionTitle, utf8Str, utf8StrLen + 1);
}

void* WindowImpl::GetNativeWindow() const
{
    return (__bridge void*)(m_nsWindow);
}

float WindowImpl::GetTransparency() const
{
    return static_cast<float>([m_nsWindow alphaValue]);
}

bool WindowImpl::HasCaption() const
{
    return static_cast<bool>([m_nsWindow hasTitleBar]);
}

bool WindowImpl::IsResizable() const
{
    return static_cast<bool>([m_nsWindow isResizable]);
}

bool WindowImpl::IsMaximized() const
{
    return static_cast<bool>([m_nsWindow isZoomed]);
}

bool WindowImpl::IsMinimized() const
{
    return static_cast<bool>([m_nsWindow isMiniaturized]);
}

} /* namespace tgon */
