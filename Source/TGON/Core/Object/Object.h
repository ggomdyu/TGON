/**
 * @filename    Object.h
 * @author      ggomdyu
 * @since       03/22/2016
 * @brief       Define class which becomes the base of all objects.
 */

#pragma once
#include "IRuntimeObject.h"
#include "IRuntimeObjectUtility.h"
#include "ICloneable.h"

#include "Core/Platform/Config.h"

#include <string>

namespace tgon
{
namespace core
{

class TGON_API Object :
    public IRuntimeObject,
    public ICloneable
{
public:
    TGON_RUNTIME_OBJECT(Object);

/* @section Public constructor */
public:
    Object() = default;

/* @section Public destructor */
public:
    virtual ~Object() override = default;
};

} /* namespace core */
} /* namespace tgon */
