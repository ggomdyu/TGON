/**
 * @file    Scene.h
 * @author  ggomdyu
 * @since   08/19/2016
 */

#pragma once
#include <memory>
#include <vector>
#include <unordered_map>

#include "Core/CoreObject.h"
#include "String/StringHash.h"

#include "GameObject.h"

namespace tgon
{

class TGON_API Scene :
    public CoreObject
{
public:
    TGON_DECLARE_RTTI(Scene)

/**@section Destructor */
public:
    virtual ~Scene() = default;

/**@section Method */
public:
    /**@brief   Updates the frame of the scene. */
    virtual void Update();
    
    /**
     * @brief   Adds a GameObject into the scene.
     * @param [in] object   The object to manage.
     */
    void AddObject(const std::shared_ptr<GameObject>& object);

    /**
     * @brief   Adds a GameObject that alives regardless of scene changes.
     * @param [in] object   The object to manage.
     */
    void AddGlobalObject(const std::shared_ptr<GameObject>& object);

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
     * @brief   Find a global GameObject with the specified object name.
     * @return  Returns the found object, nullptr otherwise.
     */
    std::shared_ptr<GameObject> FindGlobalObject(const StringViewHash& objectName);
    
    /**
     * @brief   Find a global GameObject with the specified object name.
     * @return  Returns the found object, nullptr otherwise.
     */
    std::shared_ptr<const GameObject> FindGlobalObject(const StringViewHash& objectName) const;

    /**
     * @brief   Removes a object which has the specified name.
     * @param [in] objectName   The name of object to remove.
     */
    bool RemoveObject(const StringViewHash& objectName);

    /**
     * @brief   Removes a object which has the specified name.
     * @param [in] objectName   The name of object to remove.
     */
    bool RemoveGlobalObject(const StringViewHash& objectName);

/**@section Variable */
private:
    std::vector<std::shared_ptr<GameObject>> m_objects;
    std::unordered_map<int32_t, int32_t> m_objectNameHashMap;
    
    static std::vector<std::shared_ptr<GameObject>> m_globalObjects;
    static std::unordered_map<int32_t, int32_t> m_globalObjectNameHashMap;
};

} /* namespace tgon */
