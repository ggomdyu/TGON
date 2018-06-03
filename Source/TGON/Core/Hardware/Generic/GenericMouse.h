/**
 * @filename    GenericMouse.h
 * @author      ggomdyu
 * @since       06/02/2018
 */

#pragma once
#include <boost/noncopyable.hpp>

#include "Core/Math/Point.h"

namespace tgon
{

class GenericMouse :
    private boost::noncopyable
{
/* @section Public type */
public:
    enum class MouseCode;

/* @section Public destructor */
public:
    virtual ~GenericMouse() = 0;

/* @section Public method */
public:
    virtual void Update() = 0;
    virtual void GetPosition(int32_t* x, int32_t* y) const = 0;
    I32Point GetPosition() const;
    virtual bool IsMouseDown(MouseCode mouseCode) const = 0;
    virtual bool IsMouseHold(MouseCode mouseCode) const = 0;
    virtual bool IsMouseUp(MouseCode mouseCode) const = 0;
//    float GetAxisX() const;
//    float GetAxisY() const; 
};

} /* namespace tgon */
