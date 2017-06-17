#include "PrecompiledHeader.h"
#include "GenericWindow.h"

namespace tgon
{
namespace platform
{

GenericWindow::GenericWindow() :
    m_isClosed(false)
{
}

GenericWindow::~GenericWindow()
{
    m_isClosed = true;
}

bool GenericWindow::IsClosed() const noexcept
{
    return m_isClosed;
}

} /* namespace platform */
} /* namespace tgon */
