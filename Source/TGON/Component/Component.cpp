#include "PrecompiledHeader.h"

#include "Game/GameObject.h"

#include "Component.h"

namespace tgon
{

Component::Component(const std::shared_ptr<GameObject>& gameObject) noexcept :
    m_gameObject(gameObject)
{
}

void Component::Update()
{
}
    
void Component::SetGameObject(const std::shared_ptr<GameObject>& gameObject) noexcept
{
    m_gameObject = gameObject;
}

std::shared_ptr<GameObject> Component::GetGameObject() noexcept
{
    return m_gameObject.lock();
}

std::shared_ptr<const GameObject> Component::GetGameObject() const noexcept
{
    return m_gameObject.lock();
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
