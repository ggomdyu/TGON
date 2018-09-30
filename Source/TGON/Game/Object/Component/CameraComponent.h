/**
 * @file    CameraComponent.h
 * @author  ggomdyu
 * @since   08/11/2018
 */

#pragma once
#include "Component.h"

namespace tgon
{

class Camera;
class GraphicsModule;

class TGON_API CameraComponent :
	public Component
{
public:
    TGON_DECLARE_RTTI(CameraComponent);

/**@section Public constructor */
public:
    CameraComponent();

    CameraComponent(const Rect& orthoPlane, float nearZ, float farZ);

    CameraComponent(const Vector3& eyePt, const Vector3& lookAt, float fov, float nearZ, float farZ);

/**@section Private constructor */
public:
    CameraComponent(const std::shared_ptr<Camera>& camera);

/**@section Public destructor */
public:
    virtual ~CameraComponent() override;

/**@section Public method */
public:
	virtual void Update() override;

    std::shared_ptr<Camera>& GetCamera() noexcept;

    std::shared_ptr<const Camera> GetCamera() const noexcept;

/**@section Private variable */
private:
    std::shared_ptr<Camera> m_camera;
    std::weak_ptr<GraphicsModule> m_graphicsModule;
};

} /* namespace tgon */
