#include "PrecompiledHeader.h"

#include <Windows.h>
#include <OIS.h>

#include "WindowsMouse.h"
#include "WindowsMouseType.h"
#include "WindowsInputManager.h"

namespace tgon
{

WindowsMouse::WindowsMouse(WindowsInputManager& platformInputManager) noexcept :
    m_mouseDevice(platformInputManager.CreateMouseDevice()),
    m_prevMouseState(std::make_shared<OIS::MouseState>())
{
}

void WindowsMouse::Update()
{
    *m_prevMouseState = m_mouseDevice->getMouseState();
    m_mouseDevice->capture();
}

void WindowsMouse::GetPosition(int32_t* x, int32_t* y)
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
    decltype(auto) currMouseState = m_mouseDevice->getMouseState();

    if (m_prevMouseState->buttonDown(static_cast<OIS::MouseButtonID>(mouseCode)) == false &&
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
    decltype(auto) currMouseState = m_mouseDevice->getMouseState();

    if (m_prevMouseState->buttonDown(static_cast<OIS::MouseButtonID>(mouseCode)) &&
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
    decltype(auto) currMouseState = m_mouseDevice->getMouseState();

    if (m_prevMouseState->buttonDown(static_cast<OIS::MouseButtonID>(mouseCode)) &&
        currMouseState.buttonDown(static_cast<OIS::MouseButtonID>(mouseCode)) == false)
    {
        return true;
    }
    else
    {
        return false;
    }
}

const OIS::Mouse* WindowsMouse::GetMousedDevice() const
{
    return m_mouseDevice;
}

OIS::Mouse* WindowsMouse::GetMouseDevice()
{
    return m_mouseDevice;
}

} /* namespace tgon */
