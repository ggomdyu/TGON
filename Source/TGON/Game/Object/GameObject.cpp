#include "PrecompiledHeader.h"

#include "../Component/Component.h"

#include "GameObject.h"

namespace tgon
{

GameObject::~GameObject() = default;

void GameObject::Update()
{
    for (auto& component : m_components)
    {
        component->Update();
    }
}

void GameObject::AddComponent(std::initializer_list<std::unique_ptr<Component>> components)
{
    m_components.insert(components.begin(), components.end());
    
    std::sort(m_components.begin(), m_components.end(), [](const std::unique_ptr<Component>& lhs, const std::unique_ptr<Component>& rhs)
    {
        return lhs->GetRTTI()->GetHashCode() < rhs->GetRTTI()->GetHashCode();
    });
}

void GameObject::AddComponent(std::unique_ptr<Component> component)
{
    m_components.push_back(std::move(component));
    
    std::sort(m_components.begin(), m_components.end(), [](const std::unique_ptr<Component>& lhs, const std::unique_ptr<Component>& rhs)
    {
        return lhs->GetRTTI()->GetHashCode() < rhs->GetRTTI()->GetHashCode();
    });
}

} /*namespace tgon*/
