#pragma once

#include <vector>

#include "Text/StringHash.h"

#include "Game/Transform.h"

namespace tg
{

class GameObject :
    public RuntimeObject
{
public:
    TGON_DECLARE_RTTI(GameObject)

/**@section Constructor */
public:
    GameObject() noexcept;
    explicit GameObject(const StringHash& name);
    explicit GameObject(StringHash&& name) noexcept;
    explicit GameObject(const std::shared_ptr<Transform>& transform) noexcept;

/**@section Method */
public:
    virtual void Initialize() {}
    virtual void Update();
    template <typename _ComponentType, typename... _ArgTypes>
    _ComponentType* AddComponent(_ArgTypes&&... args);
    template <typename _ComponentType>
    bool RemoveComponent();
    template <typename _ComponentType>
    _ComponentType* FindComponent();
    template <typename _ComponentType>
    const _ComponentType* FindComponent() const;
    void SetName(const StringHash& name);
    void SetName(StringHash&& name);
    void SetActive(bool isActive) noexcept;
    Transform* GetTransform() noexcept;
    const Transform* GetTransform() const noexcept;
    const StringHash& GetName() const noexcept;
    GameObject* GetParent() noexcept;
    const GameObject* GetParent() const noexcept;
    bool IsActive() const noexcept;

private:
    bool RemoveComponent(size_t componentId);
    std::shared_ptr<Component> FindComponent(size_t componentId);

/**@section Variable */
protected:
    StringHash m_name;
    bool m_isActive;
    std::unique_ptr<Transform> m_transform;
    GameObject* m_parent;
    std::vector<std::unique_ptr<Component>> m_components;
};

template <typename _ComponentType, typename... _ArgTypes>
inline _ComponentType* GameObject::AddComponent(_ArgTypes&&... args)
{
    auto component = std::make_unique<_ComponentType>(std::forward<_ArgTypes>(args)...);
    component->SetGameObject(this->shared_from_this());
    component->Initialize();

    m_components.insert(std::lower_bound(m_components.begin(), m_components.end(), tg::GetRTTI<_ComponentType>()->GetHashCode(), [&](const std::shared_ptr<Component>& lhs, size_t rhs)
    {
        return lhs->GetRTTI()->GetHashCode() < rhs;
    }), std::move(component));

    return component;
}

template <typename _ComponentType>
inline bool GameObject::RemoveComponent()
{
    return this->RemoveComponent(tg::GetRTTI<_ComponentType>()->GetHashCode());
}

template <typename _ComponentType>
inline const _ComponentType* GameObject::FindComponent() const
{
    return const_cast<GameObject*>(this)->FindComponent<_ComponentType>();
}

template <typename _ComponentType>
inline _ComponentType* GameObject::FindComponent()
{
    auto component = this->FindComponent(tg::GetRTTI<_ComponentType>()->GetHashCode());
    return std::static_pointer_cast<_ComponentType>(component);
}

template <>
inline Transform* GameObject::FindComponent()
{
    return m_transform.get();
}
    
}
