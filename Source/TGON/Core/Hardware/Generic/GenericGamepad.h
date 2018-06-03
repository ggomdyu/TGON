/**
 * @filename    GenericGamepad.h
 * @author      ggomdyu
 * @since       06/03/2018
 */

#pragma once
#include <boost/noncopyable.hpp>

namespace tgon
{

class GenericGamepad :
    private boost::noncopyable
{
/* @section Public type */
public:
/* @section Public destructor */
public:
    virtual ~GenericGamepad() = 0;

/* @section Public method */
public:
    virtual void Update() = 0;
    virtual void Vibrate(float leftMotor, float rightMotor) = 0;
    virtual bool IsButtonDown(int32_t buttonNumber) const = 0;
    virtual bool IsButtonHold(int32_t buttonNumber) const = 0;
    virtual bool IsButtonUp(int32_t buttonNumber) const = 0;
};

} /* namespace tgon */
