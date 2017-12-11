#include "PrecompiledHeader.pch"
#include "Window.h"

namespace tgon
{
namespace platform
{

bool Window::IsClosed() const noexcept
{
    return m_isClosed;
}

} /* namespace platform */
} /* namespace tgon */