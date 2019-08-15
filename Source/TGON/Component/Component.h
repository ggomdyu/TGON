/**
 * @file    Component.h
 * @author  ggomdyu
 * @since   04/26/2015
 */

#pragma once
#include "Core/CoreObject.h"

#include "ComponentUtility.h"

namespace tgon
{

class GameObject;
    
class TGON_API Component :
	public CoreObject
{
public:
    TGON_DECLARE_RTTI(Component);

/**@section Constructor */
public:
    Component(GameObject* owner = nullptr) noexcept;

/**@section Destructor */
public:
    virtual ~Component() override = default;

/**@section Method */
public:
    /**@brief   Updates this component. */
    virtual void Update() = 0;

    /**@brief   Sets the owner of this component. */
    void SetOwner(GameObject* owner);
        
    /**@brief   Gets the owner of this component. */
    const GameObject* GetOwner() const noexcept;

    /**@brief   Gets the owner of this component. */
    GameObject* GetOwner() noexcept;

    /**@brief   Sets the active state of this component. */
    void SetAcitve(bool isActive) noexcept;

    /**@brief   Gets the active state of this component. */
    bool IsActive() const noexcept;

/**@section Variable */
private:
    bool m_isActive;

    GameObject* m_owner;
};

}
