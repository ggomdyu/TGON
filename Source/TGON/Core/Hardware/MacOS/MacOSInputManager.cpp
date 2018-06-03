#include "PrecompiledHeader.h"

#include "MacOSInputManager.h"

namespace tgon
{

MacOSInputManager::MacOSInputManager(const std::shared_ptr<GenericWindow>& window)
{
}

void* MacOSInputManager::CreateKeyboard()
{
    auto keyboardDevice = m_inputManager.CreateAndGetDevice<gainput::InputDeviceKeyboard>();
    return keyboardDevice;
}

void* MacOSInputManager::CreateMouse()
{
    auto mouseDevice = m_inputManager.CreateAndGetDevice<gainput::InputDeviceMouse>();
    return mouseDevice;
}

void* MacOSInputManager::CreateGamepad()
{
    auto gamepadDevice = m_inputManager.CreateAndGetDevice<gainput::InputDevicePad>();
    return gamepadDevice;
}

void MacOSInputManager::Update()
{
    m_inputManager.Update();
}

} /* namespace tgon */
