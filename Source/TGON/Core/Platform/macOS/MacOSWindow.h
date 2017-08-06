/**
 * @filename    MacOSWindow.h
 * @author      ggomdyu
 * @since       07/21/2017
 * @brief
 */

#import <Cocoa/Cocoa.h>

#import "../Base/BaseWindow.h"

namespace tgon
{
namespace platform
{
namespace macos
{
    
class TGON_API MacOSWindow :
    public BaseWindow<MacOSWindow>
{
/* @section Ctor/Dtor */
public:
    explicit MacOSWindow(const WindowStyle& windowStyle);
    ~MacOSWindow() = default;

/* @section Public method */
public:
    void Show() {}
    void Hide() {}
    void Quit() {}
    void Maximize() {}
    void Minimize() {}
    void BringToFront() {}
    
    void SetPosition(int32_t x, int32_t y);
    void SetSize(int32_t width, int32_t height);
    void SetCaptionTitle(const char* captionTitle);
    void GetPosition(int32_t* x, int32_t* y) const;
    void GetSize(int32_t* width, int32_t* height) const;
    void GetCaptionTitle(char* destCaptionTitle) const;
    bool HasCaption() const;
    bool IsResizable() const;
    bool IsMaximized() const;
    bool IsMinimized() const;

/* @section Private variable */
private:
    NSWindow* m_nsWindow;
};
    
} /* namespace macos */

using Window = macos::MacOSWindow;

} /* namespace platform */
} /* namespace tgon */
