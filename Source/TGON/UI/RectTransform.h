/**
 * @file    RectTransform.h
 * @author  ggomdyu
 * @since   10/03/2018
 */

#pragma once
#include "Math/Vector2.h"
#include "Math/Extent.h"

#include "Component/Transform.h"

namespace tgon
{

class RectTransform :
    public Transform
{
/**@section Constructor */
public:
    using Transform::Transform;

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
    void Update() override;

/**@section Variable */
protected:
    Vector2 m_localPivot;
    FExtent2D m_size;
};

} /* namespace tgon */
