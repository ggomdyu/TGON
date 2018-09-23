/**
 * @file    GameObject.inl
 * @author  ggomdyu
 * @since   09/22/2018
 */

#pragma once

#include "GameObject.h"

namespace tgon
{

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
