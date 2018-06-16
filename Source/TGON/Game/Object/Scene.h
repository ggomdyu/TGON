/**
 * @filename    Scene.h
 * @author      ggomdyu
 * @since       06/16/2018
 */

#pragma once
#include <boost/noncopyable.hpp>
#include <memory>

#include "Core/String/StringViewHash.h"

namespace tgon
{

class GameObject;

class Scene :
    private boost::noncopyable
{
/* @section Public method */
public:
    //bool Serialize
    //bool Deserialize
    bool AddObject(const std::shared_ptr<GameObject>& object);
    bool RemoveObject(const StringViewHash& objectName);
    bool RemoveObject(GameObject* object);
    std::shared_ptr<GameObject> GetObject(const StringViewHash& objectName);
    std::shared_ptr<const GameObject> GetObject(const StringViewHash& objectName) const;

    virtual void OnInitialize() = 0;
    virtual void Update(float deltaTime) = 0;
    virtual void Draw() = 0;

/* @section Private variable */
private:
    std::map<size_t, std::shared_ptr<GameObject>> m_objects;
};

} /* namespace tgon */
