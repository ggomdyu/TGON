/**
 * @file    GraphicsObject.h
 * @author  ggomdyu
 * @since   08/02/2018
 */

#pragma once

#include "Core/Math/Vector3.h"
#include "Core/Math/Matrix4x4.h"

namespace tgon
{

class Transform
{
/* @section Public method */
public:
    /* @brief   Sets the position. */
    void SetPosition(const Vector3& position);
    
    /* @brief   Sets the rotation. */
    void SetRotation(const Vector3& rotation);
    
    /* @brief   Sets the scale. */
    void SetScale(const Vector3& scale);
    
    /* @brief   Gets the position. */
    const Vector3& GetPosition() const noexcept;
    
    /* @brief   Gets the rotation. */
    const Vector3& GetRotation() const noexcept;
    
    /* @brief   Gets the scale. */
    const Vector3& GetScale() const noexcept;
    
    void Update();
    
    /* @brief   Gets the world-view-projection matrix. */
    const Matrix4x4& GetWVP() const noexcept;
    
/* @section Private variable */
private:
    Vector3 m_position;
    Vector3 m_rotation;
    Vector3 m_scale;
    Matrix4x4 m_matWVP;
    bool m_isDirty;
};

} /* namespace tgon */
