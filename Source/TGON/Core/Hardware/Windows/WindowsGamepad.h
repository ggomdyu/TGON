/**
 * @filename    WindowsGamepad.h
 * @author      ggomdyu
 * @since       06/02/2018
 */

#pragma once
#include <cstdint>

#include "Core/Platform/Config.h"

namespace OIS
{

class JoyStick;
class JoyStickState;

} /* namespace OIS */

namespace tgon
{

class WindowsInputManager;

class TGON_API WindowsGamepad final
{
/* @section Public constructor */
public:
    explicit WindowsGamepad(WindowsInputManager& inputManager);

/* @section Public method */
public:
    void Update();
    void Vibrate(float leftMotor, float rightMotor);
    bool IsButtonDown(int32_t buttonNumber) const;
    bool IsButtonHold(int32_t buttonNumber) const;
    bool IsButtonUp(int32_t buttonNumber) const;
    const OIS::JoyStick* GetGamepadDevice() const noexcept;
    OIS::JoyStick* GetGamepadDevice() noexcept;

/* @section Private variable */
private:
    OIS::JoyStick* m_gamepadDevice;
    std::shared_ptr<OIS::JoyStickState> m_prevGamepadState;
};

using PlatformGamepad = WindowsGamepad;

} /* namespace tgon */