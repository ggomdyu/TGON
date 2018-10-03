/**
 * @file    RectTransform.h
 * @author  ggomdyu
 * @since   10/03/2018
 */

#pragma once
#include "Core/Math/Vector2.h"

#include "Transform.h"

namespace tgon
{

class RectTransform final :
    private Transform
{
/**@section Public method */
public:
    using Transform::GetLocalPosition;
    using Transform::GetLocalRotation;
    using Transform::GetLocalScale;
    using Transform::GetLocalMatrix;

    void Update();

    /**@brief   Sets a local anchor. */
    void SetLocalAnchor(const Vector2& localAnchor) noexcept;

    /**@brief   Sets a local pivot. */
    void SetLocalPivot(const Vector2& localPivot) noexcept;

    /**@brief   Gets the local anchor. */
    const Vector2& GetLocalAnchor() const noexcept;

    /**@brief   Gets the local pivot. */
    const Vector2& GetLocalPivot() const noexcept;

/**@section Protected variable */
protected:
    Vector2 m_localAnchor;
    Vector2 m_localPivot;
};

} /* namespace tgon */
