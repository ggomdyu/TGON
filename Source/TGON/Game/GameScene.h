/**
 * @file    GameScene.h
 * @author  ggomdyu
 * @since   08/19/2016
 */

#pragma once
#include <memory>
#include <vector>

#include "Core/CoreObject.h"
#include "String/StringHash.h"

#include "GameObject.h"

namespace tgon
{

class TGON_API GameScene :
    public CoreObject
{
public:
    TGON_DECLARE_RTTI(GameScene);

/**@section Destructor */
public:
    virtual ~GameScene() = default;

/**@section Method */
public:
    /**@brief   Updates the frame of the scene. */
    virtual void Update();
    
    /**
     * @brief   Adds a GameObject into the scene.
     * @param [in] object   The object to insert.
     */
    void AddObject(const std::shared_ptr<GameObject>& object);

    /**
     * @brief   Find a GameObject with the specified object name.
     * @return  Returns the found object, nullptr otherwise.
     */
    std::shared_ptr<GameObject> FindObject(const StringViewHash& objectName);

    /**
     * @brief   Find a GameObject with the specified object name.
     * @return  Returns the found object, nullptr otherwise.
     */
    const std::shared_ptr<GameObject> FindObject(const StringViewHash& objectName) const;
    
    /**
     * @brief   Removes a object which has the specified name.
     * @param [in] objectName   The name of object to remove.
     */
    bool RemoveObject(const StringViewHash& objectName);
    
/**@section Variable */
private:
    std::vector<std::shared_ptr<GameObject>> m_objects;
    
    static std::vector<std::shared_ptr<GameObject>> m_globalObjects;
};

} /* namespace tgon */