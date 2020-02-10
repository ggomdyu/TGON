/**
 * @file    GameObject.h
 * @author  ggomdyu
 * @since   03/22/2016
 */

#pragma once
#include <vector>

#include "Text/StringHash.h"

#include "Game/Transform.h"

namespace tgon
{

class GameObject :
    public RuntimeObject,
    public std::enable_shared_from_this<GameObject>
{
public:
    TGON_DECLARE_RTTI(GameObject)

/**@section Constructor */
public:
    GameObject() noexcept;
    explicit GameObject(const StringHash& name);
    explicit GameObject(StringHash&& name) noexcept;
    explicit GameObject(const std::shared_ptr<Transform>& transform) noexcept;
    GameObject(const StringHash& name, const std::shared_ptr<Transform>& transform);
    GameObject(StringHash&& name, const std::shared_ptr<Transform>& transform) noexcept;

/**@section Method */
public:
    template <typename _ObjectType = GameObject, typename... _ArgTypes>
    static std::shared_ptr<_ObjectType> Create(_ArgTypes&&... args);
    virtual void Initialize() {}
    virtual void Update();
    void AddChild(const std::shared_ptr<GameObject>& child);
    template <typename _ComponentType, typename... _ArgTypes>
    std::shared_ptr<_ComponentType> AddComponent(_ArgTypes&&... args);
    bool RemoveChild(const std::shared_ptr<GameObject>& child);
    void RemoveChildren();
    template <typename _ComponentType>
    bool RemoveComponent();
    std::shared_ptr<GameObject> FindChild(const StringViewHash& objectName);
    std::shared_ptr<const GameObject> FindChild(const StringViewHash& objectName) const;
    template <typename _ComponentType>
    std::shared_ptr<_ComponentType> FindComponent();
    template <typename _ComponentType>
    std::shared_ptr<const _ComponentType> FindComponent() const;
    void SetName(const StringHash& name);
    void SetName(StringHash&& name);
    void SetTransform(const std::shared_ptr<Transform>& transform) noexcept;
    void SetActive(bool isActive) noexcept;
    std::shared_ptr<Transform> GetTransform() noexcept;
    std::shared_ptr<const Transform> GetTransform() const noexcept;
    const StringHash& GetName() const noexcept;
    std::vector<std::shared_ptr<GameObject>>& GetChildren() noexcept;
    const std::vector<std::shared_ptr<GameObject>>& GetChildren() const noexcept;
    std::weak_ptr<GameObject> GetParent() noexcept;
    std::weak_ptr<const GameObject> GetParent() const noexcept;
    bool IsActive() const noexcept;

private:
    bool RemoveComponent(size_t componentId);
    std::shared_ptr<Component> FindComponent(size_t componentId);

/**@section Variable */
protected:
    StringHash m_name;
    bool m_isActive;
    std::shared_ptr<Transform> m_transform;
    std::weak_ptr<GameObject> m_parent;
    std::vector<std::shared_ptr<GameObject>> m_children;
    std::vector<std::shared_ptr<Component>> m_components;
};

template <typename _ObjectType, typename... _ArgTypes>
inline std::shared_ptr<_ObjectType> GameObject::Create(_ArgTypes&&... args)
{
    auto object = std::shared_ptr<_ObjectType>(new _ObjectType(std::forward<_ArgTypes>(args)...));

    if (object->m_transform != nullptr)
    {
        object->m_transform->SetGameObject(object);
    }

    object->Initialize();

    return object;
}

template <typename _ComponentType, typename... _ArgTypes>
inline std::shared_ptr<_ComponentType> GameObject::AddComponent(_ArgTypes&&... args)
{
    auto component = std::make_shared<_ComponentType>(std::forward<_ArgTypes>(args)...);

    m_components.insert(std::lower_bound(m_components.begin(), m_components.end(), tgon::GetRTTI<_ComponentType>()->GetHashCode(), [&](const std::shared_ptr<Component>& lhs, size_t rhs)
    {
        return lhs->GetRTTI()->GetHashCode() < rhs;
    }), component);

    component->SetGameObject(this->shared_from_this());
    component->Initialize();

    return component;
}

template <typename _ComponentType>
inline bool GameObject::RemoveComponent()
{
    return this->RemoveComponent(tgon::GetRTTI<_ComponentType>()->GetHashCode());
}

template <typename _ComponentType>
inline std::shared_ptr<const _ComponentType> GameObject::FindComponent() const
{
    return const_cast<GameObject*>(this)->FindComponent<_ComponentType>();
}

template <typename _ComponentType>
inline std::shared_ptr<_ComponentType> GameObject::FindComponent()
{
    auto component = this->FindComponent(tgon::GetRTTI<_ComponentType>()->GetHashCode());
    return std::static_pointer_cast<_ComponentType>(component);
}

template <>
inline std::shared_ptr<Transform> GameObject::FindComponent()
{
    return m_transform;
}
    
} /* namespace tgon */
