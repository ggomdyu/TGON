#include "PrecompiledHeader.h"

#include "Core/Utility/Algorithm.h"

#include "Mouse.h"

namespace tgon
{

//Mouse::Mouse(gainput::InputDeviceMouse* nativeMouse, gainput::InputMap& inputMap) :
//    m_nativeMouse(nativeMouse),
//    m_inputMap(inputMap)
//{
//    inputMap.MapBool(UnderlyingCast(KeyCode::Button0), m_deviceId, gainput::MouseButton0);
//    inputMap.MapBool(UnderlyingCast(KeyCode::Button1), m_deviceId, gainput::MouseButton1);
//    inputMap.MapBool(UnderlyingCast(KeyCode::Button2), m_deviceId, gainput::MouseButton2);
//    inputMap.MapBool(UnderlyingCast(KeyCode::Button3), m_deviceId, gainput::MouseButton3);
//    inputMap.MapBool(UnderlyingCast(KeyCode::Button4), m_deviceId, gainput::MouseButton4);
//    inputMap.MapBool(UnderlyingCast(KeyCode::Button5), m_deviceId, gainput::MouseButton5);
//    inputMap.MapBool(UnderlyingCast(KeyCode::Button6), m_deviceId, gainput::MouseButton6);
//    inputMap.MapBool(UnderlyingCast(KeyCode::Button7), m_deviceId, gainput::MouseButton7);
//    inputMap.MapBool(UnderlyingCast(KeyCode::Button8), m_deviceId, gainput::MouseButton8);
//    inputMap.MapBool(UnderlyingCast(KeyCode::Button9), m_deviceId, gainput::MouseButton9);
//    inputMap.MapBool(UnderlyingCast(KeyCode::Button10), m_deviceId, gainput::MouseButton10);
//    inputMap.MapBool(UnderlyingCast(KeyCode::Button11), m_deviceId, gainput::MouseButton11);
//    inputMap.MapBool(UnderlyingCast(KeyCode::Button12), m_deviceId, gainput::MouseButton12);
//    inputMap.MapBool(UnderlyingCast(KeyCode::Button13), m_deviceId, gainput::MouseButton13);
//    inputMap.MapBool(UnderlyingCast(KeyCode::Button14), m_deviceId, gainput::MouseButton14);
//    inputMap.MapBool(UnderlyingCast(KeyCode::Button15), m_deviceId, gainput::MouseButton15);
//    inputMap.MapBool(UnderlyingCast(KeyCode::Button16), m_deviceId, gainput::MouseButton16);
//    inputMap.MapBool(UnderlyingCast(KeyCode::Button17), m_deviceId, gainput::MouseButton17);
//    inputMap.MapBool(UnderlyingCast(KeyCode::Button18), m_deviceId, gainput::MouseButton18);
//    inputMap.MapBool(UnderlyingCast(KeyCode::Button19), m_deviceId, gainput::MouseButton19);
//    inputMap.MapBool(UnderlyingCast(KeyCode::Button20), m_deviceId, gainput::MouseButton20);
//}
//
//Mouse::Mouse(Mouse&& rhs) noexcept :
//    m_deviceId(rhs.m_deviceId)
//{
//    rhs.m_deviceId = 0;
//}
//
//Mouse& Mouse::operator==(Mouse&& rhs) noexcept
//{
//    m_deviceId = rhs.m_deviceId;
//    
//    rhs.m_deviceId = 0;
//}
//
//bool Mouse::IsKeyDown(KeyCode keyCode) const noexcept
//{
//    return false;
//}
//
//bool Mouse::IsKeyDown(KeyCode keyCode) noexcept
//{
//    return false;
//}
//
//bool Mouse::IsKeyUp(KeyCode keyCode) noexcept
//{
//    return false;
//}
//
//void Mouse::UpdateKeyStates()
//{
//}

} /* namespace tgon */
