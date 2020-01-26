#include "PrecompiledHeader.h"

#include <algorithm>

#include "GameObject.h"

namespace tgon
{
                                   
GameObject::GameObject() noexcept :
    GameObject(StringHash{})
{
}

GameObject::GameObject(const StringHash& name) :
   GameObject(name, std::make_shared<Transform>())
{
}

GameObject::GameObject(StringHash&& name) noexcept :
    GameObject(std::move(name), std::make_shared<Transform>())
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

void GameObject::Update()
{
    if (m_isActive == false)
    {
        return;
    }
    
    if (m_transform != nullptr)
    {
        m_transform->Update();
    }

    for (auto& component : m_components)
    {
        component->Update();
    }
        
    for (auto& child : m_children)
    {
        child->Update();
    }
}

void GameObject::AddChild(const std::shared_ptr<GameObject>& child)
{
    if (auto prevParent = child->m_parent.lock(); prevParent != nullptr)
    {
        prevParent->RemoveChild(child);
    }

    child->m_parent = this->weak_from_this();
    
    m_children.push_back(child);
}

bool GameObject::RemoveChild(const std::shared_ptr<GameObject>& child)
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

void GameObject::RemoveChildren()
{
    m_children.clear();
}

std::shared_ptr<GameObject> GameObject::FindChild(const StringViewHash& objectName)
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

std::shared_ptr<const GameObject> GameObject::FindChild(const StringViewHash& objectName) const
{
    return const_cast<GameObject*>(this)->FindChild(objectName);
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

std::weak_ptr<GameObject> GameObject::GetParent() noexcept
{
    return m_parent;
}

std::weak_ptr<const GameObject> GameObject::GetParent() const noexcept
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
