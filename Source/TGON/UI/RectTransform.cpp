#include "PrecompiledHeader.h"

#include "RectTransform.h"

namespace tgon
{

RectTransform::RectTransform() :
    RectTransform(nullptr)
{
}

RectTransform::RectTransform(const std::shared_ptr<Transform>& parent) noexcept :
    RectTransform(parent, {})
{
}

RectTransform::RectTransform(const std::shared_ptr<Transform>& parent, const Vector3& localPosition, const Vector3& localRotation, const Vector3& localScale) noexcept :
    RectTransform(parent, localPosition, localRotation, localScale, {0.5f, 0.5f})
{
}

RectTransform::RectTransform(const std::shared_ptr<Transform>& parent, const Vector3& localPosition, const Vector3& localRotation, const Vector3& localScale, const Vector2& localPivot) noexcept :
    Transform(parent, localPosition, localRotation, localScale),
    m_localPivot(localPivot)
{
}

RectTransform::RectTransform(const std::shared_ptr<Transform>& parent, const Vector3& localPosition, const Vector2& localPivot) :
    RectTransform(parent, localPosition, {}, {1.0f, 1.0f, 1.0f}, localPivot)
{
}

RectTransform::RectTransform(const std::shared_ptr<Transform>& parent, const Vector3& localPosition) :
    RectTransform(parent, localPosition, {}, {1.0f, 1.0f, 1.0f}, {0.5f, 0.5f})
{
}

RectTransform::RectTransform(const Vector3& localPosition, const Vector3& localRotation, const Vector3& localScale, const Vector2& localPivot) :
    RectTransform(nullptr, localPosition, localRotation, localScale, localPivot)
{
}

RectTransform::RectTransform(const Vector3& localPosition, const Vector2& localPivot) :
    RectTransform(nullptr, localPosition, localPivot)
{
}

RectTransform::RectTransform(const Vector3& localPosition) :
    RectTransform(nullptr, localPosition)
{
}

void RectTransform::SetLocalPivot(const Vector2& localPivot) noexcept
{
    m_localPivot = localPivot;
    m_isDirty = true;
}

const Vector2& RectTransform::GetLocalPivot() const noexcept
{
    return m_localPivot;
}

void RectTransform::SetSize(const FExtent2D& size) noexcept
{
    m_size = size;
    m_isDirty = true;
}

void RectTransform::SetWidth(float width) noexcept
{
    m_size.width = width;
    m_isDirty = true;
}

void RectTransform::SetHeight(float height) noexcept
{
    m_size.height = height;
    m_isDirty = true;
}

const FExtent2D& RectTransform::GetSize() const noexcept
{
    return m_size;
}

float RectTransform::GetWidth() const noexcept
{
    return m_size.width;
}

float RectTransform::GetHeight() const noexcept
{
    return m_size.height;
}

void RectTransform::Update()
{
    
}

} /* namespace tgon */
