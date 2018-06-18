/**
 * @file    Object.h
 * @author  ggomdyu
 * @since   03/22/2016
 * @brief   Define class which becomes the base of all objects.
 */

#pragma once
#include <string>

#include "Core/Platform/Config.h"

#include "ICloneable.h"
#include "IRuntimeObject.h"
#include "IRuntimeObjectUtility.h"

namespace tgon
{

class TGON_API Object :
    public IRuntimeObject
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

} /* namespace tgon */
