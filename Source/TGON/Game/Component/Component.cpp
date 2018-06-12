#include "PrecompiledHeader.h"

#include "Component.h"

namespace tgon
{

Component::Component() noexcept :
	m_owner(nullptr)
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
