#include "PrecompiledHeader.h"

#include "Game/Object/GameObject.h"

#include "Component.h"

namespace tgon
{

Component::Component(GameObject* owner) noexcept :
    m_owner(owner)
{
}
    
void Component::SetOwner(GameObject* owner)
{
    m_owner = owner;
}

const GameObject* Component::GetOwner() const noexcept
{
    return m_owner;
}

GameObject* Component::GetOwner() noexcept
{
    return m_owner;
}

} /* namespace tgon */