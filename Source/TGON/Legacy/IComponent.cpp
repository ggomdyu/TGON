#include "PrecompiledHeader.pch"
#include "IComponent.h"

#include "ComponentObject.h"

namespace tgon
{
namespace object
{

IComponent::IComponent(ComponentObject* owner) noexcept :
	m_owner(owner)
{
}

void IComponent::SetOwner(ComponentObject* owner) noexcept
{
    m_owner = owner;
}

ComponentObject* IComponent::GetOwner() noexcept
{
    return m_owner;
}

} /* namespace object */
} /* namespace tgon */
