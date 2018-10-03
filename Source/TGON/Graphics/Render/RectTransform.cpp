#include "PrecompiledHeader.h"

#include "RectTransform.h"

namespace tgon
{

void RectTransform::SetLocalAnchor(const Vector2& localAnchor) noexcept
{
    m_localAnchor = localAnchor;
    m_isDirty = true;
}

void RectTransform::SetLocalPivot(const Vector2& localPivot) noexcept
{
    m_localPivot = localPivot;
    m_isDirty = true;
}

const Vector2& RectTransform::GetLocalAnchor() const noexcept
{
    return m_localAnchor;
}

const Vector2& RectTransform::GetLocalPivot() const noexcept
{
    return m_localPivot;
}

void RectTransform::Update()
{
    if (m_isDirty == true)
    {
        m_matLocal = Matrix4x4::Scale(m_localScale.x, m_localScale.y, m_localScale.z) *
                     Matrix4x4::RotateX(m_localRotation.x) * Matrix4x4::RotateY(m_localRotation.y) * Matrix4x4::RotateZ(m_localRotation.z) *
                     Matrix4x4::Translate(m_localPosition.x, m_localPosition.y, m_localPosition.z);
    }
}
    
} /* namespace tgon */
