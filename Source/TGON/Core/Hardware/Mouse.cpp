#include "PrecompiledHeader.h"

#include "Core/Utility/Algorithm.h"

#include "Mouse.h"

namespace tgon
{

Mouse::Mouse(gainput::InputDeviceMouse* mouseDevice) noexcept :
    m_mouseDevice(mouseDevice)
{
    assert(mouseDevice != nullptr && "mouseDevice can't be nullptr.");
}

bool Mouse::IsMouseDown(MouseCode mouseCode) const
{
    auto castedMouseCode = UnderlyingCast(mouseCode);
    if (m_mouseDevice->GetBoolPrevious(castedMouseCode) == false &&
        m_mouseDevice->GetBool(castedMouseCode))
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
    if (m_mouseDevice->GetBoolPrevious(castedMouseCode) &&
        m_mouseDevice->GetBool(castedMouseCode) == false)
    {
        return true;
    }
    else
    {
        return false;
    }
}

} /* namespace tgon */
