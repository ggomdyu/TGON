/**
 * @file    Component.h
 * @author  ggomdyu
 * @since   04/26/2015
 */

#pragma once
#include "Core/Object/CoreObject.h"

#include "ComponentUtility.h"

namespace tgon
{

class GameObject;
    
class TGON_API Component :
	public CoreObject
{
public:
    TGON_RUNTIME_OBJECT(Component);

/* @section Public constructor */
public:
    Component(GameObject* owner = nullptr) noexcept;

/* @section Public destructor */
public:
    virtual ~Component() override = default;

/* @section Public method */
public:
    /* @brief   Updates the component. */
    virtual void Update() = 0;
        
    /* @brief   Gets the owner of this component. */
    const GameObject* GetOwner() const noexcept;

    /* @brief   Gets the owner of this component. */
    GameObject* GetOwner() noexcept;

/* @section Private variable */
private:
    GameObject* m_owner;
};

} /* namespace tgon */
