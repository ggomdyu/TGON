/**
 * @file    Transform.h
 * @author  ggomdyu
 * @since   08/19/2018
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
    Transform() noexcept :
        m_scale({1.0f, 1.0f, 1.0f}),
        m_isDirty(false)
    {
    }
    
    /* @brief   Sets the position. */
    void SetPosition(const Vector3& position)
    {
        m_position = position;
        m_isDirty = true;
    }
    
    /* @brief   Sets the rotation. */
    void SetRotation(const Vector3& rotation)
    {
        m_rotation = rotation;
        m_isDirty = true;
    }
    
    /* @brief   Sets the scale. */
    void SetScale(const Vector3& scale)
    {
        m_scale = scale;
        m_isDirty = true;
    }
    
    /* @brief   Gets the position. */
    const Vector3& GetPosition() const noexcept
    {
        return m_position;
    }
    
    /* @brief   Gets the rotation. */
    const Vector3& GetRotation() const noexcept
    {
        return m_rotation;
    }
    
    /* @brief   Gets the scale. */
    const Vector3& GetScale() const noexcept
    {
        return m_scale;
    }
    
    void Update();
    
    /* @brief   Gets the world-view-projection matrix. */
    const Matrix4x4& GetWorldMatrix() const noexcept
    {
        return m_matWorld;
    }
    
/* @section Private variable */
private:
    Vector3 m_position;
    Vector3 m_rotation;
    Vector3 m_scale;
    Matrix4x4 m_matWorld;
    bool m_isDirty;
};

} /* namespace tgon */
