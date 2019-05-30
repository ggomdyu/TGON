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
    NSRect windowFrameRect = [m_window frame];

    [m_window setFrameOrigin:NSMakePoint(static_cast<CGFloat>(x),(mainScreenRect.origin.y + mainScreenRect.size.height - windowFrameRect.size.height) - y)];
}

void MacOSWindow::SetSize(int32_t width, int32_t height)
{
    NSRect currentFrameSize = [m_window frame];
    currentFrameSize.origin.y += currentFrameSize.size.height - static_cast<CGFloat>(height);
    currentFrameSize.size.width = static_cast<CGFloat>(width);
    currentFrameSize.size.height = static_cast<CGFloat>(height);

    [m_window setFrame:currentFrameSize display:YES animate:NO];
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
    NSRect visibleMainScreenFrameRect = [[NSScreen mainScreen] visibleFrame];
    NSRect currentWindowFrameRect = [m_window frame];

    *destX = static_cast<int32_t>(currentWindowFrameRect.origin.x);
    *destY = static_cast<int32_t>((visibleMainScreenFrameRect.origin.y + visibleMainScreenFrameRect.size.height - currentWindowFrameRect.size.height) - currentWindowFrameRect.origin.y);
}

void MacOSWindow::GetExtent(int32_t* destWidth, int32_t* destHeight) const
{
    NSRect currentFrameSize = [m_window frame];

    *destWidth = static_cast<int32_t>(currentFrameSize.size.width);
    *destHeight = static_cast<int32_t>(currentFrameSize.size.height);
}

void MacOSWindow::GetTitle(char* destCaptionTitle) const
{
    const char* utf8Str = [[m_window title] UTF8String];
    std::size_t utf8StrLen = strlen(utf8Str) + 1;

    std::memcpy(destCaptionTitle, utf8Str, utf8StrLen + 1);
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
