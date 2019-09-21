/**
 * @file    GameObject.h
 * @author  ggomdyu
 * @since   03/22/2016
 */

#pragma once
#include <vector>

#include "Core/CoreObject.h"
#include "Core/DynamicCast.h"
#include "Graphics/Transform.h"
#include "String/StringHash.h"
#include "Component/Component.h"

namespace tgon
{

class TGON_API GameObject :
	public CoreObject
{
public:
    TGON_DECLARE_RTTI(GameObject)

/**@section Constructor */
public:
    template <typename... _ComponentTypes>
    explicit GameObject(const StringHash& name, Transform* transform, _ComponentTypes&&... components) :
        m_name(name),
        m_transform(transform),
        m_isActive(true),
        m_components(std::forward<_ComponentTypes>(components)...)
    {
    }

/**@section Destructor */
public:
    virtual ~GameObject() override = default;

/**@section Method */
public:
    virtual void Update();
    template <typename _ComponentType, typename... _ArgTypes>
    std::shared_ptr<_ComponentType> AddComponent(_ArgTypes&&... args);
    template <typename _ComponentType>
    std::shared_ptr<_ComponentType> AddComponent(const std::shared_ptr<_ComponentType>& component);
    template <typename _ComponentType>
    bool RemoveComponent();
    template <typename _ComponentType>
    std::shared_ptr<const _ComponentType> GetComponent() const;
    template <typename _ComponentType>
    std::shared_ptr<_ComponentType> GetComponent();
    void SetName(const StringHash& name);
    const StringHash& GetName() const noexcept;
    void SetActive(bool isActive) noexcept;
    bool IsActive() const noexcept;
    std::shared_ptr<Transform> GetTransform() noexcept;
    std::shared_ptr<const Transform> GetTransform() const noexcept;

private:
    bool RemoveComponent(int32_t componentId);
    std::shared_ptr<Component> GetComponent(int32_t componentId);

/**@section Variable */
private:
    StringHash m_name;
    bool m_isActive;
    std::shared_ptr<Transform> m_transform;
    std::vector<std::shared_ptr<Component>> m_components;
};
    
template <typename _ComponentType, typename... _ArgTypes>
inline std::shared_ptr<_ComponentType> GameObject::AddComponent(_ArgTypes&&... args)
{
    return this->AddComponent(std::make_shared<_ComponentType>(std::forward<_ArgTypes>(args)...));
}

template <typename _ComponentType>
inline std::shared_ptr<_ComponentType> GameObject::AddComponent(const std::shared_ptr<_ComponentType>& component)
{
    m_components.push_back(component);
    component->SetOwner(this);
    
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
    
} /* namespace tgon */
