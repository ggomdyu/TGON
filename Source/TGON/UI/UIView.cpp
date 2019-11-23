#include "PrecompiledHeader.h"

#include "UIView.h"

namespace tgon
{

void UIView::SetFrame(const I32Rect& frame) noexcept
{
    m_frame = frame;
}

void UIView::SetBounds(const I32Rect& bounds) noexcept
{
    m_bounds = bounds;
}

const I32Rect& UIView::GetFrame() const noexcept
{
    return m_frame;
}

const I32Rect& UIView::GetBounds() const noexcept
{
    return m_bounds;
}

} /* namespace tgon */
