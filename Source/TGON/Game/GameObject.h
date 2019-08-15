/**
 * @file    GameObject.h
 * @author  ggomdyu
 * @since   03/22/2016
 */

#pragma once
#include <vector>

#include "Core/CoreObject.h"
#include "Graphics/Transform.h"
#include "String/StringHash.h"
#include "Component/Component.h"

namespace tgon
{

class TGON_API GameObject :
	public CoreObject
{
public:
    TGON_DECLARE_RTTI(GameObject);

/**@section Constructor */
public:
    template <typename... _ComponentTypes>
    explicit GameObject(const StringHash& name, Transform* transform, _ComponentTypes&&... components) :
        m_name(name),
        m_transform(transform),
        m_isActive(true),
        m_components(std::forward<_ComponentTypes>(components)...)
    {
    }

/**@section Destructor */
public:
    virtual ~GameObject() override = default;

/**@section Method */
public:
    /**@brief   Updates the object. */
    virtual void Update();

    /**@brief   Inserts a component to manage. */
    template <typename _ComponentType, typename... _ArgTypes>
    std::shared_ptr<_ComponentType> AddComponent(_ArgTypes&&... args)
    {
        auto component = std::make_shared<_ComponentType>(std::forward<_ArgTypes>(args)...);
        component->SetOwner(this);
        
        m_components.push_back(component);
        
        return component;
    }
    
    template <typename _ComponentType>
    std::shared_ptr<_ComponentType> AddComponent(const std::shared_ptr<_ComponentType>& component)
    {
        m_components.push_back(component);
        
        component->SetOwner(this);
        return component;
    }

    /**
     * @brief   Removes the managed component.
     * @tparam _ComponentType   The type of component to remove.
     * @return  Returns true if successful, false otherwise.
     */
    template <typename _ComponentType>
    bool RemoveComponent()
    {
        static_assert(std::is_base_of<Component, _ComponentType>::value, "_ComponentType must be inherited from Component.");
        
        return this->RemoveComponent(GetComponentId<_ComponentType>());
    }

    /**
     * @brief   Gets a component that managed by this object.
     * @tparam _ComponentType   The type of component to get.
     * @return  Returns a pointer to component if successful, nullptr otherwise.
     */
    template <typename _ComponentType>
    std::shared_ptr<const _ComponentType> GetComponent() const
    {
        static_assert(std::is_base_of<Component, _ComponentType>::value, "_ComponentType must be inherited from Component.");
        
        return const_cast<decltype(this)>(this)->GetComponent<_ComponentType>();
    }

    /**
     * @brief   Gets a component that managed by this object.
     * @tparam _ComponentType   The type of component to get.
     * @return  Returns a pointer to component if successful, nullptr otherwise.
     */
    template <typename _ComponentType>
    std::shared_ptr<_ComponentType> GetComponent()
    {
        static_assert(std::is_base_of<Component, _ComponentType>::value, "_ComponentType must be inherited from Component.");
        
        return std::static_pointer_cast<_ComponentType>(GetComponent(GetComponentId<_ComponentType>()));
    }

    /**
     * @brief   Sets the name of this object.
     * @param [in] name     The name to set.
     */
    void SetName(const StringHash& name);

    /**@brief   Gets the name of this object. */
    const StringHash& GetName() const noexcept;

    /**
     * @brief   Activates or deactivates this object.
     * @remarks If the isActive is true, then all updates will be stopped.
     */
    void SetActive(bool isActive);

    /**@brief   Gets the active state of this object. */
    bool IsActive() const noexcept;
    
    std::shared_ptr<Transform> GetTransform() noexcept;
    
    std::shared_ptr<const Transform> GetTransform() const noexcept;

private:
    /**
     * @brief   Removes a component with its unique id.
     * @param [in] componentId  The unique id of component to remove.
     */
    bool RemoveComponent(size_t componentId);

    /**
     * @brief   Gets a component that managed by this object.
     * @param [in] componentId  The unique id of component to get.
     * @return  Returns the pointer to component if successful, nullptr otherwise.
     */
    std::shared_ptr<Component> GetComponent(size_t componentId);

/**@section Variable */
private:
    StringHash m_name;
    std::shared_ptr<Transform> m_transform;
    bool m_isActive;
    std::vector<std::shared_ptr<Component>> m_components;
};

}
