#include "PrecompiledHeader.h"

#include <OIS.h>

#include "WindowsKeyboard.h"
#include "WindowsKeyboardType.h"

namespace tgon
{

WindowsKeyboard::WindowsKeyboard(OIS::Keyboard* nativeKeyboard) :
    m_nativeKeyboard(nativeKeyboard),
    m_currKeyStates{}
{
}

void WindowsKeyboard::Update()
{
    m_nativeKeyboard->copyKeyStates(m_currKeyStates);
    m_nativeKeyboard->capture();
}

bool WindowsKeyboard::IsKeyDown(KeyCode keyCode) const
{
    if ((m_currKeyStates[static_cast<char>(keyCode)] == 0) &&
        m_nativeKeyboard->isKeyDown(static_cast<OIS::KeyCode>(keyCode)))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool WindowsKeyboard::IsKeyHold(KeyCode keyCode) const
{
    if ((m_currKeyStates[static_cast<char>(keyCode)] == 1) &&
        m_nativeKeyboard->isKeyDown(static_cast<OIS::KeyCode>(keyCode)))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool WindowsKeyboard::IsKeyUp(KeyCode keyCode) const
{
    if ((m_currKeyStates[static_cast<char>(keyCode)] == 1) &&
        m_nativeKeyboard->isKeyDown(static_cast<OIS::KeyCode>(keyCode)) == false)
    {
        return true;
    }
    else
    {
        return false;
    }
}

const OIS::Keyboard* WindowsKeyboard::GetNativeKeyboard() const noexcept
{
    return m_nativeKeyboard;
}

OIS::Keyboard* WindowsKeyboard::GetNativeKeyboard() noexcept
{
    return m_nativeKeyboard;
}

} /* namespace tgon */
