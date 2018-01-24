/**
 * @filename    IComponent.h
 * @author      ggomdyu
 * @since       04/26/2015
 */

#pragma once
#include "Core/Object/Object.h"

namespace tgon
{
namespace game
{

class GameObject;

class TGON_API IComponent :
	public core::Object
{
public:
	TGON_RUNTIME_OBJECT(IComponent)

/* @section Public constructor */
public:
	explicit IComponent(GameObject* owner) noexcept;

/* @section Public destructor */
public:
    virtual ~IComponent() override = default;

/* @section Public method */
public:
    /* @brief   Updates this component. */
	virtual void Update() = 0;

    /* @brief   Sets the owner of this component. */
	void SetOwner(GameObject* owner) noexcept;

    /* @brief   Returns owner of this component. */
    GameObject* GetOwner() noexcept;

/* @section Private variable */
private:
    GameObject* m_owner;
};

} /* namespace game */
} /* namespace tgon */