/**
 * @filename    IOSScreen.h
 * @author      ggomdyu
 * @since       06/10/2017
 * @brief
 */

#import "Core/Platform/Generic/GenericWindow.h"

namespace tgon
{
namespace platform
{
namespace ios
{
    
class TGON_API IOSWindow :
    public GenericWindow
{
/* @section Ctor/Dtor */
public:
    explicit IOSWindow();
    virtual ~IOSWindow() = default;

/* @section Public method */
public:
    virtual void Show() {}
    virtual void Hide() {}
    virtual void Quit() {}
    
    virtual void SetPosition(int32_t x, int32_t y) {}
    virtual void SetExtent(int32_t width, int32_t height) {}
    virtual void SetCaption(const char* caption) {}
    
    virtual void GetPosition(int32_t* x, int32_t* y) const {}
    virtual void GetExtent(int32_t* width, int32_t* height) const {}
    virtual void GetCaptionText(char* caption) const {}
    virtual bool HasCaption() const { return false; }
    virtual bool IsResizable() const { return false; }
    virtual bool IsHidden() const { return false; }
    bool IsClosed() const noexcept;

/* @section Private variable */
private:
};
    
} /* namespace ios */
} /* namespace platform */
} /* namespace tgon */
