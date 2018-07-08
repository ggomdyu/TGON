/**
 * @file    Camera.h
 * @author  ggomdyu
 * @since   09/01/2017
 */

#pragma once
#include "Core/Platform/Config.h"
#include "Core/Math/Matrix4x4.h"
#include "Core/Math/Vector3.h"

namespace tgon
{
    
enum class ProjectionMode;

class TGON_API Camera
{
/* @section Public constructor */
public:
    Camera() noexcept ;

/* @section Public method */
public:
    void Update();
    void Draw();
    
    void SetNearZ(float nearZ) noexcept;
    void SetFarZ(float farZ) noexcept;
    void SetFieldOfView(float fieldOfView) noexcept;
    void SetProjectionMode(ProjectionMode projectionMode) noexcept;
    void SetEyePt(const Vector3& eyePt) noexcept;
    void SetLookAt(const Vector3& lookAt) noexcept;

    float GetNearZ() const noexcept;
    float GetFarZ() const noexcept;
    float GetFieldOfView() const noexcept;
    ProjectionMode GetProjectionMode() const noexcept;
    const Matrix4x4& GetViewProjectionMatrix() const noexcept;
    const Vector3& GetEyePt() const noexcept;
    const Vector3& GetLookAt() const noexcept;

/* @section Private variable */
private:
    float m_nearZ;
    float m_farZ;
    float m_fieldOfView;
    ProjectionMode m_projectionMode;
    Vector3 m_eyePt;
    Vector3 m_lookAt;
    Matrix4x4 m_matViewProj;
};

} /* namespace tgon */
