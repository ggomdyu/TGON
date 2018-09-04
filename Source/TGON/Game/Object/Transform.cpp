#include "PrecompiledHeader.h"

#include "Transform.h"

namespace tgon
{

void Transform::Update()
{
    if (m_isDirty == true)
    {
        m_matWorld = Matrix4x4::Scale(m_scale.x, m_scale.y, m_scale.z) *
                     Matrix4x4::RotateX(m_rotation.x) * Matrix4x4::RotateY(m_rotation.y) * Matrix4x4::RotateZ(m_rotation.z) *
                     Matrix4x4::Translate(m_position.x, m_position.y, m_position.z);
    }
}
    
} /* namespace tgon */
