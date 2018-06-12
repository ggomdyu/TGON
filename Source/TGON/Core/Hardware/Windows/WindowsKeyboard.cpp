#include "PrecompiledHeader.h"

#include "WindowsKeyboard.h"
#include "WindowsKeyboardType.h"
#include "WindowsInputManager.h"

namespace tgon
{

KeyboardImpl::KeyboardImpl(InputManagerImpl* inputManagerImpl) :
    m_keyboardDevice(inputManagerImpl->CreateKeyboard()),
    m_prevKeyStates{}
{
}

void KeyboardImpl::Update()
{
    m_keyboardDevice->copyKeyStates(m_prevKeyStates);
    m_keyboardDevice->capture();
}

bool KeyboardImpl::IsKeyDown(KeyCode keyCode) const
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

bool KeyboardImpl::IsKeyHold(KeyCode keyCode) const
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

bool KeyboardImpl::IsKeyUp(KeyCode keyCode) const
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

const OIS::Keyboard* KeyboardImpl::GetKeyboardDevice() const noexcept
{
    return m_keyboardDevice;
}

OIS::Keyboard* KeyboardImpl::GetKeyboardDevice() noexcept
{
    return m_keyboardDevice;
}

} /* namespace tgon */
