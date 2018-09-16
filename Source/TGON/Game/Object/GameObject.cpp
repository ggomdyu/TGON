#include "PrecompiledHeader.h"

#include <algorithm>

#include "GameObject.h"

namespace tgon
{

GameObject::GameObject(const FixedHashString32& name) :
    m_name(name),
    m_isActive(true)
{
}

void GameObject::Update()
{
    if (m_isActive == false)
    {
        return;
    }

    m_transform.Update();

    for (auto& component : m_components)
    {
        component->Update();
    }
}

void GameObject::SetName(const FixedHashString32& name)
{
    m_name = name;
}

const FixedHashString32& GameObject::GetName() const noexcept
{
    return m_name;
}

void GameObject::SetPosition(const Vector3& position)
{
    m_transform.SetPosition(position);
}

void GameObject::Move(const Vector3& position)
{
    m_transform.SetPosition(m_transform.GetPosition() + position);
}

void GameObject::SetRotation(const Vector3& rotation)
{
    m_transform.SetRotation(rotation);
}

void GameObject::Rotate(const Vector3& rotation)
{
    m_transform.SetRotation(m_transform.GetRotation() + rotation);
}

void GameObject::SetScale(const Vector3& scale)
{
    m_transform.SetScale(scale);
}

void GameObject::Scale(const Vector3& scale)
{
    m_transform.SetScale(m_transform.GetScale() + scale);
}

Transform& GameObject::GetTransform() noexcept
{
    return m_transform;
}

const Transform& GameObject::GetTransform() const noexcept
{
    return m_transform;
}

void GameObject::SetActive(bool isActive)
{
    m_isActive = isActive;
}

bool GameObject::IsActive() const noexcept
{
    return m_isActive;
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
