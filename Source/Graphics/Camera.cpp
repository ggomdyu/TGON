#include "PrecompiledHeader.h"

#include "Math/Mathematics.h"

#include "Camera.h"

namespace tg
{
    
Camera::Camera(ProjectionMode projectionMode, float nearZ, float farZ) noexcept :
    m_nearZ(nearZ),
    m_farZ(farZ),
    m_isDirty(true),
    m_projectionMode(projectionMode)
{
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

void Camera::SetRenderTarget(const std::shared_ptr<RenderTarget>& renderTarget)
{
    m_renderTarget = renderTarget;
}

float Camera::GetNearZ() const noexcept
{
    return m_nearZ;
}

float Camera::GetFarZ() const noexcept
{
    return m_farZ;
}

std::shared_ptr<RenderTarget> Camera::GetRenderTarget() noexcept
{
    return m_renderTarget;
}

std::shared_ptr<const RenderTarget> Camera::GetRenderTarget() const noexcept
{
    return m_renderTarget;
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

PerspectiveCamera::PerspectiveCamera(const Vector3& eyePt, const Vector3& lookAt, float fov, float nearZ, float farZ) noexcept :
    Camera(ProjectionMode::Perspective, nearZ, farZ),
    m_eyePt(eyePt),
    m_lookAt(lookAt),
    m_fov(fov)
{
    this->Update();
}

void PerspectiveCamera::Update()
{
    if (m_isDirty == true)
    {
        m_matProj = Matrix4x4::PerspectiveRH(m_fov, 1, m_nearZ, m_farZ);
        m_matViewProj = Matrix4x4::LookAtRH(m_eyePt, m_lookAt, {0.0f, 1.0f, 0.0f});
        m_matViewProj *= m_matProj;

        m_isDirty = false;
    }
}

void PerspectiveCamera::SetEyePt(const Vector3& eyePt) noexcept
{
    m_eyePt = eyePt;
    m_isDirty = true;
}

void PerspectiveCamera::SetLookAt(const Vector3& lookAt) noexcept
{
    m_lookAt = lookAt;
    m_isDirty = true;
}

void PerspectiveCamera::SetFov(float fov) noexcept
{
    m_fov = fov;
    m_isDirty = true;
}

const Vector3& PerspectiveCamera::GetEyePt() const noexcept
{
    return m_eyePt;
}

const Vector3& PerspectiveCamera::GetLookAt() const noexcept
{
    return m_lookAt;
}

float PerspectiveCamera::GetFov() const noexcept
{
    return m_fov;
}

OrthographicCamera::OrthographicCamera(const FRect& orthoPlane, float nearZ, float farZ) noexcept :
    Camera(ProjectionMode::Orthographic, nearZ, farZ),
    m_orthoPlane(orthoPlane)
{
    this->Update();
}

void OrthographicCamera::Update()
{
    if (m_isDirty == true)
    {
        m_matProj = Matrix4x4::OrthographicRH(m_orthoPlane.x, m_orthoPlane.x + m_orthoPlane.width, m_orthoPlane.y, m_orthoPlane.y + m_orthoPlane.height, m_nearZ, m_farZ);
        m_matViewProj *= m_matProj;
        
        m_isDirty = false;
    }
}

void OrthographicCamera::SetOrthoPlane(const FRect& orthoPlane) noexcept
{
    m_orthoPlane = orthoPlane;
    m_isDirty = true;
}

const FRect& OrthographicCamera::GetOrthoPlane() const noexcept
{
    return m_orthoPlane;
}

}
