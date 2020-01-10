#include "PrecompiledHeader.h"

#include "../InputManager.h"

namespace tgon
{

MacOSInputManager::MacOSInputManager(const Window& inputTargetWindow) :
    m_inputManager(std::make_unique<gainput::InputManager>())
{
}

MacOSInputManager::MacOSInputManager(MacOSInputManager&& rhs) noexcept :
    m_inputManager(std::move(rhs.m_inputManager))
{
}

gainput::InputDeviceMouse* MacOSInputManager::CreateNativeMouse()
{
    return m_inputManager->CreateAndGetDevice<gainput::InputDeviceMouse>();
}

gainput::InputDeviceKeyboard* MacOSInputManager::CreateNativeKeyboard()
{
    return m_inputManager->CreateAndGetDevice<gainput::InputDeviceKeyboard>();
}

gainput::InputDevicePad* MacOSInputManager::CreateNativeGamepad()
{
    return m_inputManager->CreateAndGetDevice<gainput::InputDevicePad>();
}

void InputManager::Update()
{
    m_inputManager->Update();
}

} /* namespace tgon */
