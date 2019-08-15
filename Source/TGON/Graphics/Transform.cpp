#include "PrecompiledHeader.h"

#include "Math/Mathematics.h"

#include "Transform.h"

namespace tgon
{

Transform::Transform() noexcept :
    Transform(nullptr, {})
{
}
    
Transform::Transform(const Vector3& localPosition, const Vector3& localRotation, const Vector3& localScale) noexcept :
    Transform(nullptr, localPosition, localRotation, localScale)
{
}

Transform::Transform(const std::shared_ptr<Transform>& parent, const Vector3& localPosition) noexcept :
    Transform(parent, localPosition, {}, {1.0f, 1.0f, 1.0f})
{
}

Transform::Transform(const Vector3& localPosition) noexcept :
    Transform(nullptr, localPosition)
{
}
    
Transform::Transform(const std::shared_ptr<Transform>& parent) noexcept :
    Transform(parent, {})
{
}

Transform::Transform(const std::shared_ptr<Transform>& parent, const Vector3& localPosition, const Vector3& localRotation, const Vector3& localScale) noexcept :
    m_parent(parent),
    m_localPosition(localPosition),
    m_localRotation(localRotation),
    m_localScale(localScale),
    m_matWorld(Matrix4x4::Identity()),
    m_isDirty(true)
{
}
    
void Transform::SetParent(const std::shared_ptr<Transform>& parent)
{
#if _DEBUG
    auto iter = std::find_if(parent->m_children.begin(), parent->m_children.end(), [&](const std::shared_ptr<Transform>& item) {
        return this == item.get();
    });
    if (iter != parent->m_children.end())
    {
        assert(false && "The parent transform already has this child!");
        return;
    }
#endif
    
    parent->m_children.push_back(parent);
    
    m_parent = parent;
    m_isDirty = true;
}
    
std::shared_ptr<Transform> Transform::GetParent() noexcept
{
    return m_parent;
}

std::shared_ptr<const Transform> Transform::GetParent() const noexcept
{
    return m_parent;
}

void Transform::SetLocalPosition(const Vector3& localPosition) noexcept
{
    m_localPosition = localPosition;
    m_isDirty = true;
}

void Transform::SetLocalRotation(const Vector3& localRotation) noexcept
{
    m_localRotation = localRotation;
    m_isDirty = true;
}

void Transform::SetLocalScale(const Vector3& localScale) noexcept
{
    m_localScale = localScale;
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

Vector3 Transform::GetPosition() const noexcept
{
    return {m_matWorld.m30, m_matWorld.m31, m_matWorld.m32};
}
    
const Matrix4x4& Transform::GetWorldMatrix() const noexcept
{
    return m_matWorld;
}

void Transform::Update()
{
    if (m_isDirty == true)
    {
        bool isRootTransform = m_parent == nullptr;
        
        m_matWorld = (isRootTransform) ? Matrix4x4::Identity() : m_parent->GetWorldMatrix();
        m_matWorld *= Matrix4x4::Scale(m_localScale.x, m_localScale.y, m_localScale.z);
        m_matWorld *= Matrix4x4::Rotate(m_localRotation.x * Deg2Rad, m_localRotation.y * Deg2Rad, m_localRotation.z * Deg2Rad);
        m_matWorld *= Matrix4x4::Translate(m_localPosition.x, m_localPosition.y, m_localPosition.z);
        
        for (auto& child : m_children)
        {
            child->m_isDirty = true;
            child->Update();
        }
    }
    else
    {
        for (auto& child : m_children)
        {
            child->Update();
        }
    }
    
    m_isDirty = false;
}
    
}
