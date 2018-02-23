#import "PrecompiledHeader.pch"

#import "MacOSWindow.h"
#import "MacOSWindowUtility.h"
#import "MacOSWindowDelegate.h"

#import "../Generic/GenericWindowType.h"

#import <memory>
#import <cstdint>
#import <cstring>
#import <AppKit/NSWindow.h>
#import <Cocoa/Cocoa.h>

namespace tgon
{
namespace core
{

MacOSWindow::MacOSWindow(const WindowStyle& windowStyle) :
    m_nsWindow(MakeNativeWindow(windowStyle)),
    m_windowDelegate([[WindowDelegate alloc] initWithWindow:this])
{
    m_nsWindow.delegate = m_windowDelegate;
}

MacOSWindow::MacOSWindow(MacOSWindow&& rhs) noexcept :
    m_nsWindow(rhs.m_nsWindow),
    m_windowDelegate(rhs.m_windowDelegate)
{
    rhs.m_nsWindow = nullptr;
    rhs.m_windowDelegate = nullptr;
}

MacOSWindow::~MacOSWindow()
{
    this->Close();
}

MacOSWindow& MacOSWindow::operator=(MacOSWindow&& rhs) noexcept
{
    if (this == &rhs)
    {
        return *this;
    }

    this->~MacOSWindow();
    new (this) MacOSWindow(std::move(rhs));

    return *this;
}

void MacOSWindow::Show()
{
    [m_nsWindow display];
}

void MacOSWindow::Hide()
{
    [m_nsWindow miniaturize:nullptr];
}

void MacOSWindow::Close()
{
    [m_nsWindow close];

    m_nsWindow = nullptr;
    m_windowDelegate = nullptr;
    m_isClosed = true;
}

void MacOSWindow::Maximize()
{
    [m_nsWindow zoom:nullptr];
}

void MacOSWindow::Minimize()
{
    [m_nsWindow miniaturize:nullptr];
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

void MacOSWindow::SetTopMost(bool setTopMost)
{
    NSWindowLevel windowLevel = (setTopMost) ? NSStatusWindowLevel : NSMainMenuWindowLevel;
    [m_nsWindow setLevel:windowLevel];
}

bool MacOSWindow::IsTopMost() const
{
    return [m_nsWindow level] == NSStatusWindowLevel;
}

void MacOSWindow::SetTransparency(float transparency)
{
    [m_nsWindow setAlphaValue:transparency];
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

const void* MacOSWindow::GetNativeWindow() const
{
    return (__bridge const void*)(m_nsWindow);
}

float MacOSWindow::GetTransparency() const
{
    return static_cast<float>([m_nsWindow alphaValue]);
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
    return static_cast<bool>([m_nsWindow isZoomed]);
}

bool MacOSWindow::IsMinimized() const
{
    return static_cast<bool>([m_nsWindow isMiniaturized]);
}

} /* namespace core */
} /* namespace tgon */
