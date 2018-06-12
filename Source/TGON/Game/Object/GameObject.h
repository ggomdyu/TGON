/**
 * @filename    GameObject.h
 * @author      ggomdyu
 * @since       03/22/2016
 */

#pragma once
#include <boost/noncopyable.hpp>
#include <vector>
#include <algorithm>

#include "Core/Object/Object.h"

#include "GameObjectFwd.h"

namespace tgon
{

class TGON_API GameObject final :
	public Object,
    private boost::noncopyable
{
public:
    TGON_RUNTIME_OBJECT(GameObject);

/* @section Public constructor */
public:
    explicit GameObject(const std::string& name);
    
/* @section Public destructor */
public:
    virtual ~GameObject() override;

/* @section Public method */
public:
    void Update();

    void SetName(const std::string& name);
    const std::string& GetString() const noexcept;
    template <typename _ComponentType, typename... _ArgTypes>
    void AddComponent(_ArgTypes&&... args);
    void AddComponent(std::unique_ptr<Component> component);
    template <typename _ComponentType>
    const _ComponentType* GetComponent() const;
    template <typename _ComponentType>
    _ComponentType* GetComponent();
    template <typename _ComponentType>
    bool RemoveComponent();
    
/* @section Private method */
private:
    bool RemoveComponent(size_t componentId);
    Component* GetComponent(size_t componentId);
    
/* @section Private variable */
private:
    std::string m_name;
    std::vector<std::unique_ptr<Component>> m_components;
};

template<typename _ComponentType, typename... _ArgTypes>
inline void GameObject::AddComponent(_ArgTypes&&... args)
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
    return static_cast<_ComponentType*>(this->GetComponent(tgon::GetRTTI<_ComponentType>()->GetHashCode()));
}
    
template <typename _ComponentType>
inline bool GameObject::RemoveComponent()
{
    return this->RemoveComponent(tgon::GetRTTI<_ComponentType>()->GetHashCode());
}

} /* namespace tgon */
