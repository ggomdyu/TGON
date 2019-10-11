/**
 * @file    Transform.h
 * @author  ggomdyu
 * @since   08/19/2018
 */

#pragma once
#include <vector>
#include <memory>

#include "Platform/Config.h"
#include "Math/Vector3.h"
#include "Math/Matrix4x4.h"
#include "Component/Component.h"

namespace tgon
{

class TGON_API Transform :
    public Component
{
public:
    TGON_DECLARE_RTTI(Transform)

/**@section Constructor */
public:
    explicit Transform(const std::weak_ptr<GameObject>& gameObject = {}) noexcept;
    Transform(const std::weak_ptr<GameObject>& gameObject, const Vector3& localPosition, const Vector3& localRotation, const Vector3& localScale);
    Transform(const std::weak_ptr<GameObject>& gameObject, const std::shared_ptr<Transform>& parent);
    Transform(const std::weak_ptr<GameObject>& gameObject, const std::shared_ptr<Transform>& parent, const Vector3& localPosition, const Vector3& localRotation, const Vector3& localScale) noexcept;
    explicit Transform(const std::shared_ptr<Transform>& parent);
    Transform(const Vector3& localPosition, const Vector3& localRotation, const Vector3& localScale);
    Transform(const std::shared_ptr<Transform>& parent, const Vector3& localPosition, const Vector3& localRotation, const Vector3& localScale) noexcept;

/**@section Destructor */
public:
    virtual ~Transform() noexcept = default;
    
/**@section Method */
public:
    void SetParent(const std::shared_ptr<Transform>& parent);
    std::shared_ptr<Transform> GetParent() noexcept;
    std::shared_ptr<const Transform> GetParent() const noexcept;
    void SetLocalPosition(const Vector3& localPosition) noexcept;
    void SetLocalRotation(const Vector3& localRotation) noexcept;
    void SetLocalScale(const Vector3& localScale) noexcept;
    const Vector3& GetLocalPosition() const noexcept;
    const Vector3& GetLocalRotation() const noexcept;
    const Vector3& GetLocalScale() const noexcept;
    Vector3 GetPosition() const noexcept;
    const Matrix4x4& GetWorldMatrix() const noexcept;
    virtual void Update() override;
    
/**@section Variable */
protected:
    std::shared_ptr<Transform> m_parent;
    std::vector<std::shared_ptr<Transform>> m_children;
    Vector3 m_localPosition;
    Vector3 m_localRotation;
    Vector3 m_localScale;
    Matrix4x4 m_matWorld;
    bool m_isDirty;
};

} /* namespace tgon */
