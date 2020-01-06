#include "PrecompiledHeader.h"

#include "UIElement.h"

namespace tgon
{

void UIElement::SetScissorRect(const FRect& scissorRect) noexcept
{
    m_scissorRect = scissorRect;
}

void UIElement::EnableScissorRect() noexcept
{
    m_enableScissorRect = true;
}

void UIElement::DisableScissorRect() noexcept
{
    m_enableScissorRect = false;
}

bool UIElement::IsEnableScissorRect() const noexcept
{
    return m_enableScissorRect;
}

const FRect& UIElement::GetScissorRect() const noexcept
{
    return m_scissorRect;
}

} /* namespace tgon */
