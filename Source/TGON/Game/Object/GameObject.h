/**
 * @file    GameObject.h
 * @author  ggomdyu
 * @since   03/22/2016
 */

#pragma once
#include <vector>

#include "Core/Object/CoreObject.h"
#include "Core/String/StringHash.h"
#include "Graphics/Render/Transform.h"

#include "Component/Component.h"

namespace tgon
{

class TGON_API GameObject :
	public CoreObject
{
public:
    TGON_DECLARE_RTTI(GameObject);

/**@section Private constructor */
public:
    explicit GameObject(const StringHash& name);

    template <typename... ComponentTypes>
    GameObject(const StringHash& name, ComponentTypes&&... components);

/**@section Public destructor */
public:
    virtual ~GameObject() override = default;

/**@section Public method */
public:
    /**@brief   Updates the object. */
    virtual void Update();

    /**@brief   Inserts a component to manage. */
    template <typename _ComponentType, typename... _ArgTypes>
    std::shared_ptr<_ComponentType> AddComponent(_ArgTypes&&... args);

    /**
     * @brief   Removes the managed component.
     * @tparam _ComponentType   The type of component to remove.
     * @return  Returns true if successful, false otherwise.
     */
    template <typename _ComponentType, std::enable_if_t<std::is_base_of<Component, _ComponentType>::value>* = nullptr>
    bool RemoveComponent();

    /**
     * @brief   Gets a component that managed by this object.
     * @tparam _ComponentType   The type of component to get.
     * @return  Returns a pointer to component if successful, nullptr otherwise.
     */
    template <typename _ComponentType, std::enable_if_t<std::is_base_of<Component, _ComponentType>::value>* = nullptr>
    std::shared_ptr<const _ComponentType> GetComponent() const;

    /**
     * @brief   Gets a component that managed by this object.
     * @tparam _ComponentType   The type of component to get.
     * @return  Returns a pointer to component if successful, nullptr otherwise.
     */
    template <typename _ComponentType, std::enable_if_t<std::is_base_of<Component, _ComponentType>::value>* = nullptr>
    std::shared_ptr<_ComponentType> GetComponent();

    /**
     * @brief   Sets the name of this object.
     * @param [in] name     The name to set.
     */
    void SetName(const StringHash& name);

    /**@brief   Gets the name of this object. */
    const StringHash& GetName() const noexcept;

    /**
     * @brief   Sets the active state of this object.
     * @remarks If this object has been deactivated, all updates performed on this are stopped.
     */
    void SetActive(bool isActivate);

    /**@brief   Gets the active state of this object. */
    bool IsActive() const noexcept;

/**@section Private method */
private:
    /**
     * @brief   Removes a component with its unique id.
     * @param [in] componentId  The unique id of component to remove.
     */
    bool RemoveComponent(size_t componentId);

    /**
     * @brief   Gets a component that managed by this object.
     * @param [in] componentId  The unique id of component to get.
     * @return  Returns the pointer to component if successful, nullptr otherwise.
     */
    std::shared_ptr<Component> GetComponent(size_t componentId);

/**@section Private variable */
private:
    bool m_isActive;

    StringHash m_name;

    std::vector<std::shared_ptr<Component>> m_components;

    std::unique_ptr<Transform> m_transform;
};

template <typename ...ComponentTypes>
inline GameObject::GameObject(const StringHash& name, ComponentTypes&&... components) :
    m_name(name),
    m_isActive(true),
    m_components(std::forward<ComponentTypes>(components)...)
{
}

template <typename _ComponentType, typename... _ArgTypes>
inline std::shared_ptr<_ComponentType> GameObject::AddComponent(_ArgTypes&&... args)
{
    auto iter = std::lower_bound(m_components.begin(), m_components.end(), tgon::GetRTTI<_ComponentType>()->GetHashCode(), [&](const std::shared_ptr<Component>& lhs, size_t rhs)
    {
        return lhs->GetRTTI()->GetHashCode() < rhs;
    });
    auto component = std::make_shared<_ComponentType>(std::forward<_ArgTypes>(args)...);
    component->SetOwner(this);

    return std::static_pointer_cast<_ComponentType>(*m_components.insert(iter, component));
}

template <typename _ComponentType, std::enable_if_t<std::is_base_of<Component, _ComponentType>::value>*>
inline bool GameObject::RemoveComponent()
{
    return this->RemoveComponent(GetComponentId<_ComponentType>());
}

template <typename _ComponentType, std::enable_if_t<std::is_base_of<Component, _ComponentType>::value>*>
inline std::shared_ptr<const _ComponentType> GameObject::GetComponent() const
{
    return const_cast<GameObject*>(this)->GetComponent<_ComponentType>();
}

template <typename _ComponentType, std::enable_if_t<std::is_base_of<Component, _ComponentType>::value>*>
inline std::shared_ptr<_ComponentType> GameObject::GetComponent()
{
    return std::static_pointer_cast<_ComponentType>(GetComponent(GetComponentId<_ComponentType>()));
}

} /* namespace tgon */
