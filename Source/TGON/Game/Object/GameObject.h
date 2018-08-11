/**
 * @file    GameObject.h
 * @author  ggomdyu
 * @since   03/22/2016
 */

#pragma once
#include <vector>

#include "Core/String/FixedStringHash.h"
#include "Graphics/Object/GraphicsObject.h"

#include "../Component/Component.h"

namespace tgon
{

class TGON_API GameObject final :
	public GraphicsObject
{
public:
    TGON_RUNTIME_OBJECT(GameObject);

/* @section Private constructor */
public:
    explicit GameObject(const FixedStringHash32& name);
    
/* @section Public destructor */
public:
    virtual ~GameObject() override = default;

/* @section Public method */
public:
    virtual void Update() override;

    /**
     * @brief               Sets the name of object.
     * @param [in] name     The name to set.
     */
    void SetName(const FixedStringHash32& name);

    /**
     * @brief               Inserts a component to manage.
     * @param [in] args     Parameters of the _ComponentType constructor.
     */
    template <typename _ComponentType, typename... _ArgTypes>
    void AddComponent(_ArgTypes&&... args);

    /**
     * @brief                   Removes the managed component.
     * @tparam _ComponentType   The type of component to remove.
     * @return                  Returns true if successful, false otherwise.
     */
    template <typename _ComponentType, std::enable_if_t<std::is_base_of<Component, _ComponentType>::value>* = nullptr>
    bool RemoveComponent();

    /**
     * @brief                   Gets a component that managed by this instance.
     * @tparam _ComponentType   The type of component to get.
     * @return                  Returns the pointer to component if successful, nullptr otherwise.
     */
    template <typename _ComponentType, std::enable_if_t<std::is_base_of<Component, _ComponentType>::value>* = nullptr>
    const _ComponentType* GetComponent() const;

    /**
     * @brief                   Gets a component that managed by this instance.
     * @tparam _ComponentType   The type of component to get.
     * @return                  Returns the pointer to component if successful, nullptr otherwise.
     */
    template <typename _ComponentType, std::enable_if_t<std::is_base_of<Component, _ComponentType>::value>* = nullptr>
    _ComponentType* GetComponent();

    /**
     * @brief   Gets the name of object.
     * @return  The name of object to set.
     */
    const FixedStringHash32& GetName() const noexcept;

/* @section Private method */
private:
    /**
     * @brief                   Inserts a component to manage.
     * @param [in] component    The component to insert.
     */
    void AddComponent(Component* component);

    /**
     * @brief                   Removes the managed component.
     * @param [in] componentId  The unique id of component to get.
     */
    bool RemoveComponent(size_t componentId);

    /**
     * @brief                   Gets a component that managed by this instance.
     * @param [in] componentId  The unique id of component to get.
     * @return                  Returns the pointer to component if successful, nullptr otherwise.
     */
    Component* GetComponent(size_t componentId);

/* @section Private variable */
private:
    FixedStringHash32 m_name;

    std::vector<std::unique_ptr<Component>> m_components;
};

template <typename _ComponentType, std::enable_if_t<std::is_base_of<Component, _ComponentType>::value>*>
inline const _ComponentType* GameObject::GetComponent() const
{
    return const_cast<GameObject*>(this)->GetComponent<_ComponentType>();
}
    
template <typename _ComponentType, std::enable_if_t<std::is_base_of<Component, _ComponentType>::value>*>
inline _ComponentType* GameObject::GetComponent()
{
    return static_cast<_ComponentType*>(GetComponentId<_ComponentType>());
}

template <typename _ComponentType, typename... _ArgTypes>
inline void GameObject::AddComponent(_ArgTypes&&... args)
{
    this->AddComponent(std::make_unique<_ComponentType>(std::forward<_ArgTypes>(args)...));
}

template <typename _ComponentType, std::enable_if_t<std::is_base_of<Component, _ComponentType>::value>*>
inline bool GameObject::RemoveComponent()
{
    return this->RemoveComponent(GetComponentId<_ComponentType>());
}

} /* namespace tgon */
