/**
 * @file    Transform.h
 * @author  ggomdyu
 * @since   08/19/2018
 */

#pragma once
#include <memory>

#include "Math/Matrix4x4.h"

#include "Component.h"

namespace tgon
{

class Transform :
    public Component,
    public std::enable_shared_from_this<Transform>
{
public:
    TGON_DECLARE_RTTI(Transform)

/**@section Constructor */
public:
    using Component::Component;

/**@section Method */
public:
    void SetLocalPosition(const Vector3& localPosition) noexcept;
    void SetLocalRotation(const Vector3& localRotation) noexcept;
    void SetLocalScale(const Vector3& localScale) noexcept;
    const Vector3& GetLocalPosition() const noexcept;
    const Vector3& GetLocalRotation() const noexcept;
    const Vector3& GetLocalScale() const noexcept;
    const Vector3& GetPosition() const noexcept;
    const Matrix4x4& GetWorldMatrix() const noexcept;
    bool IsDirty() const noexcept;
    void Update() override;

/**@section Variable */
protected:
    Vector3 m_localPosition;
    Vector3 m_localRotation;
    Vector3 m_localScale = Vector3(1.0f, 1.0f, 1.0f);
    Matrix4x4 m_matWorld;
    bool m_isDirty = true;
};

} /* namespace tgon */
