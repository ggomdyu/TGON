#include "PrecompiledHeader.h"

#include "WindowsKeyboard.h"
#include "WindowsKeyboardType.h"
#include "WindowsInputManager.h"

namespace tgon
{

WindowsKeyboard::WindowsKeyboard(InputManagerImpl& platformInputManager) :
    m_keyboardDevice(platformInputManager.CreateKeyboardDevice()),
    m_prevKeyStates{}
{
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

const OIS::Keyboard* WindowsKeyboard::GetKeyboardDevice() const noexcept
{
    return m_keyboardDevice;
}

OIS::Keyboard* WindowsKeyboard::GetKeyboardDevice() noexcept
{
    return m_keyboardDevice;
}

} /* namespace tgon */
