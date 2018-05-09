/**
 * @filename    Component.h
 * @author      ggomdyu
 * @since       04/26/2015
 */

#pragma once
#include "Core/Object/Object.h"

#include "ComponentFwd.h"

namespace tgon
{

class TGON_API Component :
	public Object
{
public:
	TGON_RUNTIME_OBJECT(Component)

/* @section Public constructor */
public:
	explicit Component(GameObject* owner) noexcept;

/* @section Public destructor */
public:
    virtual ~Component() override = 0;

/* @section Public method */
public:
    /* @brief   Updates this component. */
	virtual void Update() = 0;

    /* @brief   Sets the owner of component. */
	void SetOwner(GameObject* owner) noexcept;

    /* @brief   Gets the owner of component. */
    GameObject* GetOwner() noexcept;

    /* @brief   Gets the owner of component. */
    const GameObject* GetOwner() const noexcept;

/* @section Private variable */
private:
    GameObject* m_owner;
};

} /* namespace tgon */