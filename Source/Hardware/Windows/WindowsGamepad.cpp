#include "PrecompiledHeader.h"

//#include <gainput/gainput.h>
//
//#include "../Gamepad.h"
//
//namespace tgon
//{
//
//WindowsGamepad::WindowsGamepad(gainput::InputDevicePad* nativeGamepad) :
//    m_nativeGamepad(nativeGamepad)
//{
//}
//
//const gainput::InputDevicePad* WindowsGamepad::GetNativeGamepad() const noexcept
//{
//    return m_nativeGamepad;
//}
//
//gainput::InputDevicePad* WindowsGamepad::GetNativeGamepad() noexcept
//{
//    return m_nativeGamepad;
//}
//    
//Gamepad::Gamepad(InputManager& inputManager) :
//    WindowsGamepad(inputManager.GetPlatformDependency().CreateNativeGamepad())
//{
//}
//    
//void Gamepad::Update()
//{
//}
//    
//void Gamepad::Vibrate(float leftMotor, float rightMotor)
//{
//    m_nativeGamepad->Vibrate(leftMotor, rightMotor);
//}
//    
//bool Gamepad::IsButtonDown(int32_t buttonNumber) const
//{
//    return false;
//}
//    
//bool Gamepad::IsButtonHold(int32_t buttonNumber) const
//{
//    return false;
//}
//    
//bool Gamepad::IsButtonUp(int32_t buttonNumber) const
//{
//    return false;
//}
//
//} /* namespace tgon */
