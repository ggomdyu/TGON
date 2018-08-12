/**
 * @file    GraphicsModule.h
 * @author  ggomdyu
 * @since   07/24/2016
 */

#pragma once
#include <memory>
#include <vector>

#include "Core/Object/CoreObject.h"
#include "Core/String/HashStringView.h"

#include "../Object/GameObject.h"

namespace tgon
{

class TGON_API GameScene :
    public CoreObject
{
public:
    TGON_RUNTIME_OBJECT(GameScene);

/* @section Public destructor */
public:
    virtual ~GameScene() = default;

/* @section Public method */
public:
    /* @brief                   Updates the frame of the scene. */
    virtual void Update();
    
    /**
     * @brief                   Adds a GameObject into scene.
     * @param [in] object       The object to insert.
     */
    void AddObject(const std::shared_ptr<GameObject>& object);

    /**
     * @brief                   Find a GameObject with the specified object name.
     * @return                  Returns the found object, nullptr otherwise.
     */
    GameObject* FindObject(const HashStringView& objectName);

    /**
     * @brief                   Find a GameObject with the specified object name.
     * @return                  Returns the found object, nullptr otherwise.
     */
    const GameObject* FindObject(const HashStringView& objectName) const;
    
    /**
     * @brief                   Removes the object which has specified name.
     * @param [in] objectName   The name of object to remove.
     */
    bool RemoveObject(const HashStringView& objectName);

/* @section Private variable */
private:
    std::vector<std::shared_ptr<GameObject>> m_objects;
};

} /* namespace tgon */
