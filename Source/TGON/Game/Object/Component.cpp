#include "PrecompiledHeader.pch"

#include "Component.h"
#include "GameObject.h"

namespace tgon
{

Component::Component(GameObject* owner) noexcept :
	m_owner(owner)
{
}

Component::~Component() = default;

void Component::SetOwner(GameObject* owner) noexcept
{
    m_owner = owner;
}

GameObject* Component::GetOwner() noexcept
{
    return m_owner;
}

const GameObject* Component::GetOwner() const noexcept
{
    return m_owner;
}

} /* namespace tgon */