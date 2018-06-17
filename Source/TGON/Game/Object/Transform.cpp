#include "PrecompiledHeader.h"

#include "Transform.h"

namespace tgon
{

Transform::Transform(const Vector3& position, const Vector3& rotation, const Vector3& scale)
{
}
    
void Transform::SetPosition(const Vector3& position) noexcept
{
    m_position = position;
}
    
void Transform::SetRotation(const Vector3& rotation) noexcept
{
    m_rotation = rotation;
}
    
void Transform::SetScale(const Vector3& scale) noexcept
{
    m_scale = scale;
}
    
const Vector3& Transform::GetPosition() const noexcept
{
    return m_position;
}
    
Vector3& Transform::GetPosition() noexcept
{
    return m_position;
}

const Vector3& Transform::GetRotation() const noexcept
{
    return m_rotation;
}

Vector3& Transform::GetRotation() noexcept
{
    return m_rotation;
}

const Vector3& Transform::GetScale() const noexcept
{
    return m_scale;
}

Vector3& Transform::GetScale() noexcept
{
    return m_scale;
}

} /* namespace tgon */
