#include "PrecompiledHeader.pch"

#include "Window.h"

namespace tgon
{
namespace core
{

bool Window::IsClosed() const noexcept
{
    return m_isClosed;
}

} /* namespace core */
} /* namespace tgon */