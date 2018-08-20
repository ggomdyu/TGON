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
    m_projectionMode(ProjectionMode::Perspective),
    m_fillMode(FillMode::Solid),
    m_cullMode(CullMode::CW)
{
    this->Update();
}
    
Camera::Camera(float left, float right, float bottom, float top, float nearZ, float farZ) noexcept :
    m_eyePt(0.0f, 0.0f, 5.0f),
    m_lookAt(0.0f, 0.0f, 0.0f),
    m_fov(Pi / 8),
    m_nearZ(nearZ),
    m_farZ(farZ),
    m_isDirty(true),
    m_projectionMode(ProjectionMode::Orthographic),
    m_fillMode(FillMode::Solid),
    m_cullMode(CullMode::CW)
{
    
}
    
Camera::Camera(const Vector3& eyePt, const Vector3& lookAt, float fov, float nearZ, float farZ, ProjectionMode projectionMode, FillMode fillMode, CullMode cullMode) noexcept :
    m_eyePt(eyePt),
    m_lookAt(lookAt),
    m_fov(fov),
    m_nearZ(nearZ),
    m_farZ(farZ),
    m_projectionMode(projectionMode),
    m_fillMode(fillMode),
    m_cullMode(cullMode)
{
}
    
void Camera::Update()
{
    if (m_isDirty == true)
    {
        // TODO: This code supposed to use OpenGL, so you should use LH function when you support DirectX.
        
        if (m_projectionMode == ProjectionMode::Perspective)
        {
            m_matViewProj = Matrix4x4::LookAtRH(m_eyePt, m_lookAt, {0.0f, 1.0f, 0.0f});
            m_matViewProj *= Matrix4x4::PerspectiveRH(m_fov, 1, m_nearZ, m_farZ);
        }
        else //if (m_projectionMode == ProjectionMode::Orthographic)
        {
            m_matViewProj = Matrix4x4::OrthographicLH(0.0f, 960.0f, 0.0f, 540.0f, -1.0f, 1000.0f);
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
    
void Camera::SetFillMode(FillMode fillMode) noexcept
{
    m_fillMode = fillMode;
}
    
void Camera::SetCullMode(CullMode cullMode) noexcept
{
    m_cullMode = cullMode;
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
    
FillMode Camera::GetFillMode() const noexcept
{
    return m_fillMode;
}

CullMode Camera::GetCullMode() const noexcept
{
    return m_cullMode;
}

} /* namespace tgon */
