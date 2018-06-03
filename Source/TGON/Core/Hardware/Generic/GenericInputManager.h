/**
 * @filename    GenericInputManager.h
 * @author      ggomdyu
 * @since       06/02/2018
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
    virtual void Update() = 0;
};

} /* namespace tgon */
