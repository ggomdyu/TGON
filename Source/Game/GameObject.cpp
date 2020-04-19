#include "PrecompiledHeader.h"

#include <algorithm>
#include <cassert>

#include "GameObject.h"

namespace tg
{
                                   
GameObject::GameObject() noexcept :
    GameObject(StringHash{})
{
}

GameObject::GameObject(const StringHash& name) :
    m_name(name),
    m_isActive(true),
    m_transform(std::make_unique<Transform>())
{
}

GameObject::GameObject(StringHash&& name) noexcept :
    m_name(std::move(name)),
    m_isActive(true),
    m_transform(std::make_unique<Transform>())
{
}

void GameObject::Update()
{
    if (m_transform != nullptr)
    {
        m_transform->Update();
    }

    for (auto& component : m_components)
    {
        if (component->IsActive())
        {
            component->Update();
        }
    }
}

void GameObject::SetName(const StringHash& name)
{
    m_name = name;
}

void GameObject::SetName(StringHash&& name)
{
    m_name = std::move(name);
}

void GameObject::SetActive(bool isActive) noexcept
{
    m_isActive = isActive;
}

bool GameObject::IsActive() const noexcept
{
    return m_isActive;
}

Transform* GameObject::GetTransform() noexcept
{
    return m_transform.get();
}

const Transform* GameObject::GetTransform() const noexcept
{
    return m_transform.get();
}

const StringHash& GameObject::GetName() const noexcept
{
    return m_name;
}

GameObject* GameObject::GetParent() noexcept
{
    return m_parent;
}

const GameObject* GameObject::GetParent() const noexcept
{
    return m_parent;
}

bool GameObject::RemoveComponent(size_t componentId)
{
    auto predicate = [&](const std::shared_ptr<Component>& lhs, size_t rhs)
    {
        return lhs->GetRTTI()->GetHashCode() < rhs;
    };
    
    auto iter = std::lower_bound(m_components.begin(), m_components.end(), componentId, predicate);
    if (iter != m_components.end())
    {
        m_components.erase(iter);
        return true;
    }
    else
    {
        return false;
    }
}

std::shared_ptr<Component> GameObject::FindComponent(size_t componentId)
{
    if (m_components.size() == 0)
    {
        return nullptr;
    }
    
    auto predicate = [&](const std::shared_ptr<Component>& lhs, size_t rhs)
    {
        return lhs->GetRTTI()->GetHashCode() < rhs;
    };
    
    auto iter = std::lower_bound(m_components.begin(), m_components.end(), componentId, predicate);
    if (iter != m_components.end())
    {
        return *iter;
    }
    else
    {
        return nullptr;
    }
}

} /*namespace tgon*/
