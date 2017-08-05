#include "PrecompiledHeader.pch"
#include "BaseWindow.h"

namespace tgon
{
namespace platform
{

BaseWindow::BaseWindow() :
    m_isClosed(false)
{
}

BaseWindow::~BaseWindow()
{
    m_isClosed = true;
}

bool BaseWindow::IsClosed() const noexcept
{
    return m_isClosed;
}

} /* namespace platform */
} /* namespace tgon */