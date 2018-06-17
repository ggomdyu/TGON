#include "PrecompiledHeader.h"

#include "../Object/GameObject.h"

#include "Component.h"

namespace tgon
{

Component::~Component() = default;

void Component::SetOwner(std::weak_ptr<GameObject> owner) noexcept
{
    m_owner = owner;
}

std::weak_ptr<const GameObject> Component::GetOwner() const noexcept
{
    return m_owner;
}

std::weak_ptr<GameObject> Component::GetOwner() noexcept
{
    return m_owner;
}

} /* namespace tgon */
