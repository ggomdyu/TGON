/**
 * @file    GameObject.h
 * @author  ggomdyu
 * @since   03/22/2016
 */

#pragma once
#include <vector>

#include "Core/Object.h"
#include "Component/Transform.h"

namespace tgon
{

class GameObject :
    public Object,
    public std::enable_shared_from_this<GameObject>
{
public:
    TGON_DECLARE_RTTI(GameObject)

/**@section Constructor */
public:
    GameObject(const StringHash& name = {}, const std::shared_ptr<Transform>& transform = std::make_shared<Transform>());

/**@section Method */
public:
    virtual void Initialize();
    virtual void Update();
    template <typename _ComponentType, typename... _ArgTypes>
    std::shared_ptr<_ComponentType> AddComponent(_ArgTypes&&... args);
    template <typename _ComponentType>
    bool RemoveComponent();
    template <typename _ComponentType>
    std::shared_ptr<const _ComponentType> GetComponent() const;
    template <typename _ComponentType>
    std::shared_ptr<_ComponentType> GetComponent();
    void SetActive(bool isActive) noexcept;
    bool IsActive() const noexcept;
    std::shared_ptr<Transform> GetTransform() noexcept;
    std::shared_ptr<const Transform> GetTransform() const noexcept;

private:
    bool RemoveComponent(size_t componentId);
    std::shared_ptr<Component> GetComponent(size_t componentId);

/**@section Variable */
private:
    bool m_isActive;
    std::shared_ptr<Transform> m_transform;
    std::vector<std::shared_ptr<Component>> m_components;
};

template <typename _ComponentType, typename... _ArgTypes>
inline std::shared_ptr<_ComponentType> GameObject::AddComponent(_ArgTypes&&... args)
{
    auto component = std::make_shared<_ComponentType>(std::forward<_ArgTypes>(args)...);
    component->SetGameObject(this->shared_from_this());

    m_components.insert(std::lower_bound(m_components.begin(), m_components.end(), tgon::GetRTTI<_ComponentType>()->GetHashCode(), [&](const std::shared_ptr<Component>& lhs, size_t rhs)
    {
        return lhs->GetRTTI()->GetHashCode() < rhs;
    }), component);

    return component;
}

template <typename _ComponentType>
inline bool GameObject::RemoveComponent()
{
    return this->RemoveComponent(tgon::GetRTTI<_ComponentType>()->GetHashCode());
}

template <typename _ComponentType>
inline std::shared_ptr<const _ComponentType> GameObject::GetComponent() const
{
    return const_cast<GameObject*>(this)->GetComponent<_ComponentType>();
}

template <typename _ComponentType>
inline std::shared_ptr<_ComponentType> GameObject::GetComponent()
{
    auto component = this->GetComponent(tgon::GetRTTI<_ComponentType>()->GetHashCode());
    return std::static_pointer_cast<_ComponentType>(component);
}

template <>
inline std::shared_ptr<Transform> GameObject::GetComponent()
{
    return m_transform;
}
    
} /* namespace tgon */
