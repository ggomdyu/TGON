#import "iOSWindow.h"


namespace tgon
{
namespace platform
{
namespace ios
{

iOSWindow::iOSWindow(UIWindow* uiWindow) :
    m_uiWindow(uiWindow)
{
}
    
bool iOSWindow::IsClosed() const noexcept
{
    return m_isClosed;
}

} /* namespace ios */
} /* namespace platform */
} /* namespace tgon */
