/**
 * @file    Scene.h
 * @author  ggomdyu
 * @since   08/19/2016
 */

#pragma once
#include <vector>
#include <unordered_map>

#include "GameObject.h"
#include "String/StringHash.h"

namespace tgon
{

class TGON_API Scene :
    public Object
{
public:
    TGON_DECLARE_RTTI(Scene)

/**@section Destructor */
public:
    virtual ~Scene() = default;

/**@section Method */
public:
    virtual void Initialize() {}
    virtual void Update();
    void AddObject(const std::shared_ptr<GameObject>& object);
    void AddObject(std::shared_ptr<GameObject>&& object);
    void AddGlobalObject(const std::shared_ptr<GameObject>& object);
    bool RemoveObject(const StringViewHash& objectName);
    bool RemoveGlobalObject(const StringViewHash& objectName);
    std::shared_ptr<GameObject> FindObject(const StringViewHash& objectName);
    std::shared_ptr<const GameObject> FindObject(const StringViewHash& objectName) const;
    std::shared_ptr<GameObject> FindGlobalObject(const StringViewHash& objectName);
    std::shared_ptr<const GameObject> FindGlobalObject(const StringViewHash& objectName) const;

/**@section Variable */
private:
    std::vector<std::shared_ptr<GameObject>> m_objects;
    static std::vector<std::shared_ptr<GameObject>> m_globalObjects;
    
    std::unordered_map<size_t, int32_t> m_objectNameHashMap;
    static std::unordered_map<size_t, int32_t> m_globalObjectNameHashMap;
};

} /* namespace tgon */
