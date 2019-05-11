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
    RectTransform(const Vector2& localAnchor, const Vector2& localPivot);

/**@section Method */
public:
    void SetLocalAnchor(const Vector2& localAnchor) noexcept;
    void SetLocalPivot(const Vector2& localPivot) noexcept;
    void SetSize(const FExtent2D& size) noexcept;
    void SetWidth(float width) noexcept;
    void SetHeight(float height) noexcept;
    const Vector2& GetLocalAnchor() const noexcept;
    const Vector2& GetLocalPivot() const noexcept;
    const FExtent2D& GetSize() const noexcept;
    float GetWidth() const noexcept;
    float GetHeight() const noexcept;
    virtual void Update() override;

/**@section Variable */
protected:
    Vector2 m_localAnchor;
    Vector2 m_localPivot;
    FExtent2D m_size;
};

} /* namespace tgon */
