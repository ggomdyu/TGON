/**
 * @file    Component.h
 * @author  ggomdyu
 * @since   04/26/2015
 */

#pragma once
#include "Core/Object.h"
#include "Core/NonCopyable.h"

namespace tgon
{

class GameObject;
    
class TGON_API Component :
	public Object
{
public:
    TGON_DECLARE_RTTI(Component)

/**@section Constructor */
public:
    Component(const std::weak_ptr<GameObject>& gameObject = {}) noexcept;

/**@section Destructor */
public:
    virtual ~Component() override = default;

/**@section Method */
public:
    virtual void Update() = 0;
    void SetGameObject(const std::weak_ptr<GameObject>& gameObject) noexcept;
    std::weak_ptr<GameObject> GetGameObject() noexcept;
    std::weak_ptr<const GameObject> GetGameObject() const noexcept;
    void SetAcitve(bool isActive) noexcept;
    bool IsActive() const noexcept;

/**@section Variable */
protected:
    bool m_isActive;
    std::weak_ptr<GameObject> m_gameObject;
};

} /* namespace tgon */
