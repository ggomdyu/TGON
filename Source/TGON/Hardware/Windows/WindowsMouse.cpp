#include "PrecompiledHeader.h"

#ifndef NOMINMAX
#    define NOMINMAX
#endif
#include <Windows.h>
#include <OIS.h>

#include "WindowsMouse.h"
#include "WindowsInputManager.h"

namespace tgon
{

WindowsMouse::WindowsMouse(OIS::Mouse* nativeMouse) noexcept :
    m_nativeMouse(nativeMouse),
    m_currMouseState(std::make_shared<OIS::MouseState>())
{
}

void WindowsMouse::Update()
{
    *m_currMouseState = m_nativeMouse->getMouseState();
    m_nativeMouse->capture();
}

void WindowsMouse::GetPosition(int32_t* x, int32_t* y)
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

bool WindowsMouse::IsMouseDown(MouseCode mouseCode) const
{
    decltype(auto) currMouseState = m_nativeMouse->getMouseState();

    if (m_currMouseState->buttonDown(static_cast<OIS::MouseButtonID>(mouseCode)) == false &&
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
    decltype(auto) currMouseState = m_nativeMouse->getMouseState();

    if (m_currMouseState->buttonDown(static_cast<OIS::MouseButtonID>(mouseCode)) &&
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
    decltype(auto) currMouseState = m_nativeMouse->getMouseState();

    if (m_currMouseState->buttonDown(static_cast<OIS::MouseButtonID>(mouseCode)) &&
        currMouseState.buttonDown(static_cast<OIS::MouseButtonID>(mouseCode)) == false)
    {
        return true;
    }
    else
    {
        return false;
    }
}

const OIS::Mouse* WindowsMouse::GetNativeMouse() const
{
    return m_nativeMouse;
}

OIS::Mouse* WindowsMouse::GetNativeMouse()
{
    return m_nativeMouse;
}

} /* namespace tgon */
