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
    TGON_RUNTIME_OBJECT(Component);

/* @section Public constructor */
public:
	explicit Component(GameObject* owner) noexcept;

/* @section Public destructor */
public:
    virtual ~Component() override = 0;

/* @section Public method */
public:
	virtual void Update() = 0;
    
	void SetOwner(GameObject* owner) noexcept;
    
    const GameObject* GetOwner() const noexcept;
    GameObject* GetOwner() noexcept;

/* @section Private variable */
private:
    GameObject* m_owner;
};

} /* namespace tgon */
