#include "PrecompiledHeader.pch"

#include "GameObject.h"
#include "Component/IComponent.h"

namespace tgon
{

GameObject::GameObject(const std::shared_ptr<GameContext>& context) :
    m_context(context)
{
}

GameObject::~GameObject()
{
}

void GameObject::Update()
{
    for (auto& component : m_components)
    {
        component->Update();
    }
}

} /*namespace tgon*/