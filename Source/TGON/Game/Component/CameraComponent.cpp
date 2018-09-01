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
    
CameraComponent::CameraComponent(const Rect& orthoPlane, float nearZ, float farZ) :
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
//    Engine::GetInstance()->FindModule<GraphicsModule>()->GetRenderStage().RemoveCamera(m_camera);
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

} /* namespace tgon */
