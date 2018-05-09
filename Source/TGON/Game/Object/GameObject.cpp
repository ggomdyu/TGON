#include "PrecompiledHeader.pch"

#include "GameObject.h"
#include "Component.h"

namespace tgon
{

GameObject::GameObject() = default;
GameObject::~GameObject() = default;

void GameObject::Update()
{
    for (auto& component : m_components)
    {
        component.second->Update();
    }

    for (auto& children : m_children)
    {
        children->Update();
    }
}

void GameObject::AddComponent(std::unique_ptr<Component>&& component)
{
    m_components.emplace(component->GetRTTI()->GetHashCode(), std::move(component));
}

void GameObject::AddChild(std::unique_ptr<GameObject>&& child)
{
    m_children.push_back(std::move(child));
}

std::vector<std::unique_ptr<GameObject>>& GameObject::GetChildren() noexcept
{
    return m_children;
}

const std::vector<std::unique_ptr<GameObject>>& GameObject::GetChildren() const noexcept
{
    return m_children;
}

} /*namespace tgon*/