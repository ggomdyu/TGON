/**
 * @file    GameObject.h
 * @author  ggomdyu
 * @since   03/22/2016
 */

#pragma once
#include <vector>

#include "Core/Object.h"
#include "Graphics/Transform.h"
#include "Component/Component.h"

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
    GameObject();
    explicit GameObject(const StringHash& name);

/**@section Destructor */
public:
    ~GameObject() override = default;

/**@section Method */
public:
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
    bool RemoveComponent(size_t key);
    std::shared_ptr<Component> GetComponent(size_t key);

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
    component->SetGameObject(this->weak_from_this());

    m_components.push_back(component);

    return component;
}

template <typename _ComponentType>
inline bool GameObject::RemoveComponent()
{
    auto componentId = tgon::GetRTTI<_ComponentType>()->GetHashCode();
    return this->RemoveComponent(componentId);
}

template <typename _ComponentType>
inline std::shared_ptr<const _ComponentType> GameObject::GetComponent() const
{
    return const_cast<GameObject*>(this)->GetComponent<_ComponentType>();
}

template <typename _ComponentType>
inline std::shared_ptr<_ComponentType> GameObject::GetComponent()
{
    auto componentId = tgon::GetRTTI<_ComponentType>()->GetHashCode();
    return std::static_pointer_cast<_ComponentType>(GetComponent(componentId));
}

template <>
inline std::shared_ptr<Transform> GameObject::GetComponent()
{
    return m_transform;
}
    
} /* namespace tgon */
