#include "PrecompiledHeader.h"

#include "RectTransform.h"

namespace tgon
{

RectTransform::RectTransform() :
    Transform(),
    m_localAnchor(0.0f, 0.0f),
    m_localPivot(0.5f, 0.5f)
{
}

RectTransform::RectTransform(const Vector2& localAnchor, const Vector2& localPivot) :
    m_localAnchor(localAnchor),
    m_localPivot(localPivot)
{
}

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
