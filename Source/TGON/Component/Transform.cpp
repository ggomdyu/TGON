#include "PrecompiledHeader.h"

#include "Math/Mathematics.h"

#include "Transform.h"

namespace tgon
{
    
void Transform::SetParent(const std::shared_ptr<Transform>& parent)
{
    auto sharedThis = this->shared_from_this();
    if (m_parent != nullptr)
    {
        m_parent->DetachChild(sharedThis);
    }

    if (parent != nullptr)
    {
        parent->m_children.push_back(sharedThis);
    }
    
    m_parent = parent;
    m_isDirty = true;
}

bool Transform::DetachChild(const std::shared_ptr<Transform>& child)
{
    auto iter = std::find_if(m_children.begin(), m_children.end(), [&](const std::shared_ptr<Transform>& object)
    {
        return child == object;
    });
    if (iter != m_children.end())
    {
        m_children.erase(iter);
        return true;
    }

    return false;
}

void Transform::DetachChildren()
{
    m_children.clear();
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

std::vector<std::shared_ptr<Transform>>& Transform::GetChildren() noexcept
{
    return m_children;
}

const std::vector<std::shared_ptr<Transform>>& Transform::GetChildren() const noexcept
{
    return m_children;
}
    
std::shared_ptr<Transform> Transform::GetParent() noexcept
{
    return m_parent;
}

std::shared_ptr<const Transform> Transform::GetParent() const noexcept
{
    return m_parent;
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

const Vector3& Transform::GetPosition() const noexcept
{
    return *reinterpret_cast<const Vector3*>(&m_matWorld.m30);
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
        }
    }
    
    m_isDirty = false;
}

bool Transform::IsDirty() const noexcept
{
    return m_isDirty;
}
    
} /* namespace tgon */
