/**
 * @filename    MacOSWindow.h
 * @author      ggomdyu
 * @since       07/21/2017
 * @brief
 */

#pragma once
#import "Core/Platform/Base/BaseWindow.h"

@class NSWindow;
@class MacOSWindowDelegate;

namespace tgon
{
namespace platform
{
namespace macos
{
    
class TGON_API MacOSWindow :
    public BaseWindow
{
/* @section Public constructor */
public:
    explicit MacOSWindow(const WindowStyle& windowStyle = WindowStyle{});
    explicit MacOSWindow(NSWindow* nsWindow) noexcept;

/* @section Public destructor */
public:
    virtual ~MacOSWindow() = default;

/* @section Public method */
public:
    virtual void Quit() override {}
    virtual void Maximize() override;
    virtual void Minimize() override;
    virtual void BringToFront() override {}
    
    virtual void SetPosition(int32_t x, int32_t y) override;
    virtual void SetSize(int32_t width, int32_t height) override;
    virtual void SetTitle(const char* title) override;
    virtual void SetFullScreen(bool isFullScreen) override;
    virtual void GetPosition(int32_t* x, int32_t* y) const override;
    virtual void GetSize(int32_t* width, int32_t* height) const override;
    virtual void GetTitle(char* destCaptionTitle) const override;
    virtual void* GetNativeWindow() noexcept override;
    virtual bool HasCaption() const override;
    virtual bool IsResizable() const override;
    virtual bool IsMaximized() const override;
    virtual bool IsMinimized() const override;

/* @section Private variable */
private:
    NSWindow* m_nsWindow;
    MacOSWindowDelegate* m_windowDelegate;
};
    
} /* namespace macos */

using Window = macos::MacOSWindow;

} /* namespace platform */
} /* namespace tgon */
