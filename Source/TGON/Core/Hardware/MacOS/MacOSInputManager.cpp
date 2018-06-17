#include "PrecompiledHeader.h"

#include <gainput/gainput.h>

#include "MacOSInputManager.h"

namespace tgon
{

InputManagerImpl::InputManagerImpl(std::shared_ptr<Window> window) :
    m_inputManager(std::make_unique<gainput::InputManager>())
{
}
    
InputManagerImpl::~InputManagerImpl() = default;

void InputManagerImpl::Update()
{
    m_inputManager->Update();
}
    
gainput::InputDeviceMouse* InputManagerImpl::CreateMouseDevice()
{
    return m_inputManager->CreateAndGetDevice<gainput::InputDeviceMouse>();
}

gainput::InputDeviceKeyboard* InputManagerImpl::CreateKeyboardDevice()
{
    return m_inputManager->CreateAndGetDevice<gainput::InputDeviceKeyboard>();
}

gainput::InputDevicePad* InputManagerImpl::CreateGamepadDevice()
{
    return m_inputManager->CreateAndGetDevice<gainput::InputDevicePad>();
}

} /* namespace tgon */
