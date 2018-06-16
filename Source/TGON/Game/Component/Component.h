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

/* @section Public destructor */
public:
    virtual ~Component() override = 0;

/* @section Public method */
public:
	virtual void Update() = 0;
    
	void SetOwner(GameObject* owner) noexcept;
    std::weak_ptr<const GameObject> GetOwner() const noexcept;
    std::weak_ptr<GameObject> GetOwner() noexcept;

/* @section Private variable */
private:
    std::weak_ptr<GameObject> m_owner;
};

/**
 * @brief   Gets the unique id of component specified by _ComponentType.
 * @tparam  The type of Component what you want to get id.
 * @return  The unique id of component.
 */
template<typename _ComponentType>
inline std::size_t GetComponentId()
{
    return tgon::GetRTTI<_ComponentType>()->GetHashCode();
}

} /* namespace tgon */
