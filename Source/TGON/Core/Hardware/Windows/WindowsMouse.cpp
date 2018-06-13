#include "PrecompiledHeader.h"

#include <Windows.h>
#include <OIS.h>

#include "WindowsInputManager.h"
#include "WindowsMouse.h"
#include "WindowsMouseType.h"

namespace tgon
{

MouseImpl::MouseImpl(InputManagerImpl* inputManagerImpl) noexcept :
    m_mouseDevice(inputManagerImpl->CreateMouseDevice()),
    m_prevMouseState(std::make_shared<OIS::MouseState>())
{
}

void MouseImpl::Update()
{
    *m_prevMouseState = m_mouseDevice->getMouseState();
    m_mouseDevice->capture();
}

void MouseImpl::GetPosition(int32_t* x, int32_t* y)
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

bool MouseImpl::IsMouseDown(MouseCode mouseCode) const
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

bool MouseImpl::IsMouseHold(MouseCode mouseCode) const
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

bool MouseImpl::IsMouseUp(MouseCode mouseCode) const
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

const OIS::Mouse* MouseImpl::GetMousedDevice() const
{
    return m_mouseDevice;
}

OIS::Mouse* MouseImpl::GetMouseDevice()
{
    return m_mouseDevice;
}

} /* namespace tgon */
