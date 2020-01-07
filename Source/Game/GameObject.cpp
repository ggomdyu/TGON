#include "PrecompiledHeader.h"

#include <algorithm>

#include "GameObject.h"

namespace tgon
{
                                   
GameObject::GameObject() :
    GameObject({}, {})
{
}

GameObject::GameObject(const StringHash& name) :
   GameObject(name, {})
{
}

GameObject::GameObject(StringHash&& name) :
    GameObject(std::move(name), {})
{
}

GameObject::GameObject(const std::shared_ptr<Transform>& transform) :
    GameObject({}, transform)
{
}

GameObject::GameObject(const StringHash& name, const std::shared_ptr<Transform>& transform) :
    Object(name),
    m_isActive(true),
    m_transform(transform)
{
}

GameObject::GameObject(StringHash&& name, const std::shared_ptr<Transform>& transform) :
    Object(std::move(name)),
    m_isActive(true),
    m_transform(transform)
{
}

std::shared_ptr<GameObject> GameObject::Create(const StringHash& name, const std::shared_ptr<Transform>& transform)
{
    std::shared_ptr<GameObject> object(new GameObject(name, transform));
    
    if (transform != nullptr)
    {
        transform->SetGameObject(object);
    }
    
    object->Initialize();

    return object;
}

std::shared_ptr<GameObject> GameObject::Create(const std::shared_ptr<Transform>& transform)
{
    return GameObject::Create({}, transform);
}

void GameObject::Update()
{
    if (m_isActive == false)
    {
        return;
    }
    
    if (m_transform != nullptr)
    {
        m_transform->Update();

        for (auto& component : m_components)
        {
            component->Update();
        }
        
        for (auto& child : m_transform->GetChildren())
        {
            child->GetGameObject()->Update();
        }
    }
    else
    {
        for (auto& component : m_components)
        {
            component->Update();
        }
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

void GameObject::SetTransform(const std::shared_ptr<Transform>& transform) noexcept
{
    m_transform = transform;
}

std::shared_ptr<Transform> GameObject::GetTransform() noexcept
{
    return m_transform;
}

std::shared_ptr<const Transform> GameObject::GetTransform() const noexcept
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