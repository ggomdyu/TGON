#include "PrecompiledHeader.h"

#include "../Keyboard.h"

namespace tgon
{

WindowsKeyboard::WindowsKeyboard(OIS::Keyboard* nativeKeyboard) noexcept :
    m_nativeKeyboard(nativeKeyboard),
    m_currKeyStates{}
{
}

OIS::Keyboard* WindowsKeyboard::GetNativeKeyboard() noexcept
{
    return m_nativeKeyboard;
}

const OIS::Keyboard* WindowsKeyboard::GetNativeKeyboard() const noexcept
{
    return m_nativeKeyboard;
}

Keyboard::Keyboard(InputManager& inputManager) :
    WindowsKeyboard(inputManager.GetPlatformDependency().CreateNativeKeyboard())
{
}

void Keyboard::Update()
{
    m_nativeKeyboard->copyKeyStates(m_currKeyStates.data());
    m_nativeKeyboard->capture();
}

bool Keyboard::IsKeyDown(KeyCode keyCode) const
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

bool Keyboard::IsKeyHold(KeyCode keyCode) const
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

bool Keyboard::IsKeyUp(KeyCode keyCode) const
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

}
