/**
 * @filename    GenericInputManager.h
 * @author      ggomdyu
 * @since       05/18/2018
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

/* @section Public constructor */
public:
    GenericInputManager() = default;

/* @section Public destructor */
public:
    virtual ~GenericInputManager() = default;
};

} /* namespace tgon */