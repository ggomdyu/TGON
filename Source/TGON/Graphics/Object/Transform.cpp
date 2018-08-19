#include "PrecompiledHeader.h"

#include "Transform.h"

namespace tgon
{
    
void Transform::SetPosition(const Vector3& position)
{
    m_position = position;
    m_isDirty = true;
}

void Transform::SetRotation(const Vector3& rotation)
{
    m_rotation = rotation;
    m_isDirty = true;
}

void Transform::SetScale(const Vector3& scale)
{
    m_scale = scale;
    m_isDirty = true;
}

const Vector3& Transform::GetPosition() const noexcept
{
    return m_position;
}

const Vector3& Transform::GetRotation() const noexcept
{
    return m_rotation;
}

const Vector3& Transform::GetScale() const noexcept
{
    return m_scale;
}

void Transform::Update()
{
    if (m_isDirty == true)
    {
        m_matWorld = Matrix4x4::Scale(m_scale.x, m_scale.y, m_scale.z) *
                     Matrix4x4::RotateX(m_rotation.x) * Matrix4x4::RotateY(m_rotation.y) * Matrix4x4::RotateZ(m_rotation.z) *
                     Matrix4x4::Translate(m_position.x, m_position.y, m_position.z);
    }
}

const Matrix4x4& Transform::GetWorldMatrix() const noexcept
{
    return m_matWorld;
}
    
} /* namespace tgon */
