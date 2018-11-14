/**
 * @file    Transform.h
 * @author  ggomdyu
 * @since   08/19/2018
 */

#pragma once
#include "Core/Platform/Config.h"
#include "Core/Math/Vector3.h"
#include "Core/Math/Matrix4x4.h"

namespace tgon
{

class TGON_API Transform
{
/**@section Public constructor */
public:
    Transform() noexcept;
    
/**@section Public method */
public:
    /**@brief   Sets the position. */
    void SetLocalPosition(const Vector3& position) noexcept;
    
    /**@brief   Sets the rotation. */
    void SetLocalRotation(const Vector3& rotation) noexcept;
    
    /**@brief   Sets the scale. */
    void SetLocalScale(const Vector3& scale) noexcept;
    
    /**@brief   Gets the position. */
    const Vector3& GetLocalPosition() const noexcept;
    
    /**@brief   Gets the rotation. */
    const Vector3& GetLocalRotation() const noexcept;
    
    /**@brief   Gets the scale. */
    const Vector3& GetLocalScale() const noexcept;
    
    /**@brief   Gets the world-view-projection matrix. */
    const Matrix4x4& GetLocalMatrix() const noexcept;
    
    virtual void Update();
    
/**@section Protected variable */
protected:
    Vector3 m_localPosition;
    Vector3 m_localRotation;
    Vector3 m_localScale;
    Matrix4x4 m_matLocal;
    bool m_isDirty;
};

} /* namespace tgon */
