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

bool BaseWindow::HasCaption() const
{
    return false;
}

bool BaseWindow::IsResizable() const
{
    return false;
}

bool BaseWindow::IsMaximized() const
{
    return false;
}

bool BaseWindow::IsMinimized() const
{
    return false;
}

bool BaseWindow::IsClosed() const noexcept
{
    return m_isClosed;
}

} /* namespace platform */
} /* namespace tgon */