#include "PrecompiledHeader.h"

#include "../Component/Component.h"

#include "GameObject.h"

namespace tgon
{

GameObject::GameObject(const std::string& name) :
    m_name(name)
{
}
    
GameObject::~GameObject() = default;

void GameObject::Update()
{
    for (auto& component : m_components)
    {
        component->Update();
    }
}
    
void GameObject::SetName(const std::string& name)
{
    m_name = name;
}

const std::string& GameObject::GetString() const noexcept
{
    return m_name;
}

void GameObject::AddComponent(std::unique_ptr<Component> component)
{
    component->SetOwner(this);
    
    auto predicate = [&](const std::unique_ptr<Component>& lhs, size_t rhs)
    {
        return lhs->GetRTTI()->GetHashCode() < rhs;
    };
    
    auto iter = std::lower_bound(m_components.begin(), m_components.end(), component->GetRTTI()->GetHashCode(), predicate);

    m_components.insert(iter, std::move(component));
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
