/**
 * @filename    GameObject.h
 * @author      ggomdyu
 * @since       03/22/2016
 */

#pragma once
#include <boost/noncopyable.hpp>
#include <vector>

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

/* @section Public constructor */
public:
    GameObject();

/* @section Public destructor */
public:
    virtual ~GameObject() override;

/* @section Public method */
public:
    void Update();

    template <typename _ComponentType, typename... _ArgTypes>
    void AddComponent(_ArgTypes&&... args);
    void AddComponent(const std::shared_ptr<Component>& component);
    template <typename _ComponentType>
    std::shared_ptr<_ComponentType> GetComponent() const;

    void AddChild(const std::shared_ptr<GameObject>& child);
    std::vector<std::shared_ptr<GameObject>>& GetChildren() noexcept;
    const std::vector<std::shared_ptr<GameObject>>& GetChildren() const noexcept;

/* @section Private variable */
private:
    std::map<std::size_t, std::shared_ptr<Component>> m_components;
    std::vector<std::shared_ptr<GameObject>> m_children;
};

template<typename _ComponentType, typename... _ArgTypes>
inline void GameObject::AddComponent(_ArgTypes&& ...args)
{
    m_components.emplace(tgon::GetRTTI<GameObject>()->GetHashCode(), std::make_shared<_ComponentType>(std::forward<_ArgTypes>(args)...));
}

template<typename _ComponentType>
inline std::shared_ptr<_ComponentType> GameObject::GetComponent() const
{
    auto iter = m_components.find(tgon::GetRTTI<GameObject>()->GetHashCode());
    if (iter == m_components.end())
    {
        return nullptr;
    }

    return std::static_pointer_cast<_ComponentType>(iter->second);
}

} /* namespace tgon */
