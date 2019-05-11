#include "PrecompiledHeader.h"

#include "../GameObject.h"

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

void Component::SetAcitve(bool isActive) noexcept
{
    m_isActive = isActive;
}

bool Component::IsActive() const noexcept
{
    return m_isActive;
}

} /* namespace tgon */
