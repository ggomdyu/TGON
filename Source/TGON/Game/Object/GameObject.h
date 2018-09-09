/**
 * @file    GameObject.h
 * @author  ggomdyu
 * @since   03/22/2016
 */

#pragma once
#include <vector>

#include "Core/Object/CoreObject.h"
#include "Core/String/FixedHashString.h"

#include "../Component/Component.h"

#include "Transform.h"

namespace tgon
{

class TGON_API GameObject :
	public CoreObject
{
public:
    TGON_RUNTIME_OBJECT(GameObject);

/* @section Private constructor */
public:
    explicit GameObject(const FixedHashString32& name);
    
/* @section Public destructor */
public:
    virtual ~GameObject() override = default;

/* @section Public method */
public:
    /* @brief   Updates the object. */
    virtual void Update();

    /**
     * @brief   Sets the name of object.
     * @param [in] name     The name to set.
     */
    void SetName(const FixedHashString32& name)
    {
        m_name = name;
    }

    template <typename _ComponentType, typename... _ArgTypes>
    std::shared_ptr<_ComponentType> AddComponent(_ArgTypes&&... args)
    {
        return std::static_pointer_cast<_ComponentType>(this->AddComponent(new _ComponentType(std::forward<_ArgTypes>(args)...)));
    }
    
    /**
     * @brief   Inserts a component to manage.
     * @param [in] component    The component to insert.
     */
    const std::shared_ptr<Component>& AddComponent(Component* component);

    /**
     * @brief   Removes the managed component.
     * @tparam _ComponentType   The type of component to remove.
     * @return  Returns true if successful, false otherwise.
     */
    template <typename _ComponentType, std::enable_if_t<std::is_base_of<Component, _ComponentType>::value>* = nullptr>
    bool RemoveComponent()
    {
        return this->RemoveComponent(GetComponentId<_ComponentType>());
    }

    /**
     * @brief   Gets a component that managed by this object.
     * @tparam _ComponentType   The type of component to get.
     * @return  Returns the pointer to component if successful, nullptr otherwise.
     */
    template <typename _ComponentType, std::enable_if_t<std::is_base_of<Component, _ComponentType>::value>* = nullptr>
    std::shared_ptr<const _ComponentType> GetComponent() const
    {
        return const_cast<GameObject*>(this)->GetComponent<_ComponentType>();
    }

    /**
     * @brief   Gets a component that managed by this object.
     * @tparam _ComponentType   The type of component to get.
     * @return  Returns the pointer to component if successful, nullptr otherwise.
     */
    template <typename _ComponentType, std::enable_if_t<std::is_base_of<Component, _ComponentType>::value>* = nullptr>
    std::shared_ptr<_ComponentType> GetComponent()
    {
        return std::static_pointer_cast<_ComponentType>(GetComponent(GetComponentId<_ComponentType>()));
    }

    /**
     * @brief   Gets the name of object.
     * @return  The name of object to set.
     */
    const FixedHashString32& GetName() const noexcept
    {
        return m_name;
    }

    /* @brief   Sets the position of this object. */
    void SetPosition(const Vector3& position)
    {
        m_transform.SetPosition(position);
    }
    
    /* @brief   Moves this object. */
    void Move(const Vector3& position)
    {
        m_transform.SetPosition(m_transform.GetPosition() + position);
    }
    
    /* @brief   Sets the rotation of this object. */
    void SetRotation(const Vector3& rotation)
    {
        m_transform.SetRotation(rotation);
    }
    
    /* @brief   Rotates this object. */
    void Rotate(const Vector3& rotation)
    {
        m_transform.SetRotation(m_transform.GetRotation() + rotation);
    }
    
    /* @brief   Sets the scale of this object. */
    void SetScale(const Vector3& scale)
    {
        m_transform.SetScale(scale);
    }
    
    /* @brief   Scales up this object. */
    void Scale(const Vector3& scale)
    {
        m_transform.SetScale(m_transform.GetScale() + scale);
    }
    
    /* @brief   Gets the transform. */
    Transform& GetTransform() noexcept
    {
        return m_transform;
    }

    /* @brief   Gets the transform. */
    const Transform& GetTransform() const noexcept
    {
        return m_transform;
    }

    /**
     * @brief   Sets this object activate or deactivate.
     * @details If this object deactivated, the object will not be updated.
     */
    void SetActivate(bool isActivate)
    {
        m_isActivated = isActivate;
    }

    /* @brief   Gets the state for whether this object has been activated or deactivated. */
    bool IsActivated() const noexcept
    {
        return m_isActivated;
    }

/* @section Private method */
private:
    /**
     * @brief   Removes the managed component.
     * @param [in] componentId  The unique id of component to get.
     */
    bool RemoveComponent(size_t componentId);

    /**
     * @brief   Gets a component that managed by this object.
     * @param [in] componentId  The unique id of component to get.
     * @return  Returns the pointer to component if successful, nullptr otherwise.
     */
    std::shared_ptr<Component> GetComponent(size_t componentId);

/* @section Private variable */
private:
    bool m_isActivated;

    FixedHashString32 m_name;

    std::vector<std::shared_ptr<Component>> m_components;

    Transform m_transform;
};

} /* namespace tgon */
