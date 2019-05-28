/**
 * @file    Camera.h
 * @author  ggomdyu
 * @since   09/01/2017
 */

#pragma once
#include "Platform/Config.h"
#include "Math/Matrix4x4.h"
#include "Math/Vector3.h"
#include "Math/Rect.h"

#include "GraphicsType.h"
#include "CameraType.h"

namespace tgon
{
    
enum class ProjectionMode
{
    Perspective,
    Orthographic
};

class TGON_API Camera
{
/**@section Constructor */
public:
    Camera() noexcept;
    Camera(const FRect& orthoPlane, float nearZ, float farZ) noexcept;
    Camera(const Vector3& eyePt, const Vector3& lookAt, float fov, float nearZ, float farZ) noexcept;

/**@section Method */
public:
    void Update();
    
    /**@brief   Sets the near clipping plane's Z-position. */
    void SetNearZ(float nearZ) noexcept;
    
    /**@brief   Sets the far clipping plane's Z-position. */
    void SetFarZ(float farZ) noexcept;
    
    /**@brief   Sets the Field of view. */
    void SetFov(float fov) noexcept;
    
    /**@brief   Sets the Camera's projection mode. */
    void SetProjectionMode(ProjectionMode projectionMode) noexcept;
    
    /**@brief   Sets the position of camera. */
    void SetEyePt(const Vector3& eyePt) noexcept;
    
    /**@brief   Sets the direction vector of camera. */
    void SetLookAt(const Vector3& lookAt) noexcept;
    
    void SetOrthoPlane(const FRect& orthoPlane) noexcept;

    const FRect& GetOrthoPlane() const noexcept;

    /**@brief   Gets the near clipping plane's Z-position. */
    float GetNearZ() const noexcept;
    
    /**@brief   Gets the far clipping plane's Z-position. */
    float GetFarZ() const noexcept;
    
    /**@brief   Gets the field of view. */
    float GetFov() const noexcept;
    
    ProjectionMode GetProjectionMode() const noexcept;
    
    /**@brief   Gets the projection matrix. */
    const Matrix4x4& GetProjectionMatrix() const noexcept;

    /**@brief   Gets the view projection matrix. */
    const Matrix4x4& GetViewProjectionMatrix() const noexcept;
    
    /**@brief   Gets the position of camera. */
    const Vector3& GetEyePt() const noexcept;
    
    /**@brief   Gets the direction vector of camera. */
    const Vector3& GetLookAt() const noexcept;
    
/**@section Variable */
private:
    Vector3 m_eyePt;
    Vector3 m_lookAt;
    float m_fov;
    float m_nearZ;
    float m_farZ;
    FRect m_orthoPlane;
    Matrix4x4 m_matProj;
    Matrix4x4 m_matViewProj;
    bool m_isDirty;
    ProjectionMode m_projectionMode;
};

} /* namespace tgon */
