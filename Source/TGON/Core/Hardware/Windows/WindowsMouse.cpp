#include "PrecompiledHeader.h"

#include <Windows.h>

#include "../Mouse.h"

namespace tgon
{

WindowsMouse::WindowsMouse(OIS::Mouse* mouseDevice) noexcept :
    m_mouseDevice(mouseDevice)
{
    assert(mouseDevice != nullptr && "mouseDevice can't be nullptr.");
}

void WindowsMouse::Update()
{
    m_prevMouseState = m_mouseDevice->getMouseState();
    m_mouseDevice->capture();
}

void WindowsMouse::GetPosition(int32_t* x, int32_t* y) const
{
    POINT pt;
    if (GetCursorPos(&pt) == TRUE)
    {
        *x = static_cast<int32_t>(pt.x);
        *y = static_cast<int32_t>(pt.y);
    }
    else
    {
        *x = 0;
        *y = 0;
    }
}

bool WindowsMouse::IsMouseDown(MouseCode mouseCode) const
{
    const OIS::MouseState& currMouseState = m_mouseDevice->getMouseState();
    
    if (m_prevMouseState.buttonDown(static_cast<OIS::MouseButtonID>(mouseCode)) == false &&
        currMouseState.buttonDown(static_cast<OIS::MouseButtonID>(mouseCode)))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool WindowsMouse::IsMouseHold(MouseCode mouseCode) const
{
    const OIS::MouseState& currMouseState = m_mouseDevice->getMouseState();

    if (m_prevMouseState.buttonDown(static_cast<OIS::MouseButtonID>(mouseCode)) &&
        currMouseState.buttonDown(static_cast<OIS::MouseButtonID>(mouseCode)))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool WindowsMouse::IsMouseUp(MouseCode mouseCode) const
{
    const OIS::MouseState& currMouseState = m_mouseDevice->getMouseState();

    if (m_prevMouseState.buttonDown(static_cast<OIS::MouseButtonID>(mouseCode)) &&
        currMouseState.buttonDown(static_cast<OIS::MouseButtonID>(mouseCode)) == false)
    {
        return true;
    }
    else
    {
        return false;
    }
}

} /* namespace tgon */
