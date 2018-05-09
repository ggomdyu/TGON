#include "PrecompiledHeader.pch"

#include "GameObject.h"
#include "Component/IComponent.h"

namespace tgon
{

void GameObject::Update()
{
    for (auto& component : m_components)
    {
        component->Update();
    }
}

void GameObject::AddComponents(const std::unique_ptr<IComponent>& component)
{
    m_components.insert({component-> , component});
}

std::vector<std::unique_ptr<GameObject>>& GameObject::GetChildren()
{
    return m_children;
}

const std::vector<std::unique_ptr<GameObject>>& GameObject::GetChildren() const
{
    return m_children;
}

} /*namespace tgon*/