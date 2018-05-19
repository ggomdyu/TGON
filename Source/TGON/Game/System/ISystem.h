/**
 * @filename    ISystem.h
 * @author      ggomdyu
 * @since       07/13/2016
 */

#pragma once
#include <boost/noncopyable.hpp>

#include "Core/Platform/Config.h"

namespace tgon
{

class TGON_API ISystem :
    private boost::noncopyable
{
/* @section Public constructor */
public:
    ISystem() = default;

/* @section Public destructor */
public:
    virtual ~ISystem() = 0;

/* @section Public method */
public:
    virtual void Update() = 0;
};

} /* namespace tgon */