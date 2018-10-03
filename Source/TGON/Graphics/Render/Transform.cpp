#include "PrecompiledHeader.h"

#include "Transform.h"

namespace tgon
{

Transform::Transform() noexcept :
    m_localScale({ 1.0f, 1.0f, 1.0f }),
    m_isDirty(false)
{
}

void Transform::SetLocalPosition(const Vector3& position) noexcept
{
    m_localPosition = position;
    m_isDirty = true;
}

void Transform::SetLocalRotation(const Vector3& rotation) noexcept
{
    m_localRotation = rotation;
    m_isDirty = true;
}

void Transform::SetLocalScale(const Vector3& scale) noexcept
{
    m_localScale = scale;
    m_isDirty = true;
}

const Vector3& Transform::GetLocalPosition() const noexcept
{
    return m_localPosition;
}

const Vector3& Transform::GetLocalRotation() const noexcept
{
    return m_localRotation;
}

const Vector3& Transform::GetLocalScale() const noexcept
{
    return m_localScale;
}

const Matrix4x4& Transform::GetLocalMatrix() const noexcept
{
    return m_matLocal;
}

void Transform::Update()
{
    if (m_isDirty == true)
    {
        m_matLocal = Matrix4x4::Scale(m_localScale.x, m_localScale.y, m_localScale.z) *
                     Matrix4x4::RotateX(m_localRotation.x) * Matrix4x4::RotateY(m_localRotation.y) * Matrix4x4::RotateZ(m_localRotation.z) *
                     Matrix4x4::Translate(m_localPosition.x, m_localPosition.y, m_localPosition.z);
    }
}
    
} /* namespace tgon */
