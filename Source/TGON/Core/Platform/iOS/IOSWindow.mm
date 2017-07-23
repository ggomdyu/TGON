#import "IOSWindow.h"

namespace tgon
{
namespace platform
{
namespace ios
{

IOSWindow::IOSWindow()
{
}

bool IOSWindow::IsClosed() const noexcept
{
    return m_isClosed;
}

} /* namespace ios */


} /* namespace platform */
} /* namespace tgon */
