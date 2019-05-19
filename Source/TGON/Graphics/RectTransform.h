/**
 * @file    RectTransform.h
 * @author  ggomdyu
 * @since   10/03/2018
 */

#pragma once
#include "Math/Vector2.h"
#include "Math/Extent.h"

#include "Transform.h"

namespace tgon
{

class TGON_API RectTransform :
    public Transform
{
/**@section Constructor */
public:
    RectTransform();
    RectTransform(const std::shared_ptr<Transform>& parent, const Vector3& localPosition, const Vector3& localRotation, const Vector3& localScale) noexcept;
    RectTransform(const std::shared_ptr<Transform>& parent, const Vector3& localPosition, const Vector3& localRotation, const Vector3& localScale, const Vector2& localPivot) noexcept;
    RectTransform(const std::shared_ptr<Transform>& parent, const Vector3& localPosition, const Vector2& localPivot);
    RectTransform(const std::shared_ptr<Transform>& parent, const Vector3& localPosition);
    RectTransform(const Vector3& localPosition, const Vector3& localRotation, const Vector3& localScale, const Vector2& localPivot);
    RectTransform(const Vector3& localPosition, const Vector2& localPivot);
    explicit RectTransform(const std::shared_ptr<Transform>& parent) noexcept;
    explicit RectTransform(const Vector3& localPosition);

/**@section Method */
public:
    void SetLocalPivot(const Vector2& localPivot) noexcept;
    void SetSize(const FExtent2D& size) noexcept;
    void SetWidth(float width) noexcept;
    void SetHeight(float height) noexcept;
    const Vector2& GetLocalPivot() const noexcept;
    const FExtent2D& GetSize() const noexcept;
    float GetWidth() const noexcept;
    float GetHeight() const noexcept;
    virtual void Update() override;

/**@section Variable */
protected:
    Vector2 m_localPivot;
    FExtent2D m_size;
};

} /* namespace tgon */
