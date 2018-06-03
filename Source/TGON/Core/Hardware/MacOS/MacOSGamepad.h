/**
 * @filename    MacOSGamepad.h
 * @author      ggomdyu
 * @since       06/03/2018
 */

#pragma once
#include "MacOSGamepadType.h"

namespace tgon
{

class MacOSGamepad :
    public GenericGamepad
{
/* @section Public constructor */
public:
    explicit MacOSGamepad(void* gamepadDevice) noexcept;
    
/* @section Public destructor */
public:
    virtual ~MacOSGamepad() override = default;

/* @section Public method */
public:
    virtual void Update() final override;
    virtual void Vibrate(float leftMotor, float rightMotor) final override;

/* @section Private variable */
private:
    gainput::InputDevicePad* m_gamepadDevice;
};
    
using Gamepad = MacOSGamepad;

} /* namespace tgon */
