#include "PrecompiledHeader.h"

#include "Core/Math/Mathematics.h"

#include "Camera.h"

namespace tgon
{
    
Camera::Camera() noexcept :
    m_eyePt(0.0f, 0.0f, 0.0f),
    m_lookAt(0.0f, 0.0f, -50.0f),
    m_fieldOfView(Pi / 8),
    m_nearZ(0.1f),
    m_farZ(1000.0f)
{
}

void Camera::SetNearZ(float nearZ) noexcept
{
    m_nearZ = nearZ;
}

void Camera::SetFarZ(float farZ) noexcept
{
    m_farZ = farZ;
}

void Camera::SetFieldOfView(float fieldOfView) noexcept
{
    m_fieldOfView = fieldOfView;
}

void Camera::SetProjectionMode(ProjectionMode projectionMode) noexcept
{
    m_projectionMode = projectionMode;
}

void Camera::SetEyePt(const Vector3& eyePt) noexcept
{
    m_eyePt = eyePt;
}

void Camera::SetLookAt(const Vector3& lookAt) noexcept
{
    m_lookAt = lookAt;
}

float Camera::GetNearZ() const noexcept
{
    return m_nearZ;
}

float Camera::GetFarZ() const noexcept
{
    return m_farZ;
}

float Camera::GetFieldOfView() const noexcept
{
    return m_fieldOfView;
}

ProjectionMode Camera::GetProjectionMode() const noexcept
{
    return m_projectionMode;
}

const Matrix4x4& Camera::GetViewProjMatrix() const noexcept
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

void Camera::Update()
{
    //(float)extent.width / (float)extent.height
    m_matViewProj = Matrix4x4::LookAtRH(m_eyePt, m_lookAt, {0.0f, 1.0f, 0.0f});
    m_matViewProj *= Matrix4x4::PerspectiveRH(m_fieldOfView, 1, m_nearZ, m_farZ);
}
    
} /* namespace tgon */
