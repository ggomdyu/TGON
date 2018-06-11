/**
 * @filename    GameObject.h
 * @author      ggomdyu
 * @since       03/22/2016
 */

#pragma once
#include <boost/noncopyable.hpp>
#include <initializer_list>
#include <vector>
#include <algorithm>

#include "Core/Object/Object.h"

#include "GameObjectFwd.h"

namespace tgon
{

class TGON_API GameObject :
	public Object,
    private boost::noncopyable
{
public:
    TGON_RUNTIME_OBJECT(GameObject);

/* @section Public destructor */
public:
    virtual ~GameObject() override;

/* @section Public method */
public:
    void Update();

    void AddComponent(std::initializer_list<std::unique_ptr<Component>> components);
    template <typename _ComponentType, typename... _ArgTypes>
    void AddComponent(_ArgTypes&&... args);
    void AddComponent(std::unique_ptr<Component> component);
    template <typename _ComponentType>
    const _ComponentType* GetComponent() const;
    template <typename _ComponentType>
    _ComponentType* GetComponent();

/* @section Private variable */
private:
    std::vector<std::unique_ptr<Component>> m_components;
};

template<typename _ComponentType, typename... _ArgTypes>
inline void GameObject::AddComponent(_ArgTypes&& ...args)
{
    this->AddComponent(std::make_unique<_ComponentType>(std::forward<_ArgTypes>(args)...));
}

template<typename _ComponentType>
inline const _ComponentType* GameObject::GetComponent() const
{
    return const_cast<GameObject*>(this)->GetComponent<_ComponentType>();
}
    
template<typename _ComponentType>
inline _ComponentType* GameObject::GetComponent()
{
//    m_components.find_if(m_components.begin(), m_components.end(), [](const std::unique_ptr<Component>& component)
//    {
//        return component->GetRTTI()->GetHashCode() == GetRTTI<_ComponentType>()->GetHashCode();
//    });
//
//    return static_cast<_ComponentType*>(iter->second);
    return nullptr;
}

} /* namespace tgon */
