#include "PrecompiledHeader.pch"

#include "IComponent.h"

namespace tgon
{
namespace game
{

IComponent::IComponent(GameObject* owner) noexcept :
	m_owner(owner)
{
}

void IComponent::SetOwner(GameObject* owner) noexcept
{
    m_owner = owner;
}

GameObject* IComponent::GetOwner() noexcept
{
    return m_owner;
}

} /* namespace game */
} /* namespace tgon */