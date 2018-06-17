/**
 * @filename    Scene.h
 * @author      ggomdyu
 * @since       06/16/2018
 */

#pragma once
#include <boost/noncopyable.hpp>
#include <memory>

#include "Core/Platform/Config.h"
#include "Core/String/StringViewHash.h"

namespace tgon
{

class GameObject;

class TGON_API Scene :
    private boost::noncopyable
{
/* @section Public destructor */
public:
    virtual ~Scene() = default;
    
/* @section Public method */
public:
    //bool Serialize
    //bool Deserialize
    bool AddObject(std::shared_ptr<GameObject> object);
    bool RemoveObject(const StringViewHash& objectName);
    bool RemoveObject(GameObject* object);
    std::shared_ptr<GameObject> GetObject(const StringViewHash& objectName);
    std::shared_ptr<const GameObject> GetObject(const StringViewHash& objectName) const;

    virtual void OnInitialize() {};
    virtual void Update(float deltaTime) {};
    virtual void Draw() {};

/* @section Private variable */
private:
    std::map<size_t, std::shared_ptr<GameObject>> m_objects;
};

} /* namespace tgon */
