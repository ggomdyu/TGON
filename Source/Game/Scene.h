/**
 * @file    Scene.h
 * @author  ggomdyu
 * @since   08/19/2016
 */

#pragma once
#include "GameObject.h"

namespace tgon
{

class Scene :
    public GameObject
{
public:
    TGON_DECLARE_RTTI(Scene)

/**@section Method */
public:
    template <typename _ObjectType = GameObject, typename... _ArgTypes>
    static std::shared_ptr<_ObjectType> Create(_ArgTypes&&... args);
};

template <typename _ObjectType, typename... _ArgTypes>
inline std::shared_ptr<_ObjectType> Scene::Create(_ArgTypes&&... args)
{
    auto object = std::make_shared<_ObjectType>(std::forward<_ArgTypes>(args)...);
    
    if (object->m_transform != nullptr)
    {
        object->m_transform->SetGameObject(object);
    }

    return object;
}

} /* namespace tgon */