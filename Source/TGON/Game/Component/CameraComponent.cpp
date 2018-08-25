#include "PrecompiledHeader.h"

#include "Core/Engine/Engine.h"
#include "Graphics/Engine/GraphicsModule.h"

#include "../Object/GameObject.h"

#include "CameraComponent.h"

namespace tgon
{

CameraComponent::CameraComponent() :
    m_camera(std::make_shared<Camera>())
{
    Engine::GetInstance()->FindModule<GraphicsModule>()->GetRenderStage().AddCamera(m_camera);
}
    
CameraComponent::CameraComponent(const FRect& orthoPlane, float nearZ, float farZ) :
    m_camera(std::make_shared<Camera>(orthoPlane, nearZ, farZ))
{
    Engine::GetInstance()->FindModule<GraphicsModule>()->GetRenderStage().AddCamera(m_camera);
}
    
CameraComponent::CameraComponent(const Vector3& eyePt, const Vector3& lookAt, float fov, float nearZ, float farZ) :
    m_camera(std::make_shared<Camera>(eyePt, lookAt, fov, nearZ, farZ))
{
    Engine::GetInstance()->FindModule<GraphicsModule>()->GetRenderStage().AddCamera(m_camera);
}

CameraComponent::~CameraComponent()
{
    Engine::GetInstance()->FindModule<GraphicsModule>()->GetRenderStage().RemoveCamera(m_camera);
}

void CameraComponent::Update()
{
    m_camera->Update();
}

std::shared_ptr<Camera>& CameraComponent::GetCamera() noexcept
{
    return m_camera;
}

const std::shared_ptr<const Camera> CameraComponent::GetCamera() const noexcept
{
    return m_camera;
}

void CameraComponent::SetNearZ(float nearZ) noexcept
{
    m_camera->SetNearZ(nearZ);
}

void CameraComponent::SetFarZ(float farZ) noexcept
{
    m_camera->SetFarZ(farZ);
}

void CameraComponent::SetFov(float fov) noexcept
{
    m_camera->SetFov(fov);
}

void CameraComponent::SetProjectionMode(ProjectionMode projectionMode) noexcept
{
    m_camera->SetProjectionMode(projectionMode);
}

void CameraComponent::SetEyePt(const Vector3& eyePt) noexcept
{
    m_camera->SetEyePt(eyePt);
}

void CameraComponent::SetLookAt(const Vector3& lookAt) noexcept
{
    m_camera->SetLookAt(lookAt);
}

void CameraComponent::SetOrthoPlane(const FRect& orthoPlane) noexcept
{
    m_camera->SetOrthoPlane(orthoPlane);
}

const FRect& CameraComponent::GetOrthoPlane() const noexcept
{
    return m_camera->GetOrthoPlane();
}

float CameraComponent::GetNearZ() const noexcept
{
    return m_camera->GetNearZ();
}

float CameraComponent::GetFarZ() const noexcept
{
    return m_camera->GetFarZ();
}

float CameraComponent::GetFov() const noexcept
{
    return m_camera->GetFov();
}

ProjectionMode CameraComponent::GetProjectionMode() const noexcept
{
    return m_camera->GetProjectionMode();
}

const Matrix4x4& CameraComponent::GetProjectionMatrix() const noexcept
{
    return m_camera->GetProjectionMatrix();
}

const Matrix4x4& CameraComponent::GetViewProjectionMatrix() const noexcept
{
    return m_camera->GetViewProjectionMatrix();
}

const Vector3& CameraComponent::GetEyePt() const noexcept
{
    return m_camera->GetEyePt();
}

const Vector3& CameraComponent::GetLookAt() const noexcept
{
    return m_camera->GetLookAt();
}

} /* namespace tgon */
