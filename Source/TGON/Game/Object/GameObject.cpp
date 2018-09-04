#include "PrecompiledHeader.h"

#include <algorithm>

#include "GameObject.h"

namespace tgon
{

GameObject::GameObject(const FixedHashString32& name) :
    m_name(name),
    m_isActivated(true)
{
}

void GameObject::Update()
{
    if (m_isActivated == false)
    {
        return;
    }

    m_transform.Update();

    for (auto& component : m_components)
    {
        component->Update();
    }
}

const std::shared_ptr<Component>& GameObject::AddComponent(Component* component)
{
    component->SetOwner(this);

    auto predicate = [&](const std::shared_ptr<Component>& lhs, size_t rhs)
    {
        return lhs->GetRTTI()->GetHashCode() < rhs;
    };
    
    auto iter = std::lower_bound(m_components.begin(), m_components.end(), component->GetRTTI()->GetHashCode(), predicate);

    return *m_components.emplace(iter, component);
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

Component* GameObject::GetComponent(size_t componentId)
{
    auto predicate = [&](const std::shared_ptr<Component>& lhs, size_t rhs)
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
