/**
 * @filename    IComponent.h
 * @author      ggomdyu
 * @since       04/26/2015
 */

#pragma once
#include "Object.h"

namespace tgon
{
namespace object
{

class ComponentObject;

class TGON_API IComponent :
	public Object
{
public:
	TGON_RUNTIME_OBJECT(IComponent)

/* @section Public constructor */
public:
	explicit IComponent(ComponentObject* owner) noexcept;

/* @section Public method */
public:
    /* @brief   Updates this component. */
	virtual void Update() = 0;

    /* @brief   Sets the owner of this component. */
	void SetOwner(ComponentObject* owner) noexcept;

    /* @brief   Returns owner of this component. */
	ComponentObject* GetOwner() noexcept;

/* @section Private variable */
private:
	ComponentObject* m_owner;
};

} /* namespace object */
} /* namespace tgon */
