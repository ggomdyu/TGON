#include "PrecompiledHeader.h"

#include <gainput/gainput.h>

#include "MacOSInputManager.h"

namespace tgon
{

MacOSInputManager::MacOSInputManager(const std::shared_ptr<Window>& window) :
    m_inputManager(std::make_unique<gainput::InputManager>())
{
}
    
MacOSInputManager::~MacOSInputManager() = default;

void InputManagerImpl::Update()
{
    m_inputManager->Update();
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

} /* namespace tgon */
