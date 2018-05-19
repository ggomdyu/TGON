/**
 * @filename    Keyboard.h
 * @author      ggomdyu
 * @since       05/15/2018
 */

#pragma once
#include <boost/noncopyable.hpp>

#include "InputManager.h"

namespace tgon
{

class Keyboard final :
    private boost::noncopyable
{
/* @section Public constructor */
public:
    explicit Keyboard(InputManager* inputManager);
    Keyboard(Keyboard&& rhs) noexcept;

/* @section Public operator */
public:
    Keyboard& operator==(Keyboard&& rhs) noexcept;
    
/* @section Public method */
public:

/* @section Private variable */
private:
    gainput::DeviceId m_deviceId;
};

} /* namespace tgon */