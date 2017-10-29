/**
 * @filename    Object.h
 * @author      ggomdyu
 * @since       03/22/2016
 * @brief       Define class which becomes the base of all objects.
 */

#pragma once
#include "Core/Platform/Config.h"

#include "IRuntimeObject.h"
#include "IRuntimeObjectUtility.h"
#include "ICloneable.h"

namespace tgon
{
namespace object
{

class TGON_API Object :
    public IRuntimeObject,
    public ICloneable
{
public:
    TGON_RUNTIME_OBJECT(Object);

/* @section Public destructor */
public:
    virtual ~Object() = default;

public:
    virtual std::shared_ptr<ICloneable> Clone() const override;
};

} /* namespace object */
} /* namespace tgon */

