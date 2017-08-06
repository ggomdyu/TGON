#import "PrecompiledHeader.pch"
#import "MacOSWindow.h"

#import <memory>
#import <cstdint>
#import <cstring>

#import "MacOSWindowUtility.h"

namespace tgon
{
namespace platform
{
namespace macos
{

MacOSWindow::MacOSWindow(const WindowStyle& windowStyle) :
    m_nsWindow(CreateNativeWindow(windowStyle))
{
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

void MacOSWindow::SetCaptionTitle(const char* captionTitle)
{
    [m_nsWindow setTitle:[NSString stringWithUTF8String:captionTitle]];
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

void MacOSWindow::GetCaptionTitle(char* destCaptionTitle) const
{
    const char* utf8Str = [[m_nsWindow title] UTF8String];
    std::size_t utf8StrLen = strlen(utf8Str) + 1;

    std::memcpy(destCaptionTitle, utf8Str, utf8StrLen + 1);
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
