/**
 * @filename    MacOSWindow.h
 * @author      ggomdyu
 * @since       07/21/2017
 * @brief
 */

#import <Cocoa/Cocoa.h>

#import "Core/Platform/Generic/GenericWindow.h"

namespace tgon
{
namespace platform
{
namespace macos
{
    
class TGON_API MacOSWindow :
    public GenericWindow
{
/* @section Ctor/Dtor */
public:
    explicit MacOSWindow(const WindowStyle& windowStyle);
    virtual ~MacOSWindow() = default;

/* @section Public method */
public:
    virtual void Show() override {}
    virtual void Hide() override {}
    virtual void Quit() override {}
    virtual void Maximize() override {}
    virtual void Minimize() override {}
    virtual void BringToFront() override {}
    
    virtual void SetPosition(int32_t x, int32_t y) override;
    virtual void SetSize(int32_t width, int32_t height) override;
    virtual void SetCaptionTitle(const char* captionTitle) override;
    
    virtual void GetPosition(int32_t* x, int32_t* y) const override;
    virtual void GetSize(int32_t* width, int32_t* height) const override;
    virtual void GetCaptionTitle(char* destCaptionTitle) const override;
    virtual bool HasCaption() const override;
    virtual bool IsResizable() const override;
    virtual bool IsMaximized() const override;
    virtual bool IsMinimized() const override;

/* @section Private variable */
private:
    NSWindow* m_nsWindow;
};
    
} /* namespace macos */

using Window = macos::MacOSWindow;

} /* namespace platform */
} /* namespace tgon */
