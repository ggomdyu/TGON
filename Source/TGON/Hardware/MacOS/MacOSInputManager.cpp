#include "PrecompiledHeader.h"

#include "../InputManager.h"

namespace tgon
{

gainput::InputDeviceMouse* MacOSInputManager::CreateNativeMouse()
{
    return m_inputManager.CreateAndGetDevice<gainput::InputDeviceMouse>();
}

gainput::InputDeviceKeyboard* MacOSInputManager::CreateNativeKeyboard()
{
    return m_inputManager.CreateAndGetDevice<gainput::InputDeviceKeyboard>();
}

gainput::InputDevicePad* MacOSInputManager::CreateNativeGamepad()
{
    return m_inputManager.CreateAndGetDevice<gainput::InputDevicePad>();
}

InputManager::InputManager(const Window& inputTargetWindow) :
    MacOSInputManager()
{
}

InputManager::~InputManager() = default;

void InputManager::Update()
{
    m_inputManager.Update();
}

} /* namespace tgon */
