#include "PrecompiledHeader.h"

#include "../InputManager.h"

namespace tgon
{

MacOSInputManager::MacOSInputManager(const Window& window)
{
}

void MacOSInputManager::Update()
{
    m_inputManager.Update();
}

std::unique_ptr<Keyboard> InputManager::CreateKeyboard()
{
    return std::make_unique<Keyboard>(m_inputManager.CreateAndGetDevice<gainput::InputDeviceKeyboard>());
}

std::unique_ptr<Mouse> InputManager::CreateMouse()
{
    return std::make_unique<Mouse>(m_inputManager.CreateAndGetDevice<gainput::InputDeviceMouse>());
}

std::unique_ptr<Gamepad> InputManager::CreateGamepad()
{
    return std::make_unique<Gamepad>(m_inputManager.CreateAndGetDevice<gainput::InputDevicePad>());
}


} /* namespace tgon */
