#include "PrecompiledHeader.h"

#include "Misc/Algorithm.h"

#include "Mouse.h"

namespace tgon
{

Mouse::Mouse(gainput::InputDeviceMouse* nativeMouse) noexcept :
    m_nativeMouse(nativeMouse)
{
}

Mouse::Mouse(Mouse&& rhs) noexcept :
    m_nativeMouse(rhs.m_nativeMouse)
{
    rhs.m_nativeMouse = nullptr;
}

Mouse& Mouse::operator=(Mouse&& rhs) noexcept
{
    m_nativeMouse = rhs.m_nativeMouse;

    rhs.m_nativeMouse = nullptr;

    return *this;
}

void Mouse::Update()
{
}

I32Vector2 Mouse::GetPosition()
{
    I32Vector2 pt;
    Mouse::GetPosition(&pt.x, &pt.y);

    return pt;
}

void Mouse::GetPosition(int32_t* x, int32_t* y)
{
    // TODO: Impl
}

bool Mouse::IsMouseDown(MouseCode mouseCode) const
{
    auto castedMouseCode = UnderlyingCast(mouseCode);

    if (m_nativeMouse->GetBoolPrevious(castedMouseCode) == false &&
        m_nativeMouse->GetBool(castedMouseCode))
    {
        return true;
    }
    else
    {
        return false;
    }
}
    
bool Mouse::IsMouseHold(MouseCode mouseCode) const
{
    auto castedMouseCode = UnderlyingCast(mouseCode);

    if (m_nativeMouse->GetBoolPrevious(castedMouseCode) &&
        m_nativeMouse->GetBool(castedMouseCode))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Mouse::IsMouseUp(MouseCode mouseCode) const
{
    auto castedMouseCode = UnderlyingCast(mouseCode);

    if (m_nativeMouse->GetBoolPrevious(castedMouseCode) &&
        m_nativeMouse->GetBool(castedMouseCode) == false)
    {
        return true;
    }
    else
    {
        return false;
    }
}

} /* namespace tgon */
