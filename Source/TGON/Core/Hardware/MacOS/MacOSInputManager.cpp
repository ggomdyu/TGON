#include "PrecompiledHeader.h"

#include <gainput/gainput.h>

#include "MacOSInputManager.h"

namespace tgon
{

MacOSInputManager::MacOSInputManager(std::shared_ptr<Window> window) :
    m_inputManager(std::make_unique<gainput::InputManager>())
{
}
    
MacOSInputManager::~MacOSInputManager() = default;

void MacOSInputManager::Update()
{
    m_inputManager->Update();
}
    
gainput::InputDeviceMouse* MacOSInputManager::CreateMouseDevice()
{
    return m_inputManager->CreateAndGetDevice<gainput::InputDeviceMouse>();
}

gainput::InputDeviceKeyboard* MacOSInputManager::CreateKeyboardDevice()
{
    return m_inputManager->CreateAndGetDevice<gainput::InputDeviceKeyboard>();
}

gainput::InputDevicePad* MacOSInputManager::CreateGamepadDevice()
{
    return m_inputManager->CreateAndGetDevice<gainput::InputDevicePad>();
}

} /* namespace tgon */
