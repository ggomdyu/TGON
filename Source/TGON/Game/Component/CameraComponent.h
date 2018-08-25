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

    /* @brief   Sets the near clipping plane's Z-position. */
    void SetNearZ(float nearZ) noexcept;

    /* @brief   Sets the far clipping plane's Z-position. */
    void SetFarZ(float farZ) noexcept;

    /* @brief   Sets the Field of view. */
    void SetFov(float fov) noexcept;

    /* @brief   Sets the Camera's projection mode. */
    void SetProjectionMode(ProjectionMode projectionMode) noexcept;

    /* @brief   Sets the position of camera. */
    void SetEyePt(const Vector3& eyePt) noexcept;

    /* @brief   Sets the direction vector of camera. */
    void SetLookAt(const Vector3& lookAt) noexcept;

    void SetOrthoPlane(const FRect& orthoPlane) noexcept;

    const FRect& GetOrthoPlane() const noexcept;

    /* @brief   Gets the near clipping plane's Z-position. */
    float GetNearZ() const noexcept;

    /* @brief   Gets the far clipping plane's Z-position. */
    float GetFarZ() const noexcept;

    /* @brief   Gets the field of view. */
    float GetFov() const noexcept;

    ProjectionMode GetProjectionMode() const noexcept;

    /* @brief   Gets the projection matrix. */
    const Matrix4x4& GetProjectionMatrix() const noexcept;

    /* @brief   Gets the view projection matrix. */
    const Matrix4x4& GetViewProjectionMatrix() const noexcept;

    /* @brief   Gets the position of camera. */
    const Vector3& GetEyePt() const noexcept;

    /* @brief   Gets the direction vector of camera. */
    const Vector3& GetLookAt() const noexcept;

/* @section Private variable */
private:
    std::shared_ptr<Camera> m_camera;
};

} /* namespace tgon */
