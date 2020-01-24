#include "PrecompiledHeader.h"

#include <algorithm>

#include "GameObject.h"

namespace tgon
{
                                   
GameObject::GameObject() noexcept :
    GameObject({}, {})
{
}

GameObject::GameObject(const StringHash& name) :
   GameObject(name, {})
{
}

GameObject::GameObject(StringHash&& name) noexcept :
    GameObject(std::move(name), {})
{
}

GameObject::GameObject(const std::shared_ptr<Transform>& transform) noexcept :
    GameObject({}, transform)
{
}

GameObject::GameObject(const StringHash& name, const std::shared_ptr<Transform>& transform) :
    m_name(name),
    m_isActive(true),
    m_transform(transform)
{
}

GameObject::GameObject(StringHash&& name, const std::shared_ptr<Transform>& transform) noexcept :
    m_name(std::move(name)),
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
        
        for (auto& child : m_children)
        {
            child->Update();
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

void GameObject::AddChild(const std::shared_ptr<GameObject>& child)
{
    m_children.push_back(child);
}

bool GameObject::DetachChild(const std::shared_ptr<GameObject>& child)
{
    auto iter = std::find_if(m_children.begin(), m_children.end(), [&](const std::shared_ptr<GameObject>& object)
    {
        return child == object;
    });
    if (iter != m_children.end())
    {
        m_children.erase(iter);
        return true;
    }

    return false;
}

void GameObject::DetachChildren()
{
    m_children.clear();
}

std::shared_ptr<GameObject> GameObject::FindObject(const StringViewHash& objectName)
{
    auto iter = std::find_if(m_children.begin(), m_children.end(), [&](const std::shared_ptr<GameObject>& item)
    {
        return item->GetName() == objectName;
    });
    if (m_children.end() == iter)
    {
        return nullptr;
    }

    return *iter;
}

std::shared_ptr<const GameObject> GameObject::FindObject(const StringViewHash& objectName) const
{
    return const_cast<GameObject*>(this)->FindObject(objectName);
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

const StringHash& GameObject::GetName() const noexcept
{
    return m_name;
}

std::vector<std::shared_ptr<GameObject>>& GameObject::GetChildren() noexcept
{
    return m_children;
}

const std::vector<std::shared_ptr<GameObject>>& GameObject::GetChildren() const noexcept
{
    return m_children;
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
