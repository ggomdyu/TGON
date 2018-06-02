#include "PrecompiledHeader.h"

#include "Core/Utility/Algorithm.h"

#include "WindowsMouse.h"

namespace tgon
{

WindowsMouse::WindowsMouse(OIS::Mouse* mouseDevice) noexcept :
    m_mouseDevice(mouseDevice)
{
    assert(mouseDevice != nullptr && "mouseDevice can't be nullptr.");
}

void WindowsMouse::Update()
{
    m_mouseDevice->capture();
}

void WindowsMouse::GetPosition(int32_t* x, int32_t* y) const
{
    const OIS::MouseState& mouseState = m_mouseDevice->getMouseState();
}

bool WindowsMouse::IsMouseDown(MouseCode mouseCode) const
{
    const OIS::MouseState& mouseState = m_mouseDevice->getMouseState();

    return false;
}

bool WindowsMouse::IsMouseUp(MouseCode mouseCode) const
{
    const OIS::MouseState& mouseState = m_mouseDevice->getMouseState();

    return false;
}

} /* namespace tgon */
