#include "PrecompiledHeader.h"

#include "../InputManager.h"

namespace tgon
{

WindowsInputManager::WindowsInputManager(const Window& inputTargetWindow) :
    m_inputManager(std::make_unique<gainput::InputManager>())
{
}

WindowsInputManager::WindowsInputManager(WindowsInputManager&& rhs) noexcept :
    m_inputManager(std::move(m_inputManager))
{
}

gainput::InputDeviceMouse* WindowsInputManager::CreateNativeMouse()
{
    return m_inputManager->CreateAndGetDevice<gainput::InputDeviceMouse>();
}

gainput::InputDeviceKeyboard* WindowsInputManager::CreateNativeKeyboard()
{
    return m_inputManager->CreateAndGetDevice<gainput::InputDeviceKeyboard>();
}

gainput::InputDevicePad* WindowsInputManager::CreateNativeGamepad()
{
    return m_inputManager->CreateAndGetDevice<gainput::InputDevicePad>();
}

void InputManager::Update()
{
    m_inputManager->Update();
}

} /* namespace tgon */
