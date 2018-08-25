/**
 * @file    MeshRendererComponent.h
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

/* @section Public constructor */
public:
    CameraComponent();

    CameraComponent(const FRect& orthoPlane, float nearZ, float farZ);

    CameraComponent(const Vector3& eyePt, const Vector3& lookAt, float fov, float nearZ, float farZ);

/* @section Public destructor */
public:
    virtual ~CameraComponent() override;

/* @section Public method */
public:
	virtual void Update() override;

    std::shared_ptr<Camera>& GetCamera() noexcept;

    const std::shared_ptr<const Camera> GetCamera() const noexcept;

/* @section Private variable */
private:
    std::shared_ptr<Camera> m_camera;
};

} /* namespace tgon */
