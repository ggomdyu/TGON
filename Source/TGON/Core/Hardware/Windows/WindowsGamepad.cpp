#include "PrecompiledHeader.h"


#include "WindowsGamepad.h"
#include "WindowsGamepadType.h"
#include "WindowsInputManager.h"

namespace tgon
{

GamepadImpl::GamepadImpl(InputManagerImpl& inputManager) :
    m_gamepadDevice(inputManager.CreateGamepadDevice())
{
}

void GamepadImpl::Update()
{
    m_prevGamepadState = m_gamepadDevice->getJoyStickState();
    m_gamepadDevice->capture();
}

void GamepadImpl::Vibrate(float leftMotor, float rightMotor)
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

    //int n = 3;
}

bool GamepadImpl::IsButtonDown(int32_t buttonNumber) const
{
    decltype(auto) currGamepadState = m_gamepadDevice->getJoyStickState();
    if (currGamepadState.mButtons.size() <= buttonNumber)
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

bool GamepadImpl::IsButtonHold(int32_t buttonNumber) const
{
    decltype(auto) currGamepadState = m_gamepadDevice->getJoyStickState();
    if (currGamepadState.mButtons.size() <= buttonNumber)
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

bool GamepadImpl::IsButtonUp(int32_t buttonNumber) const
{
    decltype(auto) currGamepadState = m_gamepadDevice->getJoyStickState();
    if (currGamepadState.mButtons.size() <= buttonNumber)
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

const OIS::JoyStick* GamepadImpl::GetGamepadDevice() const noexcept
{
    return m_gamepadDevice;
}

OIS::JoyStick* GamepadImpl::GetGamepadDevice() noexcept
{
    return m_gamepadDevice;
}

} /* namespace tgon */
