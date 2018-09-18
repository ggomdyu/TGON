/**
 * @file    GameObject.h
 * @author  ggomdyu
 * @since   03/22/2016
 */

#pragma once
#include <vector>

#include "Core/Object/CoreObject.h"
#include "Core/String/FixedHashString.h"

#include "../Component/Component.h"

#include "Transform.h"

namespace tgon
{

class TGON_API GameObject :
	public CoreObject
{
public:
    TGON_RUNTIME_OBJECT(GameObject);

/**@section Private constructor */
public:
    explicit GameObject(const FixedHashString32& name);
    
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
    void SetName(const FixedHashString32& name);

    /**@brief   Gets the name of this object. */
    const FixedHashString32& GetName() const noexcept;

    /**@brief   Sets the position of this object. */
    void SetPosition(const Vector3& position);
    
    /**@brief   Adjusts the position of this object. */
    void Move(const Vector3& position);
    
    /**@brief   Sets the rotation of this object. */
    void SetRotation(const Vector3& rotation);
    
    /**@brief   Adjusts the rotation of this object. */
    void Rotate(const Vector3& rotation);
    
    /**@brief   Sets the scale of this object. */
    void SetScale(const Vector3& scale);
    
    /**@brief   Adjusts the scale of this object. */
    void Scale(const Vector3& scale);
    
    /**@brief   Gets the position of this object. */
    const Vector3& GetPosition() const noexcept;
    
    /**@brief   Gets the rotation of this object. */
    const Vector3& GetRotation() const noexcept;
    
    /**@brief   Gets the scale of this object. */
    const Vector3& GetScale() const noexcept;
    
    /**@brief   Gets the transform. */
    Transform& GetTransform() noexcept;

    /**@brief   Gets the transform. */
    const Transform& GetTransform() const noexcept;

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

    FixedHashString32 m_name;

    std::vector<std::shared_ptr<Component>> m_components;

    Transform m_transform;
};

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
