/**
 * @file    RectTransform.h
 * @author  ggomdyu
 * @since   10/03/2018
 */

#pragma once
#include "Core/Math/Vector2.h"
#include "Core/Math/Extent.h"

#include "Transform.h"

namespace tgon
{

class TGON_API RectTransform :
    private Transform
{
/**@section Constructor */
public:
    RectTransform();
    
    RectTransform(const Vector2& localAnchor, const Vector2& localPivot);

/**@section Method */
public:
    using Transform::GetLocalPosition;
    using Transform::GetLocalRotation;
    using Transform::GetLocalScale;
    using Transform::GetLocalMatrix;

    /**@brief   Sets a local anchor. */
    void SetLocalAnchor(const Vector2& localAnchor) noexcept;

    /**@brief   Sets a local pivot. */
    void SetLocalPivot(const Vector2& localPivot) noexcept;

    /**@brief   Gets the local anchor. */
    const Vector2& GetLocalAnchor() const noexcept;

    /**@brief   Gets the local pivot. */
    const Vector2& GetLocalPivot() const noexcept;

    void SetSize(const FExtent2D& size) noexcept;

    void SetWidth(float width) noexcept;

    void SetHeight(float height) noexcept;

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
