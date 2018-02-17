#include "PrecompiledHeader.pch"

#include "GenericWindow.h"

namespace tgon
{
namespace core
{

GenericWindow::GenericWindow() noexcept :
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

void* GenericWindow::GetNativeWindow()
{
    return const_cast<void*>(static_cast<const GenericWindow&>(*this).GetNativeWindow());
}

I32Point GenericWindow::GetPosition() const
{
    I32Point::ValueType x, y;
    this->GetPosition(&x, &y);

    return I32Point{x, y};
}

I32Extent2D GenericWindow::GetSize() const
{
    I32Extent2D::ValueType width, height;
    this->GetSize(&width, &height);

    return I32Extent2D{width, height};
}

} /* namespace core */
} /* namespace tgon */