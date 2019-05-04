#include "PrecompiledHeader.h"

#include "Core/Math/Mathematics.h"

#include "Camera.h"
#include "CameraType.h"

namespace tgon
{
    
Camera::Camera() noexcept :
    m_eyePt(0.0f, 0.0f, 5.0f),
    m_lookAt(0.0f, 0.0f, 0.0f),
    m_fov(Pi / 8),
    m_nearZ(0.1f),
    m_farZ(1000.0f),
    m_isDirty(true),
    m_projectionMode(ProjectionMode::Perspective)
{
    this->Update();
}
    
Camera::Camera(const FRect& orthoPlane, float nearZ, float farZ) noexcept :
    m_eyePt(0.0f, 0.0f, 5.0f),
    m_lookAt(0.0f, 0.0f, 0.0f),
    m_fov(Pi / 8),
    m_orthoPlane(orthoPlane),
    m_nearZ(nearZ),
    m_farZ(farZ),
    m_isDirty(true),
    m_projectionMode(ProjectionMode::Orthographic)
{
    this->Update();
}
    
Camera::Camera(const Vector3& eyePt, const Vector3& lookAt, float fov, float nearZ, float farZ) noexcept :
    m_eyePt(eyePt),
    m_lookAt(lookAt),
    m_fov(fov),
    m_nearZ(nearZ),
    m_farZ(farZ),
    m_isDirty(true),
    m_projectionMode(ProjectionMode::Perspective)
{
    this->Update();
}
    
void Camera::Update()
{
    if (m_isDirty == true)
    {   
        if (m_projectionMode == ProjectionMode::Perspective)
        {
            m_matProj = Matrix4x4::PerspectiveRH(m_fov, 1, m_nearZ, m_farZ);
            m_matViewProj = Matrix4x4::LookAtRH(m_eyePt, m_lookAt, {0.0f, 1.0f, 0.0f});
            m_matViewProj *= m_matProj;
        }
        else //if (m_projectionMode == ProjectionMode::Orthographic)
        {
            m_matProj = Matrix4x4::OrthographicRH(m_orthoPlane.x, m_orthoPlane.width, m_orthoPlane.y, m_orthoPlane.height, m_nearZ, m_farZ);
            m_matViewProj = Matrix4x4::Scale(100.0f, 100.0f, 1.0f);
            m_matViewProj *= m_matProj;
        }
        
        m_isDirty = false;
    }
}

void Camera::SetNearZ(float nearZ) noexcept
{
    m_nearZ = nearZ;
    m_isDirty = true;
}

void Camera::SetFarZ(float farZ) noexcept
{
    m_farZ = farZ;
    m_isDirty = true;
}

void Camera::SetFov(float fov) noexcept
{
    m_fov = fov;
    m_isDirty = true;
}

void Camera::SetProjectionMode(ProjectionMode projectionMode) noexcept
{
    m_projectionMode = projectionMode;
    m_isDirty = true;
}

void Camera::SetEyePt(const Vector3& eyePt) noexcept
{
    m_eyePt = eyePt;
    m_isDirty = true;
}

void Camera::SetLookAt(const Vector3& lookAt) noexcept
{
    m_lookAt = lookAt;
    m_isDirty = true;
}
    
void Camera::SetOrthoPlane(const FRect& orthoPlane) noexcept
{
    m_orthoPlane = orthoPlane;
    m_isDirty = true;
}

const FRect& Camera::GetOrthoPlane() const noexcept
{
    return m_orthoPlane;
}

float Camera::GetNearZ() const noexcept
{
    return m_nearZ;
}

float Camera::GetFarZ() const noexcept
{
    return m_farZ;
}

float Camera::GetFov() const noexcept
{
    return m_fov;
}

ProjectionMode Camera::GetProjectionMode() const noexcept
{
    return m_projectionMode;
}

const Matrix4x4& Camera::GetProjectionMatrix() const noexcept
{
    return m_matProj;
}

const Matrix4x4& Camera::GetViewProjectionMatrix() const noexcept
{
    return m_matViewProj;
}

const Vector3& Camera::GetEyePt() const noexcept
{
    return m_eyePt;
}

const Vector3& Camera::GetLookAt() const noexcept
{
    return m_lookAt;
}

} /* namespace tgon */
