#include "PrecompiledHeader.h"

#include "../Gamepad.h"

namespace tgon
{

WindowsGamepad::WindowsGamepad(OIS::JoyStick* nativeGamepad) noexcept :
    m_nativeGamepad(nativeGamepad)
{
}

const OIS::JoyStick* WindowsGamepad::GetNativeGamepad() const noexcept
{
    return m_nativeGamepad;
}

OIS::JoyStick* WindowsGamepad::GetNativeGamepad() noexcept
{
    return m_nativeGamepad;
}

Gamepad::Gamepad(InputManager& inputManager) :
    WindowsGamepad(inputManager.GetPlatformDependency().CreateNativeGamepad())
{
}

PlatformGamepad& Gamepad::GetPlatformDependency() noexcept
{
    return *this;
}

const PlatformGamepad& Gamepad::GetPlatformDependency() const noexcept
{
    return *this;
}

void Gamepad::Update()
{
    m_prevGamepadState = m_nativeGamepad->getJoyStickState();
    m_nativeGamepad->capture();
}

void Gamepad::Vibrate(float leftMotor, float rightMotor)
{
    //auto a = m_gamepadDevice->getNumberOfComponents(OIS::OIS_Axis);
    //auto b = m_gamepadDevice->getNumberOfComponents(OIS::OIS_Slider);
    //auto c = m_gamepadDevice->getNumberOfComponents(OIS::OIS_POV);
    //auto d = m_gamepadDevice->getNumberOfComponents(OIS::OIS_Button);
    //auto e = m_gamepadDevice->getNumberOfComponents(OIS::OIS_Vector3);
    //auto gamepadState = m_gamepadDevice->getJoyStickState();
    //int i = 0;
    ///*for (bool axes : gamepadState.mButtons)
    //{
    //    if (axes == false)
    //    {
    //    ++i;
    //        continue;
    //    }

    //    auto str = std::wstring(L"Axis") + std::to_wstring(i++) + L" " + std::to_wstring(axes) + L"\n";
    //    OutputDebugStringW(str.c_str());
    //}*/

    //for (auto pov : gamepadState.mPOV)
    //{
    //    auto str = std::wstring(L"Pov Direction") + std::to_wstring(i++) + L" " + std::to_wstring(pov.direction) + L"\n";
    //    OutputDebugStringW(str.c_str());
    //}
}

bool Gamepad::IsButtonDown(int32_t buttonNumber) const
{
    const OIS::JoyStickState& currGamepadState = m_nativeGamepad->getJoyStickState();
    if (currGamepadState.mButtons.size() <= size_t(buttonNumber))
    {
        return false;
    }

    if (m_prevGamepadState.mButtons[buttonNumber] == false && 
        currGamepadState.mButtons[buttonNumber])
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Gamepad::IsButtonHold(int32_t buttonNumber) const
{
    const OIS::JoyStickState& currGamepadState = m_nativeGamepad->getJoyStickState();
    if (currGamepadState.mButtons.size() <= static_cast<size_t>(buttonNumber))
    {
        return false;
    }

    if (m_prevGamepadState.mButtons[buttonNumber] &&
        currGamepadState.mButtons[buttonNumber])
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Gamepad::IsButtonUp(int32_t buttonNumber) const
{
    const OIS::JoyStickState& currGamepadState = m_nativeGamepad->getJoyStickState();
    if (currGamepadState.mButtons.size() <= size_t(buttonNumber))
    {
        return false;
    }

    if (m_prevGamepadState.mButtons[buttonNumber] &&
        currGamepadState.mButtons[buttonNumber] == false)
    {
        return true;
    }
    else
    {
        return false;
    }
}

}
