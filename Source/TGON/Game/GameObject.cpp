#include "PrecompiledHeader.h"

#include <algorithm>

#include "GameObject.h"

namespace tgon
{

GameObject::GameObject() :
    GameObject(StringHash())
{
}

GameObject::GameObject(const StringHash& name) :
    Object(name),
    m_isActive(true),
    m_transform(std::make_shared<Transform>(this->weak_from_this()))
{
}

void GameObject::Update()
{
    if (m_isActive == false)
    {
        return;
    }

    m_transform->Update();

    for (auto& component : m_components)
    {
        component->Update();
    }
}

void GameObject::SetActive(bool isActive) noexcept
{
    m_isActive = isActive;
}

bool GameObject::IsActive() const noexcept
{
    return m_isActive;
}

std::shared_ptr<Transform> GameObject::GetTransform() noexcept
{
    return m_transform;
}

std::shared_ptr<const Transform> GameObject::GetTransform() const noexcept
{
    return m_transform;
}

bool GameObject::RemoveComponent(size_t key)
{
    auto predicate = [&](const std::shared_ptr<Component>& lhs, size_t rhs)
    {
        return lhs->GetRTTI()->GetHashCode() < rhs;
    };
    
    auto iter = std::lower_bound(m_components.begin(), m_components.end(), key, predicate);
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

std::shared_ptr<Component> GameObject::GetComponent(size_t key)
{
    auto predicate = [&](const std::shared_ptr<Component>& lhs, size_t rhs)
    {
        return lhs->GetRTTI()->GetHashCode() < rhs;
    };
    
    auto iter = std::lower_bound(m_components.begin(), m_components.end(), key, predicate);
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
