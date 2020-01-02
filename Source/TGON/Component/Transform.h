/**
 * @file    Transform.h
 * @author  ggomdyu
 * @since   08/19/2018
 */

#pragma once
#include <vector>

#include "Component/Component.h"
#include "Math/Matrix4x4.h"

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
    void SetParent(const std::shared_ptr<Transform>& parent);
    void DetachChildren();
    void SetLocalPosition(const Vector3& localPosition) noexcept;
    void SetLocalRotation(const Vector3& localRotation) noexcept;
    void SetLocalScale(const Vector3& localScale) noexcept;
    std::vector<std::shared_ptr<Transform>>& GetChildren() noexcept;
    const std::vector<std::shared_ptr<Transform>>& GetChildren() const noexcept;
    std::shared_ptr<Transform> GetParent() noexcept;
    std::shared_ptr<const Transform> GetParent() const noexcept;
    const Vector3& GetLocalPosition() const noexcept;
    const Vector3& GetLocalRotation() const noexcept;
    const Vector3& GetLocalScale() const noexcept;
    const Vector3& GetPosition() const noexcept;
    const Matrix4x4& GetWorldMatrix() const noexcept;
    bool IsDirty() const noexcept;
    void Update() override;

private:
    bool DetachChild(const std::shared_ptr<Transform>& child);

/**@section Variable */
protected:
    std::weak_ptr<Transform> m_parent;
    std::vector<std::shared_ptr<Transform>> m_children;
    Vector3 m_localPosition;
    Vector3 m_localRotation;
    Vector3 m_localScale = Vector3(1.0f, 1.0f, 1.0f);
    Matrix4x4 m_matWorld;
    bool m_isDirty = true;
};

} /* namespace tgon */
