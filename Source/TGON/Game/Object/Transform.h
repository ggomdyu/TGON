/**
 * @file    Transform.h
 * @author  ggomdyu
 * @since   06/14/2018
 */

#pragma once
#include "Core/Math/Vector3.h"

namespace tgon
{

class TGON_API Transform
{
/* @section Public constructor */
public:
    Transform() = default;
    Transform(const Vector3& position, const Vector3& rotation, const Vector3& scale);
    
/* @section Public method */
public:
    void SetPosition(const Vector3& position) noexcept;
    void SetRotation(const Vector3& rotation) noexcept;
    void SetScale(const Vector3& scale) noexcept;
    Vector3& GetPosition() noexcept;
    const Vector3& GetPosition() const noexcept;
    Vector3& GetRotation() noexcept;
    const Vector3& GetRotation() const noexcept;
    Vector3& GetScale() noexcept;
    const Vector3& GetScale() const noexcept;
    
/* @section Private variable */
private:
    Vector3 m_position;
    Vector3 m_rotation;
    Vector3 m_scale;
};

} /* namespace tgon */
