/**
 * @file    Component.h
 * @author  ggomdyu
 * @since   04/26/2015
 */

#pragma once
#include "Core/CoreObject.h"
#include "Core/NonCopyable.h"

namespace tgon
{

class GameObject;
    
class TGON_API Component :
	public CoreObject,
    private NonCopyable
{
public:
    TGON_DECLARE_RTTI(Component)

/**@section Constructor */
public:
    Component(GameObject* owner = nullptr) noexcept;

/**@section Destructor */
public:
    virtual ~Component() override = default;

/**@section Method */
public:
    virtual void Update() = 0;
    void SetOwner(GameObject* owner);
    const GameObject* GetOwner() const noexcept;
    GameObject* GetOwner() noexcept;
    void SetAcitve(bool isActive) noexcept;
    bool IsActive() const noexcept;

/**@section Variable */
private:
    bool m_isActive;
    GameObject* m_owner;
};

} /* namespace tgon */
