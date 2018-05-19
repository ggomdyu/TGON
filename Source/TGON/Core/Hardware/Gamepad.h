/**
 * @filename    Gamepad.h
 * @author      ggomdyu
 * @since       05/15/2018
 */

#pragma once
#include <boost/noncopyable.hpp>
#include <gainput/gainput.h>

namespace tgon
{

class Gamepad final :
    private boost::noncopyable
{
/* @section Public constructor */
public:
    explicit Gamepad(gainput::InputDevicePad* nativeGamepad) noexcept;
    Gamepad(Gamepad&& rhs) noexcept;

/* @section Public operator */
public:
    Gamepad& operator==(Gamepad&& rhs) noexcept;

/* @section Public method */
public:
    void Vibrate(float leftMotor, float rightMotor);

/* @section Private variable */
private:
    gainput::InputDevicePad* m_nativeGamepad;
};

} /* namespace tgon */