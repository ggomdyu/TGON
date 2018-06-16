/**
 * @filename    GameObject.h
 * @author      ggomdyu
 * @since       03/22/2016
 */

#pragma once
#include <boost/noncopyable.hpp>
#include <vector>

#include "Core/Object/Object.h"
#include "Core/String/FixedStringHash.h"

namespace tgon
{

class Component;

class TGON_API GameObject final :
	public Object,
    private std::enable_shared_from_this<GameObject>,
    private boost::noncopyable
{
public:
    TGON_RUNTIME_OBJECT(GameObject);

/* @section Public constructor */
public:
    explicit GameObject(const FixedStringHash32& name);
    
/* @section Public destructor */
public:
    virtual ~GameObject() override;

/* @section Public method */
public:
    void Update();

    /**
     * @brief               Sets the name of object.
     * @param [in] name     The name of object what you want to set.
     */
    void SetName(const FixedStringHash32& name);

    /**
     * @brief                   Inserts a component to manage.
     * @param [in] component    The component what you want to insert.
     */
    void AddComponent(Component* component);

    /**
     * @brief   Removes the managed component.
     * @tparam  The type of Component what you want to remove.
     * @return  Returns true if successful, false otherwise.
     */
    template <typename _ComponentType>
    bool RemoveComponent();

    /**
     * @brief   Gets a component that managed by this instance.
     * @tparam  The type of Component what you want to get.
     * @return  Returns the pointer to component if successful, nullptr otherwise.
     */
    template <typename _ComponentType>
    const _ComponentType* GetComponent() const;

    /**
     * @brief   Gets a component that managed by this instance.
     * @tparam  The type of Component what you want to get.
     * @return  Returns the pointer to component if successful, nullptr otherwise.
     */
    template <typename _ComponentType>
    _ComponentType* GetComponent();

    /**
     * @brief   Gets the name of object.
     * @return  The name of object what you want to set.
     */
    const FixedStringHash32& GetName() const noexcept;

    std::weak_ptr<GameObject> GetWeakFromThis();

    std::weak_ptr<const GameObject> GetWeakFromThis() const;
    
/* @section Private method */
private:
    /**
     * @brief                   Removes the managed component.
     * @param [in] componentId  The unique id of Component what you want to get.
     */
    bool RemoveComponent(size_t componentId);

    /**
     * @brief                   Gets a component that managed by this instance.
     * @param [in] componentId  The unique id of Component what you want to get.
     * @return                  Returns the pointer to component if successful, nullptr otherwise.
     */
    Component* GetComponent(size_t componentId);
    
/* @section Private variable */
private:
    FixedStringHash32 m_name;
    std::vector<std::unique_ptr<Component>> m_components;
};

template<typename _ComponentType>
inline const _ComponentType* GameObject::GetComponent() const
{
    return const_cast<GameObject*>(this)->GetComponent<_ComponentType>();
}
    
template<typename _ComponentType>
inline _ComponentType* GameObject::GetComponent()
{
    return static_cast<_ComponentType*>(GetComponentId<_ComponentType>());
}

template <typename _ComponentType>
inline bool GameObject::RemoveComponent()
{
    return this->RemoveComponent(GetComponentId<_ComponentType>());
}

} /* namespace tgon */
