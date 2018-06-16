#include "PrecompiledHeader.h"

#include <algorithm>

#include "../Component/Component.h"

#include "GameObject.h"

namespace tgon
{

GameObject::GameObject(const FixedStringHash32& name) :
    m_name(name)
{
}
    
GameObject::~GameObject() = default;

std::shared_ptr<GameObject> GameObject::Create(const FixedStringHash32& name)
{
    return std::shared_ptr<GameObject>(new GameObject(name));
}

void GameObject::Update()
{
    for (auto& component : m_components)
    {
        component->Update();
    }
}
    
void GameObject::SetName(const FixedStringHash32& name)
{
    m_name = name;
}

const FixedStringHash32& GameObject::GetName() const noexcept
{
    return m_name;
}

std::weak_ptr<GameObject> GameObject::GetWeakFromThis()
{
    return this->weak_from_this();
}

std::weak_ptr<const GameObject> GameObject::GetWeakFromThis() const
{
    return this->weak_from_this();
}

void GameObject::AddComponent(Component* component)
{
    component->SetOwner(this);
    
    auto predicate = [&](const std::unique_ptr<Component>& lhs, size_t rhs)
    {
        return lhs->GetRTTI()->GetHashCode() < rhs;
    };
    
    auto iter = std::lower_bound(m_components.begin(), m_components.end(), component->GetRTTI()->GetHashCode(), predicate);

    m_components.emplace(iter, component);
}
    
bool GameObject::RemoveComponent(size_t componentId)
{
    auto predicate = [&](const std::unique_ptr<Component>& lhs, size_t rhs)
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

Component* GameObject::GetComponent(size_t componentId)
{
    auto predicate = [&](const std::unique_ptr<Component>& lhs, size_t rhs)
    {
        return lhs->GetRTTI()->GetHashCode() < rhs;
    };
    
    auto iter = std::lower_bound(m_components.begin(), m_components.end(), componentId, predicate);
    if (iter != m_components.end())
    {
        return iter->get();
    }
    else
    {
        return nullptr;
    }
}

} /*namespace tgon*/
