/**
 * @filename    WindowsGamepad.h
 * @author      ggomdyu
 * @since       06/02/2018
 */

#pragma once
#include "WindowsGamepadType.h"

namespace tgon
{

enum class GamepadPov
{
    Left,
    Up,
    Down,
    Right,
    LeftUp,
    LeftDown,
};

class WindowsGamepad :
    public GenericGamepad
{
/* @section Public constructor */
public:
    explicit WindowsGamepad(OIS::JoyStick* gamepadDevice) noexcept;

/* @section Public destructor */
public:
    virtual ~WindowsGamepad() override = default;

/* @section Public method */
public:
    virtual void Update() final override;
    virtual void Vibrate(float leftMotor, float rightMotor) final override;
    virtual bool IsButtonDown(int32_t buttonNumber) const final;
    virtual bool IsButtonHold(int32_t buttonNumber) const final;
    virtual bool IsButtonUp(int32_t buttonNumber) const final;

/* @section Private variable */
private:
    OIS::JoyStick* m_gamepadDevice;
    OIS::JoyStickState m_prevGamepadState;
};

using Gamepad = WindowsGamepad;

} /* namespace tgon */
