#include "PrecompiledHeader.h"
#include "GenericWindow.h"

namespace tgon {
namespace window {

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

} /* namespace window */
} /* namespace tgon */