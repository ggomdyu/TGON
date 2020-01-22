/**
 * @file    Component.h
 * @author  ggomdyu
 * @since   04/26/2015
 */

#pragma once
#include "Core/RuntimeObject.h"

namespace tgon
{

class GameObject;

class Component :
    public RuntimeObject
{
public:
    TGON_DECLARE_RTTI(Component)

/**@section Constructor */
public:
    Component() noexcept = default;
    Component(const std::shared_ptr<GameObject>& gameObject) noexcept;

/**@section Method */
public:
    virtual void Initialize() {}
    virtual void Update() {}
    void SetGameObject(const std::shared_ptr<GameObject>& gameObject) noexcept;
    void SetAcitve(bool isActive) noexcept;
    std::shared_ptr<GameObject> GetGameObject() noexcept;
    std::shared_ptr<const GameObject> GetGameObject() const noexcept;
    bool IsActive() const noexcept;

/**@section Variable */
protected:
    std::weak_ptr<GameObject> m_gameObject;
    bool m_isActive = true;
};

} /* namespace tgon */
