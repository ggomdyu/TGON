/**
 * @file    Camera.h
 * @author  ggomdyu
 * @since   09/01/2017
 */

#pragma once
#include "Platform/Config.h"
#include "Math/Matrix4x4.h"
#include "Math/Vector3.h"
#include "Math/Rect.h"

namespace tgon
{
    
enum class ProjectionMode
{
    Perspective,
    Orthographic
};

class Camera
{
/**@section Constructor */
public:
    Camera() noexcept;
    Camera(const FRect& orthoPlane, float nearZ, float farZ) noexcept;
    Camera(const Vector3& eyePt, const Vector3& lookAt, float fov, float nearZ, float farZ) noexcept;

/**@section Method */
public:
    void Update();
    void SetNearZ(float nearZ) noexcept;
    void SetFarZ(float farZ) noexcept;
    void SetFov(float fov) noexcept;
    void SetProjectionMode(ProjectionMode projectionMode) noexcept;
    void SetEyePt(const Vector3& eyePt) noexcept;
    void SetLookAt(const Vector3& lookAt) noexcept;
    void SetOrthoPlane(const FRect& orthoPlane) noexcept;
    const FRect& GetOrthoPlane() const noexcept;
    float GetNearZ() const noexcept;
    float GetFarZ() const noexcept;
    float GetFov() const noexcept;
    ProjectionMode GetProjectionMode() const noexcept;
    const Matrix4x4& GetProjectionMatrix() const noexcept;
    const Matrix4x4& GetViewProjectionMatrix() const noexcept;
    const Vector3& GetEyePt() const noexcept;
    const Vector3& GetLookAt() const noexcept;
    
/**@section Variable */
private:
    Vector3 m_eyePt;
    Vector3 m_lookAt;
    float m_fov;
    float m_nearZ;
    float m_farZ;
    FRect m_orthoPlane;
    Matrix4x4 m_matProj;
    Matrix4x4 m_matViewProj;
    bool m_isDirty;
    ProjectionMode m_projectionMode;
};

} /* namespace tgon */
