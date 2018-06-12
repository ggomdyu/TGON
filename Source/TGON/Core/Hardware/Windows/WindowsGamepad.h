/**
 * @filename    WindowsGamepad.h
 * @author      ggomdyu
 * @since       06/02/2018
 */

#pragma once
#include <cstdint>

#include "Core/Platform/Config.h"

#include "WindowsGamepadFwd.h"

namespace tgon
{

class TGON_API GamepadImpl final
{
/* @section Public constructor */
public:
    explicit GamepadImpl(InputManagerImpl* inputManager);

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

} /* namespace tgon */