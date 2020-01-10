/**
 * @file    Camera.h
 * @author  ggomdyu
 * @since   09/01/2017
 */

#pragma once
#include "Math/Matrix4x4.h"
#include "Math/Rect.h"

namespace tgon
{
    
enum class ProjectionMode
{
    Perspective,
    Orthographic
};

class Camera
{
/**@section Constructor */
public:
    Camera(ProjectionMode projectionMode, float nearZ, float farZ) noexcept;

/**@section Destructor */
public:
    virtual ~Camera() = 0;
    
/**@section Method */
public:
    virtual void Update() = 0;
    void SetNearZ(float nearZ) noexcept;
    void SetFarZ(float farZ) noexcept;
    float GetNearZ() const noexcept;
    float GetFarZ() const noexcept;
    ProjectionMode GetProjectionMode() const noexcept;
    const Matrix4x4& GetProjectionMatrix() const noexcept;
    const Matrix4x4& GetViewProjectionMatrix() const noexcept;
    
/**@section Variable */
protected:
    float m_nearZ;
    float m_farZ;
    Matrix4x4 m_matProj;
    Matrix4x4 m_matViewProj;
    bool m_isDirty;
    ProjectionMode m_projectionMode;
};

class PerspectiveCamera :
    public Camera
{
/**@section Constructor */
public:
    PerspectiveCamera(const Vector3& eyePt, const Vector3& lookAt, float fov, float nearZ, float farZ) noexcept;

/**@section Method */
public:
    void Update() override;
    void SetFov(float fov) noexcept;
    void SetEyePt(const Vector3& eyePt) noexcept;
    void SetLookAt(const Vector3& lookAt) noexcept;
    float GetFov() const noexcept;
    const Vector3& GetEyePt() const noexcept;
    const Vector3& GetLookAt() const noexcept;

/**@section Variable */
protected:
    Vector3 m_eyePt;
    Vector3 m_lookAt;
    float m_fov;
};

class OrthographicCamera :
    public Camera
{
/**@section Constructor */
public:
    OrthographicCamera(const FRect& orthoPlane, float nearZ, float farZ) noexcept;

/**@section Method */
public:
    void Update() override;
    void SetOrthoPlane(const FRect& orthoPlane) noexcept;
    const FRect& GetOrthoPlane() const noexcept;

/**@section Variable */
protected:
    FRect m_orthoPlane;
};

} /* namespace tgon */
