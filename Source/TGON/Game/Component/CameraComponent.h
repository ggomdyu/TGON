/**
 * @file    CameraComponent.h
 * @author  ggomdyu
 * @since   08/11/2018
 */

#pragma once
#include "Graphics/Render/Material.h"
#include "Graphics/Render/Mesh.h"
#include "Graphics/Engine/GraphicsModule.h"

#include "Component.h"

namespace tgon
{

class TGON_API CameraComponent :
	public Component
{
public:
    TGON_RUNTIME_OBJECT(CameraComponent);

/**@section Public constructor */
public:
    CameraComponent(const Rect& orthoPlane, float nearZ, float farZ) :
        CameraComponent(std::make_shared<Camera>(orthoPlane, nearZ, farZ))
    {
    }

    CameraComponent(const Vector3& eyePt, const Vector3& lookAt, float fov, float nearZ, float farZ) :
        CameraComponent(std::make_shared<Camera>(eyePt, lookAt, fov, nearZ, farZ))
    {
    }

/**@section Private constructor */
public:
    CameraComponent(const std::shared_ptr<Camera>& camera) :
        m_camera(camera)
    {
        Application::GetInstance()->GetEngine()->FindModule<GraphicsModule>()->GetRenderStage().AddCamera(camera);
    }

/**@section Public destructor */
public:
    virtual ~CameraComponent() override
    {
        Application::GetInstance()->GetEngine()->FindModule<GraphicsModule>()->GetRenderStage().RemoveCamera(m_camera);
    }

/**@section Public method */
public:
	virtual void Update() override
    {
        m_camera->Update();
    }

    std::shared_ptr<Camera>& GetCamera() noexcept
    {
        return m_camera;
    }

    const std::shared_ptr<const Camera> GetCamera() const noexcept
    {
        return m_camera;
    }

/**@section Private variable */
private:
    std::shared_ptr<Camera> m_camera;
};

} /* namespace tgon */
