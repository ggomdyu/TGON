#include "PrecompiledHeader.h"

#include "InputManager.h"

namespace tgon
{

InputManager::InputManager() :
    m_inputManager(std::make_unique<gainput::InputManager>())
{
}
    
void InputManager::Update()
{
    m_inputManager->Update();
}
    
std::unique_ptr<Mouse> InputManager::CreateMouse() const
{
    auto mouseDevice = m_inputManager->CreateAndGetDevice<gainput::InputDeviceMouse>();
    return std::make_unique<Mouse>(mouseDevice);
}
    
std::unique_ptr<Keyboard> InputManager::CreateKeyboard() const
{
    auto keyboardDevice = m_inputManager->CreateAndGetDevice<gainput::InputDeviceKeyboard>();
    return std::make_unique<Keyboard>(keyboardDevice);
}

} /* namespace tgon */
