#include "PrecompiledHeader.h"

#include "Core/Utility/Algorithm.h"

#include "WindowsKeyboard.h"

namespace tgon
{
    
WindowsKeyboard::WindowsKeyboard(OIS::Keyboard* keyboardDevice) noexcept :
    m_keyboardDevice(keyboardDevice)
{
    assert(keyboardDevice != nullptr && "keyboardDevice can't be nullptr.");
}

void WindowsKeyboard::Update()
{
    m_keyboardDevice->capture();
}

bool WindowsKeyboard::IsKeyDown(KeyCode keyCode) const
{
    if (m_keyboardDevice->isKeyDown(static_cast<OIS::KeyCode>(keyCode)))
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
    return false;
}

} /* namespace tgon */
