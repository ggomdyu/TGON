#include "PrecompiledHeader.h"

#include <algorithm>

#include "GameObject.h"

namespace tgon
{

void GameObject::Update()
{
    if (m_isActive == false)
    {
        return;
    }

    //m_transform.Update();

    for (auto& component : m_components)
    {
        component->Update();
    }
}

void GameObject::SetName(const StringHash& name)
{
    m_name = name;
}

const StringHash& GameObject::GetName() const noexcept
{
    return m_name;
}

void GameObject::SetActive(bool isActive)
{
    m_isActive = isActive;
}

bool GameObject::IsActive() const noexcept
{
    return m_isActive;
}

Transform& GameObject::GetTransform()
{
    return m_transform;
}

const Transform& GameObject::GetTransform() const
{
    return m_transform;
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

std::shared_ptr<Component> GameObject::GetComponent(size_t componentId)
{
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
