/**
 * @file    Component.h
 * @author  ggomdyu
 * @since   04/26/2015
 */

#pragma once
#include "Core/Object/Object.h"

namespace tgon
{

class GameObject;
    
class TGON_API Component :
	public Object
{
public:
    TGON_RUNTIME_OBJECT(Component);

/* @section Public destructor */
public:
    virtual ~Component() override = 0;

/* @section Public method */
public:
	virtual void Update() = 0;
    
	void SetOwner(std::weak_ptr<GameObject> owner) noexcept;
    std::weak_ptr<const GameObject> GetOwner() const noexcept;
    std::weak_ptr<GameObject> GetOwner() noexcept;

/* @section Private variable */
private:
    std::weak_ptr<GameObject> m_owner;
};

} /* namespace tgon */
