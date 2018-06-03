/**
 * @filename    GenericInputManager.h
 * @author      ggomdyu
 * @since       06/02/2018
 */

#pragma once
#include <boost/noncopyable.hpp>

namespace tgon
{

class GenericInputManager :
    private boost::noncopyable
{
/* @section Public destructor */
public:
    virtual ~GenericInputManager() = 0;

/* @section Public method */
public:
    virtual void* CreateKeyboard() = 0;
    virtual void* CreateMouse() = 0;
    virtual void* CreateGamepad() = 0;

    virtual void Update() = 0;
};

} /* namespace tgon */
