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

/**@section Constructor */
public:
    CameraComponent();
    CameraComponent(const FRect& orthoPlane, float nearZ, float farZ);
    CameraComponent(const Vector3& eyePt, const Vector3& lookAt, float fov, float nearZ, float farZ);
    CameraComponent(const std::shared_ptr<Camera>& camera);

/**@section Destructor */
public:
    virtual ~CameraComponent() override;

/**@section Method */
public:
	virtual void Update() override;
    std::shared_ptr<Camera> GetCamera() noexcept;
    std::shared_ptr<const Camera> GetCamera() const noexcept;

/**@section Variable */
private:
    std::shared_ptr<Camera> m_camera;
    std::weak_ptr<GraphicsModule> m_graphicsModule;
};

} /* namespace tgon */
