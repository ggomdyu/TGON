#include "PrecompiledHeader.h"

#include "../Keyboard.h"

namespace tgon
{
    
WindowsKeyboard::WindowsKeyboard(OIS::Keyboard* keyboardDevice) noexcept :
    m_keyboardDevice(keyboardDevice),
    m_prevKeyStates{}
{
    assert(keyboardDevice != nullptr && "keyboardDevice can't be nullptr.");
}

void WindowsKeyboard::Update()
{
    m_keyboardDevice->copyKeyStates(m_prevKeyStates);
    m_keyboardDevice->capture();
}

bool WindowsKeyboard::IsKeyDown(KeyCode keyCode) const
{
    if ((m_prevKeyStates[static_cast<char>(keyCode)] == 0) &&
        m_keyboardDevice->isKeyDown(static_cast<OIS::KeyCode>(keyCode)))
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
    if ((m_prevKeyStates[static_cast<char>(keyCode)] == 1) &&
        m_keyboardDevice->isKeyDown(static_cast<OIS::KeyCode>(keyCode)))
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
    if ((m_prevKeyStates[static_cast<char>(keyCode)] == 1) &&
        m_keyboardDevice->isKeyDown(static_cast<OIS::KeyCode>(keyCode)) == false)
    {
        return true;
    }
    else
    {
        return false;
    }
}

} /* namespace tgon */
