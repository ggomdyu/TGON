/**
 * @filename    ComponentObject.h
 * @author      ggomdyu
 * @since       03/22/2016
 */

#pragma once
#include <vector>
#include <memory>

#include "Object.h"

namespace tgon
{
namespace object
{

class IComponent;

class TGON_API ComponentObject :
	public Object
{
public:
    TGON_RUNTIME_OBJECT(ComponentObject);

/* @section Public constructor */
public:
	ComponentObject() = default;

/* @section Public destructor */
public:
	virtual ~ComponentObject() = default;

/* @section Public method */
public:
    /* @brief   Updates all component this object owned. */
    virtual void Update();

/* @section Private variable */
private:
    std::vector<std::unique_ptr<IComponent>> m_components;
};

} /* namespace object */
} /* namespace tgon */
