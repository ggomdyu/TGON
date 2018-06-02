/**
 * @filename    GenericInputManager.h
 * @author      ggomdyu
 * @since       05/15/2018
 */

#pragma once
#include <boost/noncopyable.hpp>

#include "Core/Object/Object.h"

namespace tgon
{

class GenericInputManager :
    public Object,
    private boost::noncopyable
{
public:
    TGON_RUNTIME_OBJECT(GenericInputManager);

/* @section Public destructor */
public:
    virtual ~GenericInputManager() = 0;

/* @section Public method */
public:
    virtual void* CreateKeyboard() const = 0;
    virtual void* CreateMouse() const = 0;
    virtual void* CreateGamepad() const = 0;

    virtual void Update() = 0;
};

} /* namespace tgon */