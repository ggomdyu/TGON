#include "PrecompiledHeader.h"

#ifndef NOMINMAX
#    define NOMINMAX
#endif
#include <Windows.h>

#include "../Mouse.h"

namespace tgon
{

WindowsMouse::WindowsMouse(OIS::Mouse* nativeMouse) noexcept :
    m_nativeMouse(nativeMouse)
{
}

OIS::Mouse* WindowsMouse::GetNativeMouse() noexcept
{
    return m_nativeMouse;
}

const OIS::Mouse* WindowsMouse::GetNativeMouse() const noexcept
{
    return m_nativeMouse;
}

Mouse::Mouse(InputManager& inputManager) :
    WindowsMouse(inputManager.GetPlatformDependency().CreateNativeMouse())
{
}

void Mouse::Update()
{
    m_currMouseState = m_nativeMouse->getMouseState();
    m_nativeMouse->capture();
}

void Mouse::GetPosition(int32_t* x, int32_t* y)
{
    POINT pt;
    if (::GetCursorPos(&pt) == TRUE)
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

bool Mouse::IsMouseDown(MouseCode mouseCode) const
{
    if (m_currMouseState.buttonDown(static_cast<OIS::MouseButtonID>(mouseCode)) == false &&
        m_nativeMouse->getMouseState().buttonDown(static_cast<OIS::MouseButtonID>(mouseCode)))
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
    if (m_currMouseState.buttonDown(static_cast<OIS::MouseButtonID>(mouseCode)) &&
        m_nativeMouse->getMouseState().buttonDown(static_cast<OIS::MouseButtonID>(mouseCode)))
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
    if (m_currMouseState.buttonDown(static_cast<OIS::MouseButtonID>(mouseCode)) &&
        m_nativeMouse->getMouseState().buttonDown(static_cast<OIS::MouseButtonID>(mouseCode)) == false)
    {
        return true;
    }
    else
    {
        return false;
    }
}

}